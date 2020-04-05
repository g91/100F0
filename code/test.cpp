


/*
		extern BYTE ChalKey[] = {
			0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x04, 0xD0, 0x55, 0x50, 0x79, 0x19, 0x95, 0x27,
			0x78, 0x89, 0x97, 0x08, 0xDE, 0x24, 0xD1, 0xED, 0xB1, 0xEA, 0xE5, 0x48,
			0xAC, 0x1A, 0xC3, 0xC8, 0x29, 0x45, 0xB0, 0x16, 0x9B, 0xEF, 0x78, 0x8F,
			0xEF, 0x26, 0x9D, 0x54, 0x59, 0x95, 0x2D, 0x25, 0xA5, 0xAC, 0xA3, 0xA6,
			0x94, 0x45, 0xE5, 0x42, 0x2E, 0x39, 0x88, 0x0C, 0x3C, 0xAE, 0xEB, 0xFD,
			0x53, 0x3A, 0xE9, 0x70, 0x43, 0xEA, 0xD1, 0xD1, 0x78, 0xCE, 0xED, 0x1C,
			0xE5, 0xFD, 0x0F, 0x80, 0x94, 0x6F, 0x4F, 0xFF, 0xAD, 0x45, 0x88, 0xCF,
			0x22, 0x4C, 0x56, 0xDE, 0x03, 0xE2, 0x46, 0x2F, 0x19, 0xB8, 0x2C, 0xD0,
			0xD7, 0xE9, 0x64, 0xB2, 0x68, 0x0C, 0x40, 0xF5, 0x4F, 0xDA, 0x80, 0x8F,
			0x71, 0xA9, 0x64, 0xA4, 0x15, 0x53, 0x6E, 0x2B, 0x49, 0x44, 0x55, 0xCB,
			0x05, 0x17, 0x3F, 0x66, 0xE1, 0x32, 0x2F, 0x1D, 0xE9, 0x2A, 0xD6, 0x4B
		};*/
//
//void MakeHvHashes(QWORD qwHvAddress, DWORD cCount) {
//	if ((cCount << 7) > 0x10000)
//		return;
//
//	DWORD szCacheBlock = 0x80;
//	DWORD cbBytes = cCount << 7;
//	DWORD szCacheBlockCount = cCount;
//	DWORD cbHashes = cCount << 1;
//
//	QWORD qwHvAddy = qwHvAddress;
//	QWORD qwHvSRAM = ProtToSRAM(qwHvAddy);
//
//	PBYTE pbHvBuf = (PBYTE)XPhysicalAllocM(cbBytes);
//	ZeroMemory(pbHvBuf, cbBytes);
//	Hvx::HvPeekBytes(qwHvAddy, pbHvBuf, cbBytes);
//	xbox::utilities::DbgOut("HV Address: %016llX, HV SRAM Address: %016llX, Bytes: %X, Cacheline Count: %X\n", qwHvAddy, qwHvSRAM, cbBytes, szCacheBlockCount);
//
//
//	PBYTE pbHvHashes = (PBYTE)XPhysicalAllocM(cbHashes);
//	ZeroMemory(pbHvHashes, cbHashes);
//	Hvx::HvPeekBytes(qwHvSRAM, pbHvHashes, cbHashes);
//
//	BYTE bBufKey = 0x3B;
//	PBYTE pbBuf = (PBYTE)XPhysicalAlloc(cbBytes, MAXULONG_PTR, 0x10000, PAGE_READWRITE);
//	ZeroMemory(pbBuf, cbBytes);
//	QWORD pbBufReal = 0x8000000000000000ULL | (DWORD)MmGetPhysicalAddress(pbBuf);
//	QWORD pbBufProt = Hvx::HvProc(Hvx::HvpRelocatePhysicalToProtected, 3, pbBufReal, cbBytes, bBufKey);
//	QWORD pbBufSRAM = ProtToSRAM(pbBufProt);
//	xbox::utilities::DbgOut("Buffer Real Address: %016llX, Buffer Protected Address: %016llX, Buffer SRAM Address: %016llX, Buffer Key: %X\n", pbBufReal, pbBufProt, pbBufSRAM, bBufKey);
//	Hvx::HvPokeBytes(pbBufProt, pbHvBuf, cbBytes);
//	PBYTE pbBufHashes = (PBYTE)XPhysicalAllocM(cbHashes);
//	ZeroMemory(pbBufHashes, cbHashes);
//	Hvx::HvPeekBytes(pbBufSRAM, pbBufHashes, cbHashes);
//	//printf("Buf Hashes (first 16 bytes): ");
//	//arrPrintXln(pbBufHashes, 0x10);
//
//	Hvx::HvProc(Hvx::HvpInvalidateCachelines, 2, pbBufProt, cbBytes);
//	Hvx::HvProc(Hvx::HvpZeroCacheLines, 2, pbBufReal, szCacheBlockCount);
//
//	XPhysicalFree(pbHvBuf);
//	XPhysicalFree(pbBuf);
//	XPhysicalFree(pbHvHashes);
//	XPhysicalFree(pbBufHashes);
//}
//

