#include "stdafx.h"
#include <fstream>

#ifdef _DEBUG
#include <xbdm.h>
#endif

#pragma warning(disable:4101) // unreferenced variable warning(certain variables are only needed when compiling for XDK

namespace xbox {
	namespace utilities {
		// Resolve set memory
		pDmSetMemory DevSetMemory = NULL;

		typedef void (*XNotifyQueueUI1)(XNOTIFYQUEUEUI_TYPE exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData);
		XNotifyQueueUI1 XNotifyD = (XNotifyQueueUI1)resolveFunction("xam.xex", 656);

		DWORD MountPath(PCHAR Drive, PCHAR Device) {
			CHAR Destination[MAX_PATH] = { 0 };
			sprintf_s(Destination, MAX_PATH, (KeGetCurrentProcessType() == PROC_SYSTEM) ? OBJ_SYS_STRING : OBJ_USR_STRING, Drive);
			ANSI_STRING LinkName, DeviceName;
			RtlInitAnsiString(&LinkName, Destination);
			RtlInitAnsiString(&DeviceName, Device);
			ObDeleteSymbolicLink(&LinkName);
			return (DWORD)ObCreateSymbolicLink(&LinkName, &DeviceName);
		}

		VOID ApplyOffsetPatches(DWORD StartAddress, CONST PVOID Patch) {
			PDWORD PatchBlock = (PDWORD)Patch;

			while (*PatchBlock != 0xFFFFFFFF)
			{
				memcpy((PVOID)(StartAddress + PatchBlock[0x00]), &PatchBlock[0x02], (PatchBlock[0x01] * sizeof(DWORD)));
				PatchBlock += (PatchBlock[0x01] + 0x02);
			}
		}

		void DbgOut(const char* text, ...) {
			char dest[0x512]; // WARNING: SYSTEM CRASH IF EXCEEDS STACK SIZE
			va_list args;
			va_start(args, text);
			vsprintf(dest, text, args);
			va_end(args);
			printf("%s", dest);
			std::ofstream log_file(va("Usb:\\100F0\\Domo-%i.txt", XboxKrnlVersion->Build), std::ios_base::app);
			if (log_file.is_open())
				log_file << dest;
			else
				return;
		}

		BOOL DumpFile(const CHAR* szFileName, BYTE* pbData, DWORD dwSize) {
			FILE* f = fopen(szFileName, "wb");

			if (f) {
				fwrite(pbData, 1, dwSize, f);
				fflush(f);
				fclose(f);
				return TRUE;
			}

			return FALSE;
		}

		std::string va(char* format, ...) {
			char charBuffer[0x200];
			va_list arglist;
			va_start(arglist, format);
			vsprintf(charBuffer, format, arglist);
			va_end(arglist);
			return std::string(charBuffer);
		}

		DWORD applyPatches(VOID* patches) {
			DWORD patchCount = 0;
			MemoryBuffer mbPatches;
			DWORD* patchData = (DWORD*)patches;

			if (patchData == NULL)
				return 0;

			while (*patchData != 0xFFFFFFFF) {
				BOOL inHvMode = (patchData[0] < 0x40000);
				QWORD patchAddr = inHvMode ? (0x200000000 * (patchData[0] / 0x10000)) + patchData[0] : (QWORD)patchData[0];
				xbox::utilities::setMemory((VOID*)patchData[0], &patchData[2], patchData[1] * sizeof(DWORD));
				patchData += (patchData[1] + 2);
				patchCount++;
			}

			return patchCount;
		}

		VOID launchDefaultApp() {
			XSetLaunchData(NULL, 0);
			XamLoaderLaunchTitleEx(XLAUNCH_KEYWORD_DEFAULT_APP, NULL, NULL, 0);
		}

