#include "stdafx.h"
#include <direct.h>
#include <xui.h>
#include "soc.h"
//=========================================================================================
BYTE Keys[0x30]		= { 0x00 };
//=========================================================================================
VOID DumpSRAM(char* file) {
	xbox::utilities::DbgOut("DumpSRAM: %s\n", file);
	PBYTE pCache2 = (PBYTE)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(pCache2, 0, 0x1000);
	xbox::Hvx::HvPeekBytes(0x8000020000010000, pCache2, 0x1000);
	xbox::utilities::writeFile(file, pCache2, 0x1000);
	XPhysicalFree(pCache2);
}
//=========================================================================================
VOID DumpHV(char* file) {
	xbox::utilities::DbgOut("DumpHV: %s_DEC.bin\n", file);

	BYTE* LiveHV = (BYTE*)XPhysicalAlloc(0x40000, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(LiveHV, 0, 0x40000);
	xbox::Hvx::HvPeekBytes(0, LiveHV, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010200010000, LiveHV + 0x10000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010400020000, LiveHV + 0x20000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010600030000, LiveHV + 0x30000, 0xFFFF);
	xbox::utilities::writeFile(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\%s_DEC.bin", XboxKrnlVersion->Build, file).c_str(), LiveHV, 0x40000);
	XPhysicalFree(LiveHV);

	xbox::utilities::DbgOut("DumpHV: %s_ENC.bin\n", file);
	PBYTE pbHVPage0 = (PBYTE)XPhysicalAlloc(0x40000, MAXULONG_PTR, 0, PAGE_READWRITE);
	memcpy(pbHVPage0, (PVOID)0x80000000, 0x40000);
	xbox::utilities::writeFile(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\%s_ENC.bin", XboxKrnlVersion->Build, file).c_str(), pbHVPage0, 0x40000);
	XPhysicalFree(pbHVPage0);
}
//=========================================================================================
VOID DumpKeys(char* file) {
	xbox::utilities::DbgOut("DumpKeys: %s\n", file);
	PBYTE Keys = (PBYTE)XPhysicalAlloc(0x30, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Keys, 0, 0x30);
	xbox::Hvx::HvPeekBytes(0x0000000200010100, Keys, 0x30);
	memcpy(Keys, Keys, 0x30);
	xbox::utilities::writeFile(file, Keys, 0x30);
}
//=========================================================================================
void RunChallenges() {
	//=========================================================
	typedef struct {
		BYTE header[0x20]; //0x0
		BYTE result[0x08]; //0x20
		BYTE HvMagic[0x02]; //0x28
		BYTE HvVersion[0x02]; //0x2A
		BYTE HvQfe[0x02]; //0x2C
		BYTE BldrFlags[0x02]; //0x2E
		BYTE BaseKernelVersion[0x04]; //0x30
		BYTE UpdateSequence[0x04]; //0x34
		BYTE HvStatusFlags[0x04]; //0x38
		BYTE ConsoleTypeSeqAllow[0x04]; //0x3C
		BYTE RTOC[0x08]; //0x40
		BYTE HRMOR[0x08]; //0x48
		BYTE HvECCDigest[0x14]; //0x50
		BYTE CpuKeyDigest[0x14]; //0x64
		BYTE HvCertificate[0x80]; //0x78
		BYTE hvExAddr[0x02]; //0xF8
		BYTE HvDigest[0x06]; //0xFA
	} XE_KEYS_BUFFER, * PXE_KEYS_BUFFER;
	//=====================================================================================
	mkdir((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\xke\\", XboxKrnlVersion->Build).c_str());
	xbox::utilities::DbgOut("mkdir: dump xke\n");
	//=====================================================================================
	mkdir((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\Salts\\", XboxKrnlVersion->Build).c_str());
	xbox::utilities::DbgOut("mkdir: dump Salts\n");
	//=========================================================
	MemoryBuffer mbHV;
	xbox::utilities::readFile((char*)xbox::utilities::va("Usb:\\challenge\\challenge-%i.bin", XboxKrnlVersion->Build).c_str(), mbHV);
	DWORD Size = mbHV.GetDataLength();
	//=========================================================
	BYTE* Data = (BYTE*)XPhysicalAlloc(Size, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(Data, 0, Size);
	memcpy(Data, mbHV.GetData(), Size);
	//=========================================================
	typedef DWORD(*XAMEXECUTECHALLENGE)(PBYTE challenge, DWORD chalPageSize, PBYTE salt, DWORD saltSize, PVOID chalResp, DWORD respSize);
	XAMEXECUTECHALLENGE XamExecuteChallenge = (XAMEXECUTECHALLENGE)xbox::utilities::resolveFunction("xam.xex", 0x1C8);
	//=========================================================
	xbox::utilities::DbgOut("running challenges and generating data\n");
	for (int i = 0; i <= 255; i++) {
		xbox::utilities::DbgOut("start Dumping (%i)\n", i);
		BYTE pSalt[0x10];
		memset(pSalt, 0, 0x10);
		PBYTE Salt = xbox::Challenge::FillBuffer::GetHVSalts(i);
		memcpy(pSalt, Salt, 0x10);

		BYTE Buffer0[0x100];
		memset(Buffer0, 0, 0x100);

		xbox::utilities::DbgOut(" - call		XamExecuteChallenge (%i)\n", i);
		xbox::utilities::DbgOut(" - HVSalt 0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);

		XamExecuteChallenge((PBYTE)Data, 0x000003F0, pSalt, 0x00000010, Buffer0, 0x00000100);
		XE_KEYS_BUFFER* Buffer = (XE_KEYS_BUFFER*)(Buffer0 - 0x20);

		BYTE Salt2[0x02];
		xbox::Hvx::HvPeekBytes(0x800002000001F810LL, Salt2, 0x02);

		BYTE ECCSalt[0x02];
		memcpy(ECCSalt, Salt2, 0x02);
		xbox::utilities::DbgOut(" - ECCSalt 0x%02X%02X						(%i)\n", ECCSalt[0], ECCSalt[1], i);

		xbox::utilities::DbgOut(" - HvMagic 0x%02X%02X						(%i)\n", Buffer->HvMagic[0], Buffer->HvMagic[1], i);
		xbox::utilities::DbgOut(" - HvVersion 0x%02X%02X					(%i)\n", Buffer->HvVersion[0], Buffer->HvVersion[1], i);
		xbox::utilities::DbgOut(" - HvQfe 0x%02X%02X						(%i)\n", Buffer->HvQfe[0], Buffer->HvQfe[1], i);
		xbox::utilities::DbgOut(" - BldrFlags 0x%02X%02X					(%i)\n", Buffer->BldrFlags[0], Buffer->BldrFlags[1], i);
		xbox::utilities::DbgOut(" - BaseKernelVersion 0x%02X%02X%02X%02X	(%i)\n", Buffer->BaseKernelVersion[0], Buffer->BaseKernelVersion[1], Buffer->BaseKernelVersion[2], Buffer->BaseKernelVersion[3], i);
		xbox::utilities::DbgOut(" - UpdateSequence 0x%02X%02X%02X%02X		(%i)\n", Buffer->UpdateSequence[0], Buffer->UpdateSequence[1], Buffer->UpdateSequence[2], Buffer->UpdateSequence[3], i);
		xbox::utilities::DbgOut(" - HvStatusFlags 0x%02X%02X%02X%02X		(%i)\n", Buffer->HvStatusFlags[0], Buffer->HvStatusFlags[1], Buffer->HvStatusFlags[2], Buffer->HvStatusFlags[3], i);
		xbox::utilities::DbgOut(" - ConsoleTypeSeqAllow 0x%02X%02X%02X%02X	(%i)\n", Buffer->ConsoleTypeSeqAllow[0], Buffer->ConsoleTypeSeqAllow[1], Buffer->ConsoleTypeSeqAllow[2], Buffer->ConsoleTypeSeqAllow[3], i);
		xbox::utilities::DbgOut(" - HvECCDigest %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X (%i) \n", Buffer->HvECCDigest[0], Buffer->HvECCDigest[1], Buffer->HvECCDigest[2], Buffer->HvECCDigest[3], Buffer->HvECCDigest[4], Buffer->HvECCDigest[5], Buffer->HvECCDigest[6], Buffer->HvECCDigest[7], Buffer->HvECCDigest[8], Buffer->HvECCDigest[9], Buffer->HvECCDigest[10], Buffer->HvECCDigest[11], Buffer->HvECCDigest[12], Buffer->HvECCDigest[13], Buffer->HvECCDigest[14], Buffer->HvECCDigest[15], i);
		xbox::utilities::DbgOut(" - hvExAddr 0x%02X%02X						(%i)\n", Buffer->hvExAddr[0], Buffer->hvExAddr[1], i);
		xbox::utilities::DbgOut(" - HvDigest %02X%02X%02X%02X%02X%02X		(%i)\n", Buffer->HvDigest[0], Buffer->HvDigest[1], Buffer->HvDigest[2], Buffer->HvDigest[3], Buffer->HvDigest[4], Buffer->HvDigest[5], Buffer->HvDigest[6], i);

		BYTE DUMP[0x70];
		memset(DUMP, 0, 0x70);
		memcpy(DUMP, pSalt, 0x10);
		memset(DUMP + 0x10, 0, 0x10);
		memset(DUMP + 0x20, 0, 0x10);
		memcpy(DUMP + 0x20, ECCSalt, 0x02);
		memset(DUMP + 0x30, 0, 0x10);
		memcpy(DUMP + 0x30, Buffer->hvExAddr, 0x02);
		memcpy(DUMP + 0x3A, Buffer->HvDigest, 0x06);
		memcpy(DUMP + 0x50, Buffer->HvECCDigest, 0x14);
		xbox::utilities::DumpFile(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\Salts\\0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X.bin", XboxKrnlVersion->Build, pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), DUMP, 0x70);

		BYTE* xke = (BYTE*)XPhysicalAlloc(0x100, MAXULONG_PTR, NULL, PAGE_READWRITE);
		memset(xke, 0, 0x100);
		memcpy(xke, Buffer, 0x100);
		xbox::utilities::DumpFile(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\xke\\0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X.bin", XboxKrnlVersion->Build, pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), xke, 0x100);
		XPhysicalFree(xke);

		xbox::utilities::DbgOut(" - File Dumped xke File (%i)\n", i);
		Sleep(100);
		xbox::utilities::DbgOut(" - Done (%i)\n", i);
	}
	//=========================================================
	XPhysicalFree(Data);
	//=========================================================
}
//=========================================================================================
void setHV0(BYTE* HV, QWORD qAddress, DWORD Address, DWORD Size) {

	xbox::utilities::DbgOut("setHV0: 0x%04X, 0x%02X\n", Address, Size);
	BYTE* Data = (BYTE*)XPhysicalAlloc(Size, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(Data, 0, Size);
	memcpy(Data, HV + Address, Size);
	xbox::Hvx::HvPokeBytes(qAddress + Address, Data, Size);
	XPhysicalFree(Data);
}
//=========================================================================================
void cleaningHV(BYTE* SystemHV, BYTE* CleanHV) {
	
	setHV0(CleanHV,	0x8000010000000000, 0x34, 0x40);
	setHV0(CleanHV, 0x8000010000000000, 0x40, 0x30);

	setHV0(SystemHV, 0x8000010000000000, 0x54, 0x10);
	setHV0(SystemHV, 0x8000010000000000, 0x77, 0x02);

	setHV0(CleanHV, 0x8000010000000000, 0x78, 0xFF88);
	setHV0(CleanHV, 0x8000010200000000, 0x100C0, 0x40);
	setHV0(CleanHV,	0x8000010200000000, 0x10350, 0x30);

	setHV0(CleanHV, 0x8000010200000000, 0x15E00, 0x80);
	setHV0(CleanHV,	0x8000010200000000, 0x15FD0, 0x04);
	setHV0(CleanHV,	0x8000010200000000, 0x16280, 0x40);
	setHV0(CleanHV,	0x8000010200000000, 0x162A0, 0x16);
	setHV0(CleanHV,	0x8000010200000000, 0x16EA0, 0x60);
	setHV0(CleanHV,	0x8000010200000000, 0x169DE, 0x01);
	setHV0(CleanHV,	0x8000010200000000, 0x16A37, 0x01);

	setHV0(SystemHV, 0x8000010200000000, 0x16710, 0x10);
	setHV0(SystemHV, 0x8000010200000000, 0x16980, 0x102);
	setHV0(SystemHV, 0x8000010200000000, 0x16B90, 0x10);
	setHV0(SystemHV, 0x8000010200000000, 0x16E98, 0x04);

	setHV0(CleanHV, 0x8000010400000000, 0x20000, 0xFFFF);
	setHV0(CleanHV, 0x8000010600000000, 0x30000, 0xFFFF);
}
//=========================================================================================
void DirtyHV(BYTE* SystemHV) {
	setHV0(SystemHV, 0x8000010000000000, 0x00000, 0xFFFF);
	setHV0(SystemHV, 0x8000010200000000, 0x10000, 0xFFFF);
	setHV0(SystemHV, 0x8000010400000000, 0x20000, 0xFFFF);
	setHV0(SystemHV, 0x8000010600000000, 0x30000, 0xFFFF);
}
//=========================================================================================
BOOL FindPaths() {
	//=========================================================
	mkdir("Usb:\\100F0\\dump\\");
	mkdir(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\", XboxKrnlVersion->Build).c_str());
	mkdir(xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\", XboxKrnlVersion->Build).c_str());
	xbox::utilities::DbgOut("Version %i \n", XboxKrnlVersion->Build);
	xbox::utilities::DbgOut("Generate: Start\n");
	//=========================================================
	BYTE* SystemHV = (BYTE*)XPhysicalAlloc(0x40000, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(SystemHV, 0, 0x40000);
	xbox::Hvx::HvPeekBytes(0x8000010000000000, SystemHV, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x8000010200010000, SystemHV + 0x10000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x8000010400020000, SystemHV + 0x20000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x8000010600030000, SystemHV + 0x30000, 0xFFFF);
	//=========================================================
	MemoryBuffer mbHV;
	xbox::utilities::readFile(xbox::utilities::va("Usb:\\100F0\\HV-base-%i.bin", XboxKrnlVersion->Build).c_str(), mbHV);
	BYTE* CleanHV = (BYTE*)XPhysicalAlloc(mbHV.GetDataLength(), MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(CleanHV, 0, mbHV.GetDataLength());
	memcpy(CleanHV, mbHV.GetData(), mbHV.GetDataLength());
	//=========================================================
	cleaningHV(SystemHV, CleanHV);
	//=========================================================
	xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010000000000, 0x200);
	xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010200010000, 0x200);
	xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010400020000, 0x200);
	xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010600030000, 0x200);
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\Cache0.bin", XboxKrnlVersion->Build).c_str());
	DumpHV("HV0");
	//=========================================================
	xbox::Hvx::HvProc(xbox::Hvx::sub2210, 0);
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\Cache1.bin", XboxKrnlVersion->Build).c_str());
	DumpHV("HV1");
	//=========================================================
	BYTE* dSalt2 = (BYTE*)XPhysicalAlloc(0x30, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(dSalt2, 0, 0x30);
	memcpy(dSalt2, SystemHV + 0x100C0, 0x30);
	xbox::utilities::DumpFile(xbox::utilities::va("Usb:\\100F0\\100C0-%i.bin", XboxKrnlVersion->Build).c_str(), dSalt2, 0x30);
	XPhysicalFree(dSalt2);
	//=========================================================
	BYTE* dSalt3 = (BYTE*)XPhysicalAlloc(0x10, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memset(dSalt3, 0, 0x10);
	xbox::Hvx::HvPeekBytes(0x00000102000100F0LL, dSalt3, 0x10);
	xbox::utilities::DumpFile(xbox::utilities::va("Usb:\\100F0\\100F0-%i.bin", XboxKrnlVersion->Build).c_str(), dSalt3, 0x10);
	XPhysicalFree(dSalt3);
	//=========================================================
	setHV0(SystemHV, 0x8000010200000000, 0x100C0, 0x30);
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\Cache2.bin", XboxKrnlVersion->Build).c_str());
	DumpHV("HV2");
	//=========================================================
	memset(CleanHV, 0, 0x40000);
	xbox::Hvx::HvPeekBytes(0, CleanHV, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010200010000, CleanHV + 0x10000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010400020000, CleanHV + 0x20000, 0xFFFF);
	xbox::Hvx::HvPeekBytes(0x0000010600030000, CleanHV + 0x30000, 0xFFFF);
	//=========================================================
	PBYTE pbHv = (PBYTE)XPhysicalAllocM(0x40000);
	QWORD pbHvReal = 0x8000000000000000ULL | (DWORD)MmGetPhysicalAddress(pbHv);
	ZeroMemory(pbHv, 0x40000);
	memcpy(pbHv, CleanHV, 0x40000);
	//=========================================================
	DumpKeys((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\keys.bin", XboxKrnlVersion->Build).c_str());
	xbox::utilities::DbgOut("Generate: DumpKeys Keys.bin\n");
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\Cache.bin", XboxKrnlVersion->Build).c_str());
	xbox::utilities::DbgOut("Generate: DumpSRAM Cache.bin\n");
	//=========================================================
	DumpHV("HV");
	xbox::utilities::DbgOut("Generate: DumpHV HV.bin\n");
	//=========================================================
	RunChallenges();
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\Cache3.bin", XboxKrnlVersion->Build).c_str());
	DumpHV("HV3");
	//=========================================================
	DirtyHV(SystemHV);
	//=========================================================
	DumpSRAM((char*)xbox::utilities::va("Usb:\\100F0\\dump\\%i\\test\\Cache_Dirty.bin", XboxKrnlVersion->Build).c_str());
	DumpHV("HV1_Dirty");
	//=========================================================
	return TRUE;
}
//=========================================================================================
BOOL Initialize() {
	xbox::utilities::MountPath("Usb:\\", "\\Device\\Mass0");

	xbox::Hvx::InitializeHvProc();
	xbox::utilities::DbgOut("Start: InitializeHvProc\n");
	xbox::Hvx::InitializeHvHash();
	xbox::utilities::DbgOut("Start: InitializeHvHash\n");
	xbox::Hvx::InitializeHvPeekPoke();
	xbox::utilities::DbgOut("Start: InitializeHvPeekPoke\n");
	
	if (!FindPaths()) {
		return FALSE;
	}
	return TRUE;
}
//=========================================================================================
BOOL APIENTRY DllMain(HANDLE Handle, DWORD Reason, PVOID Reserved){
	if (Reason == DLL_PROCESS_ATTACH) {
		global::modules::client = Handle;
		if (XamLoaderGetDvdTrayState() == DVD_TRAY_STATE_OPEN) {
			return FALSE;
		}

		if (!Initialize()) {
			return FALSE;
		}
	}
	return TRUE;
}
//=========================================================================================