//namespace data {
	//		KEY_VAULT buffer;
	//		DWORD updSeqFlags;
	//		DWORD cTypeFlags;
	//		DWORD hardwareFlags;
	//		DWORD hvStatusFlags = 0x23289D3;
	//		DWORD bldrFlags = 0xD83E;
	//		BYTE consoleType;
	//		BYTE SerialByte;
	//		BYTE cpuKey[0x10];
	//		BYTE cpuKeyDigest[0x14];
	//		BYTE keyvaultDigest[0x14];
	//		BOOL fcrtRequired = FALSE;
	//		BOOL type1KV = FALSE;
	//		BYTE partnumber[0x08];
	//		BYTE kvsignature[0x100];
	//		BOOL crl = FALSE;
	//	}

	//	PBYTE GetKeyVault(){
	//		QWORD KVAddress = xbox::Hvx::HvPeekQWORD(0x0000010200016240);
	//		if (xbox::Hvx::HvPeekBytes(KVAddress, &data::buffer, sizeof(KEY_VAULT)) != S_OK) return 0;
	//		return (PBYTE)&data::buffer;
	//	}

	//	BYTE char2byte(char input) {
	//		if (input >= '0' && input <= '9')
	//			return input - '0';
	//		if (input >= 'A' && input <= 'F')
	//			return input - 'A' + 10;
	//		if (input >= 'a' && input <= 'f')
	//			return input - 'a' + 10;
	//		return 0;
	//	}

	//	BOOL XeKeysPkcs1Verify(const BYTE* pbHash, const BYTE* pbSig, XECRYPT_RSA* pRsa) {
	//		BYTE scratch[256];
	//		DWORD val = pRsa->cqw << 3;
	//		if (val <= 0x200) {
	//			XeCryptBnQw_SwapDwQwLeBe((QWORD*)pbSig, (QWORD*)scratch, val >> 3);
	//			if (XeCryptBnQwNeRsaPubCrypt((QWORD*)scratch, (QWORD*)scratch, pRsa) == 0) return FALSE;
	//			XeCryptBnQw_SwapDwQwLeBe((QWORD*)scratch, (QWORD*)scratch, val >> 3);
	//			return XeCryptBnDwLePkcs1Verify((const PBYTE)pbHash, scratch, val);
	//		}
	//		else return FALSE;
	//	}

	//	//HRESULT setupSpecialValues(DWORD updSeq) {
	//	//	data::fcrtRequired = (xbox::utilities::data::buffer.OddFeatures & ODD_POLICY_FLAG_CHECK_FIRMWARE) != 0;
	//	//	BYTE moboSerialByte = (((char2byte(data::buffer.ConsoleCertificate.ConsolePartNumber[2]) << 4) & 0xF0) | ((char2byte(data::buffer.ConsoleCertificate.ConsolePartNumber[3]) & 0x0F)));

	//	//	if (data::fcrtRequired) {
	//	//		data::hvStatusFlags |= 0x1000000;
	//	//		data::bldrFlags = 0xD81E;
	//	//	}

	//	//	data::SerialByte = moboSerialByte;
	//	//	if (moboSerialByte < 0x10) {
	//	//		data::consoleType = 0;
	//	//		data::cTypeFlags = 0x010B0FFB;
	//	//	}
	//	//	else if (moboSerialByte < 0x14) {
	//	//		data::consoleType = 1;
	//	//		data::cTypeFlags = 0x010B0524;
	//	//	}
	//	//	else if (moboSerialByte < 0x18) {
	//	//		data::consoleType = 2;
	//	//		data::cTypeFlags = 0x010C0AD8;
	//	//	}
	//	//	else if (moboSerialByte < 0x52) {
	//	//		data::consoleType = 3;
	//	//		data::cTypeFlags = 0x010C0AD0;
	//	//	}
	//	//	else if (moboSerialByte < 0x58) {
	//	//		data::consoleType = 4;
	//	//		data::cTypeFlags = 0x0304000D;
	//	//	}
	//	//	else {
	//	//		data::consoleType = 5;
	//	//		data::cTypeFlags = 0x0304000E;
	//	//	}

	//	//	data::hardwareFlags = (XboxHardwareInfo->Flags & 0x0FFFFFFF) | ((data::consoleType & 0xF) << 28);
	//	//	data::hardwareFlags = data::hardwareFlags & ~0x20;
	//	//	data::updSeqFlags = updSeq;
	//	//	return S_OK;
	//	//}


	//	#define hvKvPtrDev      0x00000102000162E0
	//	#define hvKvPtrRetail   0x00000002000163C0
	//	BYTE RetailRoamableObfuscationKey[0x10] = { 0xE1, 0xBC, 0x15, 0x9C, 0x73, 0xB1, 0xEA, 0xE9, 0xAB, 0x31, 0x70, 0xF3, 0xAD, 0x47, 0xEB, 0xF3 };
	//	BOOL SetKeyVault() {
	//		xbox::utilities::DbgOut("SetKeyVault #1 ");

	//		BOOL KVFound = FALSE;
	//		MemoryBuffer mbCPU, mbKV;
	//		if (fileExists(PATH_CPU)) {
	//			if (!readFile(PATH_CPU, mbCPU)) {
	//				xbox::utilities::DbgOut("CPUKey #FALSE ");
	//				return FALSE;
	//			}
	//		}

	//		memcpy(data::cpuKey, (mbCPU.GetDataLength() == 0x10) ? mbCPU.GetData() : global::challenge::cpukey, 0x10);
	//		XeCryptSha(data::cpuKey, 0x10, 0, 0, 0, 0, data::cpuKeyDigest, 0x14);
	//		memcpy((PVOID)0x8E03AA30, data::cpuKeyDigest, 0x10);


	//		if (KVFound = fileExists(PATH_KV)) {
	//			if (!readFile(PATH_KV, mbKV)) {
	//				xbox::utilities::DbgOut("KV #FALSE ");
	//				return FALSE;
	//			}
	//		}

	//		memcpy(&data::buffer, KVFound ? mbKV.GetData() : GetKeyVault(), sizeof(KEY_VAULT));

	//		XECRYPT_HMACSHA_STATE HMACSHA = { 0 };
	//		XeCryptHmacShaInit(&HMACSHA, data::cpuKey, 0x10);
	//		XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&data::buffer.OddFeatures, 0xD4);
	//		XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&data::buffer.DvdKey, 0x1CF8);
	//		XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&data::buffer.CardeaCertificate, 0x2108);
	//		XeCryptHmacShaFinal(&HMACSHA, data::keyvaultDigest, 0x14);
	//		memcpy((PVOID)0x8E03AA40, data::keyvaultDigest, 0x14);

	//		data::type1KV = TRUE;
	//		for (DWORD x = 0; x < 0x100; x++) {
	//			if (data::buffer.KeyVaultSignature[x] != NULL) {
	//				data::type1KV = FALSE;
	//			}
	//		}

	///*		if (!XeKeysPkcs1Verify(data::keyvaultDigest, data::buffer.KeyVaultSignature, (XECRYPT_RSA*)masterKey))
	//			xbox::utilities::log("The cpu key provided is not for this keyvault.");*/

	//		data::fcrtRequired = ((data::buffer.OddFeatures & ODD_POLICY_FLAG_CHECK_FIRMWARE) != 0);

	//	    xbox::utilities::setMemory((PVOID)0x8E03A000, &data::buffer.ConsoleCertificate, 0x1A8);
	//		xbox::utilities::setMemory((PVOID)0x8E038020, &data::buffer.ConsoleCertificate.ConsoleId.abData, 5);

	//		memcpy((PVOID)0x8E03A000, &data::buffer.ConsoleCertificate, 0x1A8);
	//		memcpy((PVOID)0x8E038020, &data::buffer.ConsoleCertificate.ConsoleId.abData, 5);
	//		if (global::isDevkit) xbox::utilities::setMemory((BYTE*)((*(DWORD*)0x81D6B198) + 0x30BC), &data::buffer.ConsoleCertificate, 0x1A8);
	//		XeCryptSha((PBYTE)0x8E038014, 0x3EC, 0, 0, 0, 0, (PBYTE)0x8E038000, 0x14);

	//		BYTE newHash[XECRYPT_SHA_DIGEST_SIZE];
	//		XeCryptSha((BYTE*)0x8E038014, 0x3EC, NULL, NULL, NULL, NULL, newHash, XECRYPT_SHA_DIGEST_SIZE);
	//		xbox::utilities::setMemory((PVOID)0x8E038000, newHash, XECRYPT_SHA_DIGEST_SIZE);

	//		BYTE sataUpdateHash[0x14];
	//		XeCryptSha((BYTE*)0x8E038794, 0x8C, 0, 0, 0, 0, sataUpdateHash, 0x14);
	//		xbox::utilities::setMemory((PVOID)0x8E038794, sataUpdateHash, 0x14);

	//		xbox::utilities::setMemory((PVOID)0x8E03AA30, data::cpuKeyDigest, 0x10);
	//		xbox::utilities::setMemory((PVOID)0x8E03AA40, data::keyvaultDigest, 0x10);
	//		//xbox::utilities::setMemory((PVOID)0x8E03AA50, kvFuseKey, 0x10);
	//		QWORD KVAddress = (global::isDevkit) ? xbox::Hvx::HvPeekQWORD(hvKvPtrDev) : xbox::Hvx::HvPeekQWORD(hvKvPtrRetail);
	//		if (xbox::Hvx::HvPeekBytes(KVAddress + 0xD0, &data::buffer.ConsoleObfuscationKey, 0x40) != S_OK) return FALSE;
	//		memcpy(&data::buffer.RoamableObfuscationKey, RetailRoamableObfuscationKey, 0x10);
	//		if (xbox::Hvx::HvPokeBytes(KVAddress, &data::buffer, sizeof(KEY_VAULT)) != S_OK) return FALSE;

	//		BYTE currentMacAddress[6];
	//		BYTE spoofedMacAddress[6] = {
	//			0xFF, 0xFF, 0xFF,
	//			data::buffer.ConsoleCertificate.ConsoleId.asBits.MacIndex3,
	//			data::buffer.ConsoleCertificate.ConsoleId.asBits.MacIndex4,
	//			data::buffer.ConsoleCertificate.ConsoleId.asBits.MacIndex5
	//		};

	//		if ((XboxHardwareInfo->Flags & 0xF0000000) > 0x40000000) {
	//			spoofedMacAddress[0] = 0x7C;
	//			spoofedMacAddress[1] = 0xED;
	//			spoofedMacAddress[2] = 0x8D;
	//		} else {
	//			spoofedMacAddress[0] = 0x00;
	//			spoofedMacAddress[1] = 0x22;
	//			spoofedMacAddress[2] = 0x48;
	//		}

	//		memcpy(global::challenge::spoofedMacAddress, spoofedMacAddress, 6);
	//		if (NT_SUCCESS(ExGetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, currentMacAddress, 6, NULL))) {
	//			if (memcmp(currentMacAddress, spoofedMacAddress, 6) != 0) {
	//				if (NT_SUCCESS(ExSetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, spoofedMacAddress, 6))) {
	//					XamCacheReset(XAM_CACHE_ALL);
	//					HalReturnToFirmware(HalFatalErrorRebootRoutine);
	//				}
	//			}
	//		}


	//		//DWORD temp = 0;
	//		//XeCryptSha(spoofedMacAddress, 6, NULL, NULL, NULL, NULL, (BYTE*)& temp, 4);
	//		//if (setupSpecialValues(temp & ~0xFF) != S_OK) {
	//		//	return E_FAIL;
	//		//}

	//		//SetLiveBlock(TRUE);
	//		//if (!XamCacheReset(XAM_CACHE_TICKETS)) return FALSE;
	//		return TRUE;
	//	}