		VOID patchInJump(DWORD* Address, DWORD Destination, BOOL Linked) {
			Address[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
			if (Destination & 0x8000) Address[0] += 1;
			Address[1] = 0x396B0000 + (Destination & 0xFFFF);
			Address[2] = 0x7D6903A6;
			Address[3] = Linked ? 0x4E800421 : 0x4E800420;
		}

		VOID PatchInBranch(DWORD* Address, DWORD Destination, BOOL Linked) {
			Address[0] = (0x48000000 + ((Destination - (DWORD)Address) & 0x3FFFFFF));
			if (Linked) Address[0] += 1;
		}

		QWORD getFuseline(DWORD fuse) {
			if ((fuse * 0x40) < 0x300)
				return Hvx::HvPeekQWORD(0x8000020000020000ULL + ((fuse * 0x40) << 3));
			return 0;
		}

		void getCPUKey(BYTE* KeyBuf) {
			QWORD Key1 = getFuseline(3) | getFuseline(4);
			QWORD Key2 = getFuseline(5) | getFuseline(6);

			memcpy(KeyBuf, &Key1, 8);
			memcpy(KeyBuf + 8, &Key2, 8);
		}

		FARPROC resolveFunction(CHAR* ModuleName, DWORD Ordinal) {
			HMODULE mHandle = GetModuleHandle(ModuleName);
			return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
		}

		DWORD patchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
		{
			LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
			return (moduleHandle == NULL) ? S_FALSE : patchModuleImport(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);
		}

		DWORD patchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
		{
			DWORD address = (DWORD)resolveFunction(ImportedModuleName, Ordinal);
			if (address == NULL)
				return S_FALSE;

			VOID* headerBase = Module->XexHeaderBase;
			PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
			if (importDesc == NULL)
				return S_FALSE;

			DWORD result = 2;

			CHAR* stringTable = (CHAR*)(importDesc + 1);

			XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);

			for (DWORD x = 0; x < importDesc->ModuleCount; x++)
			{
				DWORD* importAdd = (DWORD*)(importTable + 1);
				for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++)
				{
					DWORD value = *((DWORD*)importAdd[y]);
					if (value == address)
					{
						setMemory((DWORD*)importAdd[y], &PatchAddress, 4);
						DWORD newCode[4];
						patchInJump(newCode, PatchAddress, FALSE);
						setMemory((DWORD*)importAdd[y + 1], newCode, 16);
						result = S_OK;
					}
				}
				importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
			}
			return result;
		}

		DWORD ReadHighLow(DWORD Address, DWORD HighAdditive, DWORD LowAdditive, char label[50]) {
			DWORD returnAddr = (*(PWORD)(Address + HighAdditive) << 16) | *(PWORD)(Address + LowAdditive);
			DWORD returnFinal = (returnAddr & 0x8000) ? returnAddr - 0x10000 : returnAddr;

			return returnFinal;
		}

		VOID __declspec(naked) GLPR(VOID) {
			__asm
			{
				std     r14, -0x98(sp)
				std     r15, -0x90(sp)
				std     r16, -0x88(sp)
				std     r17, -0x80(sp)
				std     r18, -0x78(sp)
				std     r19, -0x70(sp)
				std     r20, -0x68(sp)
				std     r21, -0x60(sp)
				std     r22, -0x58(sp)
				std     r23, -0x50(sp)
				std     r24, -0x48(sp)
				std     r25, -0x40(sp)
				std     r26, -0x38(sp)
				std     r27, -0x30(sp)
				std     r28, -0x28(sp)
				std     r29, -0x20(sp)
				std     r30, -0x18(sp)
				std     r31, -0x10(sp)
				stw     r12, -0x8(sp)
				blr
			}
		}

		DWORD RelinkGPLR(DWORD SFSOffset, PDWORD SaveStubAddress, PDWORD OriginalAddress) {
			DWORD Instruction = 0, Replacing;
			PDWORD Saver = (PDWORD)GLPR;

			if (SFSOffset & 0x2000000) {
				SFSOffset = SFSOffset | 0xFC000000;
			}
			Replacing = OriginalAddress[SFSOffset / 4];

 			for (int i = 0; i < 20; i++) {
				if (Replacing == Saver[i]) {
					DWORD NewOffset = (DWORD)&Saver[i] - (DWORD)SaveStubAddress;
					Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
				}
			}
			return Instruction;
		}