////=====================================================================================
//if (!global::isDevkit) {
//	*(PDWORD)((DWORD)xbox::utilities::resolveFunction("xam.xex", 0x1C8) + 0x16C) = 0x60000000; // MmGetPhysicalAddress
//	//BYTE RETAIL_GOLD_PATCHES[0x40] =
//	//{
//	//	0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x01, 0x39, 0x60, 0x00, 0x01,
//	//	0x00, 0x00, 0x01, 0xA0, 0x00, 0x00, 0x00, 0x01, 0x39, 0x60, 0x00, 0x01,
//	//	0x00, 0x00, 0x01, 0xAC, 0x00, 0x00, 0x00, 0x01, 0x39, 0x60, 0x00, 0x01,
//	//	0x00, 0x00, 0x01, 0xB4, 0x00, 0x00, 0x00, 0x01, 0x39, 0x60, 0x00, 0x01,
//	//	0x00, 0x00, 0x01, 0xBC, 0x00, 0x00, 0x00, 0x01, 0x39, 0x60, 0x00, 0x01,
//	//	0xFF, 0xFF, 0xFF, 0xFF
//	//};
//	//Tools::ApplyOffsetPatches(Tools::ResolveFunction(MODULE_XAM, 0x212), Patches::RETAIL_GOLD_PATCHES);
//	DWORD XamUserCheckPrivilege = (DWORD)xbox::utilities::resolveFunction("xam.xex", 0x212); // Gold Spoofing
//	*(int*)(XamUserCheckPrivilege + 0x140) = 0x39600001; // Gold Spoofing
//	*(int*)(XamUserCheckPrivilege + 0x1A0) = 0x39600001; // Gold Spoofing
//	*(int*)(XamUserCheckPrivilege + 0x1AC) = 0x39600001; // Gold Spoofing
//	*(int*)(XamUserCheckPrivilege + 0x1B4) = 0x39600001; // Gold Spoofing
//	*(int*)(XamUserCheckPrivilege + 0x1BC) = 0x39600001; // Gold Spoofing
//}
//=====================================================================================



////				//=========================================================
//MemoryBuffer mbHV;
//xbox::utilities::readFile("Usb:\\HV.bin", mbHV);
////=========================================================
//cleanhv(mbHV);
//xbox::utilities::DbgOut("GenerateSignature: cleanhv\n");
//Sleep(50);
////=========================================================
//cleanhv2(mbHV);
//xbox::utilities::DbgOut("GenerateSignature: cleanhv2\n");
//Sleep(50);
////=========================================================
//cleanhv4(mbHV);
//xbox::utilities::DbgOut("GenerateSignature: cleanhv4\n");
//Sleep(50);
////=========================================================
//cleanhv6(mbHV);
//xbox::utilities::DbgOut("GenerateSignature: cleanhv6\n");
//Sleep(50);




	//=========================================================
			//QWORD zAddy[0xD] = {
			//	0x34000C, 			// HV 0x34-0x3F, 0xC bytes
			//	0x400030, 			// HV 0x40-0x6F, 0x30 bytes
			//	0x700004, 			// HV 0x70-0x73, 4 bytes
			//	0x780008, 			// HV 0x78-0x7F, 8 bytes
			//	0x8081FF, 			// SRAM 0x2-0x3FF, 0x3FE bytes ; HV 0x80-0xFFFF
			//	0x2000100C00040, 	// HV 0x100C0-0x100FF, 0x40 bytes
			//	0x2000103500030, 	// HV 0x10350-0x1037F, 0x30 bytes
			//	0x20001038080BE, 	// SRAM 0x40E-0x583, 0x176 bytes ; HV 0x10380-0x160FF
			//	0x2000162800040, 	// HV 0x16100-0x1613F, 0x40 bytes
			//	0x200016EA00060, 	// HV 0x16D20-0x16D7F, 0x60 bytes
			//	0x200016F008122, 	// SRAM 0x5B6-0x7FF, 0x24A bytes ; HV 0x16D80-0x1FFFF
			//	0x4000200008200, 	// SRAM 0x800-0xBFF, 0x400 bytes ; HV 0x20000-0x2FFFF
			//	0x6000300008200  	// SRAM 0xC00-0xFFF, 0x400 bytes ; HV 0x30000-0x3FFFF
			//};
			//=========================================================
	/*			0x000000034000C,
				0x0000000400030,
				0x0000000700004,
				0x0000000780008,
				0x00000008081FF,
				0x2000100C00040,
				0x2000103500030,
				0x20001038080BE,
				0x2000162800040,
				0x200016EA00060,
				0x200016F008122,
				0x4000200008200,
				0x6000300008200
*/
////=========================================================
//PBYTE pbBuf = (PBYTE)XPhysicalAlloc(0x40000, MAXULONG_PTR, 0x10000, PAGE_READWRITE);
//ZeroMemory(pbBuf, 0x40000);
////=========================================================
//xbox::Hvx::HvPeekBytes(0, LiveHV, 0xFFFF);
//xbox::Hvx::HvPeekBytes(0x0000010200010000, LiveHV + 0x10000, 0xFFFF);
//xbox::Hvx::HvPeekBytes(0x0000010400020000, LiveHV + 0x20000, 0xFFFF);
//xbox::Hvx::HvPeekBytes(0x0000010600030000, LiveHV + 0x30000, 0xFFFF);
////=========================================================
//PBYTE pbHv = (PBYTE)XPhysicalAllocM(0x40000);
//QWORD pbHvReal = 0x8000000000000000ULL | (DWORD)MmGetPhysicalAddress(pbHv);
//ZeroMemory(pbHv, 0x40000);
//memcpy(pbHv, LiveHV, 0x40000);
////=========================================================
//QWORD pbBufProt = Hvx::HvProc(Hvx::HvpRelocatePhysicalToProtected, 3, pbHvReal, 0x40000, 0x3E);
////=========================================================
//for (int i = 0; i < 0xD; i++)
//{
//	QWORD xAddy = zAddy[i];
//	if (xAddy & 0x8000){
//		xbox::utilities::DbgOut("\nxAddy: %016llX\n", xAddy);
//		xbox::utilities::DbgOut("\nHvBuf: %016llX\n", pbHvReal);
//		PBYTE pbBufHash = (PBYTE)XPhysicalAllocM((xAddy & 0x3FF) << 1);
//		ZeroMemory(pbBufHash, (xAddy & 0x3FF) << 1);
//		QWORD pbBufHashReal = 0x8000000000000000ULL | (DWORD)MmGetPhysicalAddress(pbBufHash);

//		xbox::utilities::DbgOut("BufHashReal: %016llX\n", pbBufHashReal);

//		QWORD ret = Hvx::HvHash(xAddy, pbBufProt, pbHvReal, pbBufHashReal);

//		//printf("Block at HV+%X, With Key: %04X\n", (xAddy >> 16) & 0x3FFFF, Hvx::HvPeekWORD(ProtToSRAM(xAddy >> 16)));
//		//printf("Block at HV+%X, Without Key: %04X\n", (xAddy >> 16) & 0x3FFFF, SoCHash((pbHv + ((xAddy >> 16) & 0x3FFFF))));
//		//printf("Block at HV+%X, Without Key: %04X\n", (xAddy >> 16) & 0x3FFFF, SoCHashBy16A((pbHv + ((xAddy >> 16) & 0x3FFFF))));
//		//printf("Hash Buffer: ");
//		//arrPrintXln(pbBufHash, 0x10);

//		XPhysicalFree(pbBufHash);
//	}
//}
////=========================================================
//Hvx::HvProc(Hvx::HvpInvalidateCachelines, 2, pbBufProt, 0x1000);

//Hvx::HvProc(Hvx::HvpZeroCacheLines, 2, pbHvReal, 0x1000);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, pbHvReal, 0x1000);
			//==============================================================
			//xbox::utilities::setLiveBlock(TRUE);
			//==============================================================
			//DumpSRAM("Client:\\pCache0.bin");
			//==============================================================
			//xbox::Hvx::InitializeHvProc();
			////==============================================================
			//Sleep(50);
			////==============================================================
			//PBYTE Signature = (PBYTE)XPhysicalAlloc(0x80, MAXULONG_PTR, 0, PAGE_READWRITE);
			//xbox::Hvx::HvPeekBytes(0x0000000200010040, Signature, 0x80);
			//memcpy(Challenge::Signature, Signature, 0x80);
			//==============================================================
			//PXE_KEYS_BUFFER resp = (PXE_KEYS_BUFFER)(Buffer + 0x20);
			//BYTE hvExAddr[0x02];
			//memcpy(hvExAddr, (PBYTE)resp->hvExAddr, 0x02);
			//BYTE hvExAddr[0x02] = { ((PBYTE)(resp->hvExAddr))[0x00], ((PBYTE)(resp->hvExAddr))[0x01] };
			//==============================================================
			//XeCryptRandom(Challenge::XeRand, 0x14);
			//sub_23918(Challenge::Signature, Challenge::Keys, Challenge::XeRand);
			//std::reverse(Challenge::Signature, Challenge::Signature + 0x40);
			//XeCryptBnQw_SwapDwQwLeBe((PQWORD)Challenge::Signature, (PQWORD)Challenge::Signature, 0x10);
			//XeCryptBnQwNeRsaPubCrypt((PQWORD)Challenge::Signature, (PQWORD)Challenge::Signature, (PXECRYPT_RSA)Challenge::ChalKey);
			//XeCryptBnQw_SwapDwQwLeBe((PQWORD)Challenge::Signature, (PQWORD)Challenge::Signature, 0x10);
			//==============================================================
			//0x0000010200010040
			//==============================================================
			//xbox::Hvx::HvPokeBytes(0x0000000200010040, Challenge::Signature, 0x80);
			//==============================================================
			//Sleep(500);
			////==============================================================
			//DumpSRAM("Client:\\pCache6.bin");
			////==============================================================
			//Sleep(500);
			////==============================================================
			////xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0, 0x200);
			////xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010000000000, 0x200);
			////xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010200010000, 0x200);
			////xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010400020000, 0x200);
			////xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010600030000, 0x200);
			////==============================================================







//
//	//			//=========================================================
//Hvx::HvProc(Hvx::sub2210, 0);
//DumpSRAM("Usb:\\dump\\pCache3.bin");
//xbox::utilities::DbgOut("GenerateSignature: sub2210\n");
//Sleep(50);

//				//=========================================================
//MakeHvHashes(0x0000000000000000, 0x200);
//MakeHvHashes(0x0000010000000000, 0x200);
//MakeHvHashes(0x0000010200010000, 0x200);
//MakeHvHashes(0x0000010400020000, 0x200);
//MakeHvHashes(0x0000010600030000, 0x200);
//xbox::utilities::DbgOut("GenerateSignature: MakeHvHashes\n");
//DumpSRAM("Usb:\\dump\\pCache2.bin");

//	//			//=========================================================
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000000000000000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000010000000000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000010200010000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000000200010000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000010400020000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000000400020000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000010600030000, 0x200);
//Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x0000000600030000, 0x200);
//DumpSRAM("Usb:\\dump\\pCache5.bin");
//