		VOID hookFunctionStart(PDWORD Address, PDWORD SaveStub, DWORD Destination) {
			if ((SaveStub != NULL) && (Address != NULL)) {
				DWORD AddressRelocation = (DWORD)(&Address[4]);
				if (AddressRelocation & 0x8000) {
					SaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1);
				} else {
					SaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF);
				}
				SaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF);
				SaveStub[2] = 0x7D6903A6;

				for (int i = 0; i < 4; i++) {
					if ((Address[i] & 0x48000003) == 0x48000001) {
						SaveStub[i + 3] = RelinkGPLR((Address[i] & ~0x48000003), &SaveStub[i + 3], &Address[i]);
					} else {
						SaveStub[i + 3] = Address[i];
					}
				}

				SaveStub[7] = 0x4E800420;
				__dcbst(0, SaveStub);
				__sync();
				__isync();
				patchInJump(Address, Destination, FALSE);
			}
		}

		HRESULT setMemory(VOID* Destination, VOID* Source, DWORD Length){
			if (DevSetMemory == NULL){
				DevSetMemory = (pDmSetMemory)resolveFunction("xbdm.xex", 40);
			}
			if (DevSetMemory == NULL){
				memcpy(Destination, Source, Length);
				return ERROR_SUCCESS;
			}else{
				if (DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0, 0x2da, 0))
					return ERROR_SUCCESS;
			}
			return E_FAIL;
		}

		HRESULT setMemory(VOID* Destination, DWORD Value){
			return setMemory(Destination, &Value, 4);
		}

		BOOL GetSectionInfo(CONST PCHAR SectionName, PDWORD Address, PDWORD Length) {
			DWORD SectionInfoOffset = 0x82000000;
			while (!strcmp(".rdata", (PCHAR)SectionInfoOffset) == FALSE) {
				SectionInfoOffset += 4;
			}
			PIMAGE_SECTION_HEADER DefaultSections = (PIMAGE_SECTION_HEADER)SectionInfoOffset;

			BOOL Succeded = FALSE;
			for (DWORD i = 0; strlen((PCHAR)DefaultSections[i].Name); i++) {
				if (!strcmp(SectionName, (PCHAR)DefaultSections[i].Name) == TRUE) {
					*Address = 0x82000000 + _byteswap_ulong(DefaultSections[i].VirtualAddress);
					*Length = _byteswap_ulong(DefaultSections[i].Misc.VirtualSize);
					Succeded = TRUE;
					break;
				}
			}

			return Succeded;
		}

		BOOL DataCompare(PBYTE pbData, PBYTE pbMask, PCHAR szMask) {
			for (; *szMask; ++szMask, ++pbData, ++pbMask) {
				if (*szMask == 'X' && *pbData != *pbMask) {
					return FALSE;
				}
			}
			return (*szMask == NULL);
		}

		DWORD FindPattern(PCHAR SectionName, PCHAR pbMask, PCHAR szMask){
			DWORD Address, Length;
			if (GetSectionInfo(SectionName, &Address, &Length) == TRUE) {
				for (DWORD i = 0; i < Length; i++) {
					if (DataCompare((PBYTE)(Address + i), (PBYTE)pbMask, szMask) == TRUE) {
						return Address + i;
					}
				}
			}
			return NULL;
		}

		DWORD ReadHighLow(DWORD Address, DWORD HighAdditive, DWORD LowAdditive) {
			DWORD ReturnAddress = (*(PWORD)(Address + HighAdditive) << 16) | *(PWORD)(Address + LowAdditive);
			return (ReturnAddress & 0x8000) ? ReturnAddress - 0x10000 : ReturnAddress;
		}

		VOID MakeThread(LPTHREAD_START_ROUTINE Address) {
			HANDLE Handle = 0;
			ExCreateThread(&Handle, 0, 0, XapiThreadStartup, Address, 0, (EX_CREATE_FLAG_SUSPENDED | EX_CREATE_FLAG_SYSTEM | 0x18000424));
			XSetThreadProcessor(Handle, 4);
			SetThreadPriority(Handle, THREAD_PRIORITY_ABOVE_NORMAL);
			ResumeThread(Handle);
			CloseHandle(Handle);
		}

		BOOL pfShow = (BOOL)0xDEADBEEF;  //flag to init values
		BOOL pfShowMovie;
		BOOL pfPlaySound;
		BOOL pfShowIPTV;

		VOID toggleNotify(BOOL on) {
			if ((int)pfShow == 0xDEADBEEF) //init values
				XNotifyUIGetOptions(&pfShow, &pfShowMovie, &pfPlaySound, &pfShowIPTV);

			if (!on) {

				XNotifyUISetOptions(pfShow, pfShowMovie, pfPlaySound, pfShowIPTV);  //set back original values
			} else {
				XNotifyUISetOptions(true, true, true, true);  //turn on notifications so XBLSE msgs always show..
			}
			Sleep(500);
		}

		VOID XDoNotify(PWCHAR Message) {
			toggleNotify(true);
			XNotifyD(XNOTIFYUI_TYPE_GENERIC, XUSER_INDEX_ANY, XNOTIFYUI_PRIORITY_HIGH, Message, NULL);
			toggleNotify(false);
		}

		VOID XNotify(std::string str) {
			std::wstring wstr = std::wstring(str.begin(), str.end());
			const PWCHAR pwszStringParam = (PWCHAR)wstr.c_str();
			if (KeGetCurrentProcessType() != PROC_USER)
			{
				HANDLE th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XDoNotify, (LPVOID)pwszStringParam, CREATE_SUSPENDED, NULL);
				if (th == NULL) return;
				ResumeThread(th);
				return;
			}
			else
				XDoNotify(pwszStringParam);
		}

		BOOL fileExists(LPCSTR lpFileName) {
			if (GetFileAttributes(lpFileName) == -1) {
				DWORD lastError = GetLastError();
				if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
					return FALSE;
			}
			return TRUE;
		}

		BOOL writeFile(const CHAR* FilePath, const VOID* Data, DWORD Size) {
			// Open our file
			HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (fHandle == INVALID_HANDLE_VALUE) {
				//DbgPrint("writeFile - CreateFile failed");
				return FALSE;
			}

			// Write our data and close
			DWORD writeSize = Size;
			if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE) {
				//DbgPrint("writeFile - WriteFile failed");
				return FALSE;
			}

			CloseHandle(fHandle);
			return TRUE;
		}

		BOOL readFile(const CHAR* FileName, MemoryBuffer& pBuffer) {
			HANDLE hFile; DWORD dwFileSize, dwNumberOfBytesRead;
			hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) {
				//DbgPrint("readFile - CreateFile failed");
				return FALSE;
			}
			dwFileSize = GetFileSize(hFile, NULL);
			PBYTE lpBuffer = (BYTE*)malloc(dwFileSize);
			if (lpBuffer == NULL) {
				CloseHandle(hFile);
				//DbgPrint("readFile - malloc failed");
				return FALSE;
			}

			if (ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE) {
				free(lpBuffer);
				CloseHandle(hFile);
				//DbgPrint("readFile - ReadFile failed");
				return FALSE;
			}
			else if (dwNumberOfBytesRead != dwFileSize) {
				free(lpBuffer);
				CloseHandle(hFile);
				//DbgPrint("readFile - Failed to read all the bytes");
				return FALSE;
			}
			CloseHandle(hFile);
			pBuffer.Add(lpBuffer, dwFileSize);
			free(lpBuffer);
			return TRUE;
		}
	}
}