//VOID xebuildptch_hv() {
//	xbox::utilities::DbgOut("xebuildptch_hv: start\n");
//	xbox::Hvx::HvPokeDWORD(0x0000010000001880, 0x4800B513);
//	xbox::Hvx::HvPokeDWORD(0x00000100000011BC, 0x4800154E);
//	xbox::Hvx::HvPokeDWORD(0x000001000000154C, 0x38800007);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001550, 0x7C212078);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001554, 0x7C35EBA6);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001558, 0x480011C2);
//	xbox::Hvx::HvPokeDWORD(0x0000010000003120, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x000001000000A560, 0x38600001);
//	xbox::Hvx::HvPokeDWORD(0x000001000000A564, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006BB0, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006BB4, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C48, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C4C, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C98, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C9C, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D08, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D0C, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D58, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D5C, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x00000100000070BC, 0x38600001);
//	xbox::Hvx::HvPokeDWORD(0x0000010000007268, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072B4, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072C4, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072EC, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072F0, 0x39600001);
//	xbox::Hvx::HvPokeDWORD(0x000001000000813C, 0x48000030);
//	xbox::utilities::DbgOut("xebuildptch_hv: down\n");
//}
//
//VOID cleanhv(MemoryBuffer mbHV) {
//	xbox::utilities::DbgOut("cleanhv: start\n");
//
//	BYTE pB510[0x120];
//	memset(pB510, 0, 0x120);
//	xbox::Hvx::HvPokeBytes(0x000001000000B510, pB510, 0x120);
//	xbox::Hvx::HvPokeDWORD(0x0000010000000030, 0x00008000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000000F0, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000000F4, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000000F8, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x00000100000000FC, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001880, 0x4BFFEA59);
//	xbox::Hvx::HvPokeDWORD(0x00000100000011BC, 0x7C35EBA6);
//	xbox::Hvx::HvPokeDWORD(0x000001000000154C, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001550, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001554, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000001558, 0x00000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010000003120, 0x4BFFEB31);
//	xbox::Hvx::HvPokeDWORD(0x000001000000A560, 0x7D8802A6);
//	xbox::Hvx::HvPokeDWORD(0x000001000000A564, 0x48000299);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006BB0, 0x7D8802A6);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006BB4, 0xF981FFF8);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C48, 0x3D620001);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C4C, 0xA16B6A94);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C98, 0x7D8802A6);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006C9C, 0xF981FFF8);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D08, 0x3D620001);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D0C, 0xA16B6A94);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D58, 0x7D8802A6);
//	xbox::Hvx::HvPokeDWORD(0x0000010000006D5C, 0xF981FFF8);
//	xbox::Hvx::HvPokeDWORD(0x00000100000070BC, 0x4800431D);
//	xbox::Hvx::HvPokeDWORD(0x0000010000007268, 0x48004219);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072B4, 0x4BFF8F65);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072C4, 0x4BFF8F55);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072EC, 0x4BFF8F2D);
//	xbox::Hvx::HvPokeDWORD(0x00000100000072F0, 0x817D03B0);
//	xbox::Hvx::HvPokeDWORD(0x000001000000813C, 0x419A0028);
//	xbox::utilities::DbgOut("cleanhv: down\n");
//}
//
//VOID xebuildptch_hv2() {
//	xbox::utilities::DbgOut("xebuildptch_hv2: start\n");
//
//	xbox::Hvx::HvPokeDWORD(0x0000010200015FD0, 0x0000B564);
//	xbox::utilities::DbgOut("xebuildptch_hv2: down\n");
//}
//
//VOID cleanhv2(MemoryBuffer mbHV) {
//	xbox::utilities::DbgOut("cleanhv2: start\n");
//
//	xbox::Hvx::HvPokeDWORD(0x00000102000100F0, 0xD8D815C0);
//	xbox::utilities::DbgOut("cleanhv2: 0x00000102000100F0, 0xD8D815C0\n");
//	xbox::Hvx::HvPokeDWORD(0x00000102000100F4, 0x1FEF372B);
//	xbox::utilities::DbgOut("cleanhv2: 0x00000102000100F4, 0x1FEF372B\n");
//	xbox::Hvx::HvPokeDWORD(0x00000102000100F8, 0x8ACA4B23);
//	xbox::utilities::DbgOut("cleanhv2: 0x00000102000100F8, 0x8ACA4B23\n");
//	xbox::Hvx::HvPokeDWORD(0x00000102000100FC, 0xE449B79F);
//
//	xbox::utilities::DbgOut("cleanhv2: 0x00000102000100FC, 0xE449B79F\n");
//	//xbox::Hvx::HvPokeDWORD(0x0000010200015FD0, 0x00001CC8);
//	xbox::Hvx::HvPokeBytes(0x0000010400015FD0, mbHV.GetData() + 0x15FD0, 0x4);
//
//	//xbox::utilities::DbgOut("cleanhv2: 0x0000010200015FD0, 0x00001CC8\n");
//	//xbox::Hvx::HvPokeDWORD(0x00000102000162AC, 0x00000000);
//	//xbox::utilities::DbgOut("cleanhv2: 0x00000102000162AC, 0x00000000\n");
//	xbox::utilities::DbgOut("cleanhv2: down\n");
//}
//
//VOID xebuildptch_hv4() {
//	xbox::utilities::DbgOut("xebuildptch_hv4: start\n");
//
//	xbox::Hvx::HvPokeDWORD(0x0000010400024D58, 0x38600001);
//	xbox::Hvx::HvPokeDWORD(0x0000010400024D5C, 0x4E800020);
//	xbox::Hvx::HvPokeDWORD(0x00000104000264F0, 0x38600001);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B08, 0x2B3C0000);
//
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B0C, 0x419A0030);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B10, 0x2F030000);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B14, 0x409A0010);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B18, 0x388000F0);
//
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B1C, 0x48000018);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B20, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B24, 0x2B1D0000);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B28, 0x389F0440);
//
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B2C, 0x409A0008);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B30, 0x38800054);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B34, 0x7F83E378);
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B38, 0x4BFF65C1);
//
//	xbox::Hvx::HvPokeDWORD(0x0000010400029B3C, 0x3BE00000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002B778, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002CAE8, 0x38600000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002CDD8, 0x60000000);
//
//	xbox::Hvx::HvPokeDWORD(0x000001040002A30C, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002A310, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002AA80, 0x60000000);
//	xbox::Hvx::HvPokeDWORD(0x000001040002AA8C, 0x60000000);
//	xbox::utilities::DbgOut("xebuildptch_hv4: down\n");
//}
//
//VOID cleanhv4(MemoryBuffer mbHV) {
//	xbox::utilities::DbgOut("cleanhv4: start\n");
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400024D58, 0x7D8802A6);
//	xbox::Hvx::HvPokeBytes(0x0000010400024D58, mbHV.GetData() + 0x24D58, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400024D5C, 0xF981FFF8);
//	xbox::Hvx::HvPokeBytes(0x0000010400024D5C, mbHV.GetData() + 0x24D58, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x00000104000264F0, 0x480038DB);
//	xbox::Hvx::HvPokeBytes(0x00000104000264F0, mbHV.GetData() + 0x264F0, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B08, 0x2F030000);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B08, mbHV.GetData() + 0x29B08, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B0C, 0x409A0010);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B0C, mbHV.GetData() + 0x29B0C, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B10, 0x3FE0C000);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B10, mbHV.GetData() + 0x29B10, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B14, 0x63FF0221);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B14, mbHV.GetData() + 0x29B14, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B18, 0x48000028);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B18, mbHV.GetData() + 0x29B18, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B1C, 0x2B3C0000);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B1C, mbHV.GetData() + 0x29B1C, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B20, 0x419A001C);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B20, mbHV.GetData() + 0x29B20, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B24, 0x2B1D0000);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B24, mbHV.GetData() + 0x29B24, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B28, 0x389F0440);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B28, mbHV.GetData() + 0x29B28, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B2C, 0x409A0008);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B2C, mbHV.GetData() + 0x29B2C, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B30, 0x38800054);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B30, mbHV.GetData() + 0x29B30, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B34, 0x7F83E378);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B34, mbHV.GetData() + 0x29B34, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B38, 0x4BFF65C1);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B38, mbHV.GetData() + 0x29B38, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x0000010400029B3C, 0x3BE00000);
//	xbox::Hvx::HvPokeBytes(0x0000010400029B3C, mbHV.GetData() + 0x29B3C, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002B778, 0x419AFFB8);
//	xbox::Hvx::HvPokeBytes(0x000001040002B778, mbHV.GetData() + 0x2B778, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002CAE8, 0x48000889);
//	xbox::Hvx::HvPokeBytes(0x000001040002CAE8, mbHV.GetData() + 0x2CAE8, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002CDD8, 0x419AFFDC);
//	xbox::Hvx::HvPokeBytes(0x000001040002CDD8, mbHV.GetData() + 0x2CDD8, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002A30C, 0x2F030000);
//	xbox::Hvx::HvPokeBytes(0x000001040002A30C, mbHV.GetData() + 0x2A30C, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002A310, 0x409A00C0);
//	xbox::Hvx::HvPokeBytes(0x000001040002A310, mbHV.GetData() + 0x2A310, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002AA80, 0x4198022C);
//	xbox::Hvx::HvPokeBytes(0x000001040002AA80, mbHV.GetData() + 0x2AA80, 0x4);
//
//	//xbox::Hvx::HvPokeDWORD(0x000001040002AA8C, 0x41980220);
//	xbox::Hvx::HvPokeBytes(0x000001040002AA8C, mbHV.GetData() + 0x2AA8C, 0x4);
//	xbox::utilities::DbgOut("cleanhv4: down\n");
//}

//
//VOID cleanhv6(MemoryBuffer mbHV) {
//	xbox::utilities::DbgOut("cleanhv6: start\n");
//	xbox::Hvx::HvPokeDWORD(0x00000106000304FC, 0x409AFFB0);
//	xbox::Hvx::HvPokeBytes(0x00000106000304FC, mbHV.GetData() + 0x304FC, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x00000106000304FC, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x00000106000304FC, 0x409AFFB0\n");
//
//	xbox::Hvx::HvPokeDWORD(0x00000106000304E8, 0x409AFFC4);
//	xbox::Hvx::HvPokeBytes(0x00000106000304E8, mbHV.GetData() + 0x304E8, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x00000106000304E8, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x00000106000304E8, 0x409AFFC4\n");
//
//	xbox::Hvx::HvPokeDWORD(0x000001060003089C, 0x419AFF40);
//	xbox::Hvx::HvPokeBytes(0x000001060003089C, mbHV.GetData() + 0x3089C, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x000001060003089C, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x000001060003089C, 0x419AFF40\n");
//
//	xbox::Hvx::HvPokeDWORD(0x00000106000308A0, 0x817F0008);
//	xbox::Hvx::HvPokeBytes(0x00000106000308A0, mbHV.GetData() + 0x308A0, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x00000106000308A0, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x00000106000308A0, 0x817F0008\n");
//
//	xbox::Hvx::HvPokeDWORD(0x00000106000308A4, 0x7F0BE040);
//	xbox::Hvx::HvPokeBytes(0x00000106000308A4, mbHV.GetData() + 0x308A4, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x00000106000308A4, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x00000106000308A4, 0x7F0BE040\n");
//
//	xbox::Hvx::HvPokeDWORD(0x00000106000308A8, 0x4199FF34);
//	xbox::Hvx::HvPokeBytes(0x00000106000308A8, mbHV.GetData() + 0x308A8, 0x4);
//	Hvx::HvProc(Hvx::HvpSaveCachelines, 2, 0x00000106000308A8, 0x4);
//	xbox::utilities::DbgOut("cleanhv6: 0x00000106000308A8, 0x4199FF34\n");
//	xbox::utilities::DbgOut("cleanhv6: down\n");
//}





//VOID sub_23830(PBYTE Buffer1, DWORD Size1, PBYTE Buffer2, DWORD Size2) {
//	DWORD i = 0;
//	for (DWORD s = 0; s < Size2; s += 0x14)
//	{
//		DWORD subsize = (s + 0x14 > Size2) ? Size2 - s : 0x14;
//		BYTE tmp[0x14];
//		BYTE tmpint[0x04] = { 0, 0, 0, i };
//		XECRYPT_SHA_STATE sha;
//		XeCryptShaInit(&sha);
//		XeCryptShaUpdate(&sha, Buffer1, Size1);
//		XeCryptShaUpdate(&sha, tmpint, 4);
//		XeCryptShaFinal(&sha, tmp, 0x14);
//		for (DWORD l = 0; l < subsize; l++)
//			Buffer2[s + l] ^= tmp[l];
//		i++;
//	}
//}
//
//void Reverse(BYTE* Input, DWORD Length) {
//	BYTE* tmp = (BYTE*)XEncryptedAlloc(Length);
//	for (DWORD i = Length - 1; i > 0; i--)
//	{
//		DWORD x = abs((int)i - 40);
//		tmp[x] = Input[i];
//	}
//	memcpy(Input, tmp, Length);
//	XEncryptedFree(tmp);
//}
//
//VOID sub_23918(PBYTE Sig, PBYTE Key, BYTE* XeRand) {
//	BYTE HvData[] = { 0xDA, 0x39, 0xA3, 0xEE, 0x5E, 0x6B, 0x4B, 0x0D, 0x32, 0x55, 0xBF, 0xEF, 0x95, 0x60, 0x18, 0x90, 0xAF, 0xD8, 0x07, 0x09 };
//	Sig[0] = 0;
//	memcpy((Sig + 1), XeRand, 0x14);
//	memcpy((Sig + 0x15), HvData, 0x14);
//	memset((Sig + 0x29), 0, 0x26);
//	Sig[0x4F] = 1;
//	memcpy((Sig + 0x50), Key, 0x30);
//	sub_23830(XeRand, 0x14, (Sig + 0x15), 0x6B);
//	sub_23830((Sig + 0x15), 0x6B, XeRand, 0x14);
//}*/

//NTSTATUS SysChall_GetDeviceControlRequest(xoscResponse* chalResp) {
//	chalResp->operations |= 1;

//	PVOID deviceObject = NULL;
//	BYTE partitionInfo[0x24] = { 0 };
//	NTSTATUS status = STATUS_SUCCESS;
//	STRING objectPath = { 0xE, 0xF, "\\Device\\Cdrom0" };

//	if (!NT_SUCCESS(status = ObReferenceObjectByName(&objectPath, 0, 0, 0, &deviceObject)))
//		return chalResp->ioCtlResult = status;

//	*(long long*)((int)chalResp + 0xF0) = -1;
//	*(long long*)((int)chalResp + 0xF8) = -1;
//	*(long long*)((int)chalResp + 0x100) = -1;
//	*(long long*)((int)chalResp + 0x108) = -1;
//	*(long long*)((int)chalResp + 0x110) = -1;

//	*(short*)((int)deviceObject + 0x20) = *(short*)((int)chalResp + 0xF0);

//	*(char*)partitionInfo = 0x24;
//	*(char*)(partitionInfo + 0x7) = 1;
//	*(int*)(partitionInfo + 0x8) = 0x24;
//	*(char*)(partitionInfo + 0x14) = 0x12;
//	*(char*)(partitionInfo + 0x18) = 0x24;
//	*(char*)(partitionInfo + 0x19) = 0xC0;

//	status = IoSynchronousDeviceIoControlRequest(IOCTL_DISK_VERIFY, &deviceObject, partitionInfo, 0x24, 0, 0, 0);
//	ObDereferenceObject(deviceObject);

//	return chalResp->ioCtlResult = status;
//}




//81A724EC 397 XeCryptRc4 xboxkrnl.exe
//81A72B9C 395 XeCryptRc4Key xboxkrnl.exe
//81A72B7C 346 XeCryptAesEcb xboxkrnl.exe

//	EXPORTNUM(346)
//	XeCryptAesEcb(
//		IN		const PXECRYPT_AES_STATE pAesState,
//		IN		const PBYTE pbInp,
//		OUT		PBYTE pbOut,
//		IN		BOOL fEncrypt
//	);


//std::string getTime()
//{
//	SYSTEMTIME st;
//	GetSystemTime(&st);
//	//return va("%d.%d.%d-%d.%d.%d", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wMilliseconds);
//	std::ostringstream os;
//	os << st.wMonth << "." << st.wDay << "." << st.wYear << "-" << st.wHour << "." << st.wMinute << "." << st.wMilliseconds;
//	return os.str();
//}
//
//void arrPrintXln(char* txt, PBYTE pbArray, DWORD cbArray) {
//	char dest[0x512];
//	std::ofstream log_file("Client:\\dump.log", std::ios_base::app);
//	if (log_file.is_open()) {
//		sprintf(dest, "XBLH: %s\n", txt);
//		printf(dest);
//		log_file << dest;
//
//		for (int i = 0; i < cbArray; i++)
//		{
//			sprintf(dest, "%02X", pbArray[i]);
//			printf(dest);
//			log_file << dest;
//
//			if (i != cbArray - 1) {
//				sprintf(dest, " ");
//				printf(dest);
//				log_file << dest;
//			}
//		}
//
//		sprintf(dest, "\n");
//		printf(dest);
//		log_file << dest;
//	}
//}
//
//Detour<VOID>* pXeCryptAesKey = new Detour<VOID>;
//VOID XeCryptAesKey_Hook(PXECRYPT_AES_STATE pAesState, PBYTE pbKey) {
//
//	xbox::utilities::DbgOut("XeCryptAesKey: ");
//	arrPrintXln("pbKey: ", pbKey, 0x30);
//
//	pXeCryptAesKey->CallOriginal(pAesState, pbKey);
//}
//
//Detour<VOID>* pXeCryptAesCbc = new Detour<VOID>;
//VOID XeCryptAesCbc_Hook(const PXECRYPT_AES_STATE pAesState, const PBYTE pbInp, DWORD cbInp, PBYTE pbOut, PBYTE pbFeed, BOOL fEncrypt) {
//
//	//xbox::utilities::DbgOut("XeCryptAesCbc: ");
//	pXeCryptAesCbc->CallOriginal(pAesState, pbInp, cbInp, pbOut, pbFeed, fEncrypt);
//}
//
//
////81A72B9C 395 XeCryptRc4Key xboxkrnl.exe
////
//
//Detour<int>* pNetDll_recv = new Detour<int>;
//int NetDll_recv_Hook(XNCALLER_TYPE xnc, SOCKET s, const char FAR* buf, int len, int flags) {
//
//	//xbox::utilities::DbgOut("NetDll_recv: len: %i flags: %i", len, flags);
//	return pNetDll_recv->CallOriginal(xnc, s, buf, len, flags);
//}
//
//Detour<int>* pNetDll_send = new Detour<int>;
//int NetDll_send_Hook(XNCALLER_TYPE xnc, SOCKET s, const char FAR* buf, int len, int flags) {
//
//	//xbox::utilities::DbgOut("NetDll_send: len: %i flags: %i", len, flags);
//	return pNetDll_send->CallOriginal(xnc, s, buf, len, flags);
//}

	//pXeCryptAesKey->SetupDetour((DWORD)xbox::utilities::resolveFunction(MODULE_XAM, 345), XeCryptAesKey_Hook);
	//pXeCryptAesCbc->SetupDetour((DWORD)xbox::utilities::resolveFunction(MODULE_XAM, 347), XeCryptAesCbc_Hook);
	//pNetDll_recv->SetupDetour((DWORD)xbox::utilities::resolveFunction(MODULE_XAM, 18), NetDll_recv_Hook);
	//pNetDll_send->SetupDetour((DWORD)xbox::utilities::resolveFunction(MODULE_XAM, 22), NetDll_send_Hook);
		//*(PDWORD)((DWORD)xbox::utilities::resolveFunction("xam.xex", 0x1C8) + 0x16C) = 0x60000000;

//
//	//=========================================================
//xbox::Hvx::HvPeekBytes(0, LiveHV, 0xFFFF);
//*(PDWORD)(LiveHV + 0x11BC) = *(PDWORD)(BaseHV + 0x11BC);
//memcpy(LiveHV + 0x154C, BaseHV + 0x154C, 0x10);
//*(PDWORD)(LiveHV + 0x1880) = *(PDWORD)(BaseHV + 0x1880);
//*(PDWORD)(LiveHV + 0x3120) = *(PDWORD)(BaseHV + 0x3120);
//*(PDWORD)(LiveHV + 0x6BB0) = *(PDWORD)(BaseHV + 0x6BB0);
//*(PDWORD)(LiveHV + 0x6BB4) = *(PDWORD)(BaseHV + 0x6BB4);
//*(PDWORD)(LiveHV + 0x6C48) = *(PDWORD)(BaseHV + 0x6C48);
//*(PDWORD)(LiveHV + 0x6C4C) = *(PDWORD)(BaseHV + 0x6C4C);
//*(PDWORD)(LiveHV + 0x6C98) = *(PDWORD)(BaseHV + 0x6C98);
//*(PDWORD)(LiveHV + 0x6C9C) = *(PDWORD)(BaseHV + 0x6C9C);
//*(PDWORD)(LiveHV + 0x6D08) = *(PDWORD)(BaseHV + 0x6D08);
//*(PDWORD)(LiveHV + 0x6D0C) = *(PDWORD)(BaseHV + 0x6D0C);
//*(PDWORD)(LiveHV + 0x6D58) = *(PDWORD)(BaseHV + 0x6D58);
//*(PDWORD)(LiveHV + 0x6D5C) = *(PDWORD)(BaseHV + 0x6D5C);
//*(PDWORD)(LiveHV + 0x70BC) = *(PDWORD)(BaseHV + 0x70BC);
//*(PDWORD)(LiveHV + 0x7268) = *(PDWORD)(BaseHV + 0x7268);
//*(PDWORD)(LiveHV + 0x72B4) = *(PDWORD)(BaseHV + 0x72B4);
//*(PDWORD)(LiveHV + 0x72C4) = *(PDWORD)(BaseHV + 0x72C4);
//*(PDWORD)(LiveHV + 0x72EC) = *(PDWORD)(BaseHV + 0x72EC);
//*(PDWORD)(LiveHV + 0x72F0) = *(PDWORD)(BaseHV + 0x72F0);
//*(PDWORD)(LiveHV + 0x813C) = *(PDWORD)(BaseHV + 0x813C);
//*(PDWORD)(LiveHV + 0xA560) = *(PDWORD)(BaseHV + 0xA560);
//*(PDWORD)(LiveHV + 0xA564) = *(PDWORD)(BaseHV + 0xA564);
//memcpy(LiveHV + 0xB510, BaseHV + 0xB510, 0x120);
//xbox::utilities::DbgOut("Reading #1\n");
//
//Sleep(300);
////MakeHvHashes(0x0000000000000000, 0x100);
////MakeHvHashes(0x0000000000000000, 0x200);
//xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0, 0x200);
//Sleep(300);
//xbox::Hvx::HvPokeBytes(0, LiveHV, 0xFFFF);
////=========================================================
//Sleep(300);
//
//xbox::utilities::DbgOut("Reading #2\n");
//xbox::Hvx::HvPeekBytes(0x0000010200010000, LiveHV, 0xFFFF);
//*(PDWORD)(LiveHV + 0x15E60) = *(PDWORD)(BaseHV + 0x15E60);
//*(PDWORD)(LiveHV + 0x15FD0) = *(PDWORD)(BaseHV + 0x15FD0);
//*(PDWORD)(LiveHV + 0x100F0) = 0xD8D815C0;
//*(PDWORD)(LiveHV + 0x100F4) = 0x1FEF372B;
//*(PDWORD)(LiveHV + 0x100F8) = 0x8ACA4B23;
//*(PDWORD)(LiveHV + 0x100FC) = 0xE449B79F;
//Sleep(300);
////MakeHvHashes(0x0000010200010000, 0x100);
////MakeHvHashes(0x0000010200010000, 0x200);
//xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010200010000, 0x200);
//Sleep(300);
//xbox::Hvx::HvPokeBytes(0x0000010200010000, LiveHV, 0xFFFF);
//Sleep(300);
//
//xbox::utilities::DbgOut("Reading #3\n");
//xbox::Hvx::HvPeekBytes(0x0000010400020000, LiveHV, 0xFFFF);
//*(PDWORD)(LiveHV + 0x24D58) = *(PDWORD)(BaseHV + 0x24D58);
//*(PDWORD)(LiveHV + 0x24D5C) = *(PDWORD)(BaseHV + 0x24D5C);
//*(PDWORD)(LiveHV + 0x264F0) = *(PDWORD)(BaseHV + 0x264F0);
//memcpy(LiveHV + 0x29B08, BaseHV + 0x29B08, 0x38);
//*(PDWORD)(LiveHV + 0x2A30C) = *(PDWORD)(BaseHV + 0x2A30C);
//*(PDWORD)(LiveHV + 0x2A310) = *(PDWORD)(BaseHV + 0x2A310);
//*(PDWORD)(LiveHV + 0x2AA80) = *(PDWORD)(BaseHV + 0x2AA80);
//*(PDWORD)(LiveHV + 0x2AA8C) = *(PDWORD)(BaseHV + 0x2AA8C);
//*(PDWORD)(LiveHV + 0x2B770) = *(PDWORD)(BaseHV + 0x2B770);
//*(PDWORD)(LiveHV + 0x2B778) = *(PDWORD)(BaseHV + 0x2B778);
//*(PDWORD)(LiveHV + 0x2C0B0) = *(PDWORD)(BaseHV + 0x2C0B0);
//*(PDWORD)(LiveHV + 0x2C3A0) = *(PDWORD)(BaseHV + 0x2C3A0);
//*(PDWORD)(LiveHV + 0x2CAE8) = *(PDWORD)(BaseHV + 0x2CAE8);
//*(PDWORD)(LiveHV + 0x2CDD8) = *(PDWORD)(BaseHV + 0x2CDD8);
//Sleep(300);
////MakeHvHashes(0x0000010400020000, 0x100);
////MakeHvHashes(0x0000010400020000, 0x200);
//xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010400020000, 0x200);
//Sleep(300);
//xbox::Hvx::HvPokeBytes(0x0000010400020000, LiveHV, 0xFFFF);
//Sleep(300);
//
//xbox::utilities::DbgOut("Reading #4\n");
//xbox::Hvx::HvPeekBytes(0x0000010600030000, LiveHV, 0xFFFF);
//*(PDWORD)(LiveHV + 0x304E8) = *(PDWORD)(BaseHV + 0x304E8);
//*(PDWORD)(LiveHV + 0x304FC) = *(PDWORD)(BaseHV + 0x304FC);
//*(PDWORD)(LiveHV + 0x3089C) = *(PDWORD)(BaseHV + 0x3089C);
//*(PDWORD)(LiveHV + 0x308A0) = *(PDWORD)(BaseHV + 0x308A0);
//*(PDWORD)(LiveHV + 0x308A4) = *(PDWORD)(BaseHV + 0x308A4);
//*(PDWORD)(LiveHV + 0x308A8) = *(PDWORD)(BaseHV + 0x308A8);
//Sleep(300);
////MakeHvHashes(0x0000010600030000, 0x100);
////MakeHvHashes(0x0000010600030000, 0x200);
//xbox::Hvx::HvProc(xbox::Hvx::HvpSaveCachelines, 2, 0x0000010600030000, 0x200);
//Sleep(300);
//xbox::Hvx::HvPokeBytes(0x0000010600030000, LiveHV, 0xFFFF);
//Sleep(300);