#include "stdafx.h"

namespace global {
	//
	BOOL isDevkit = FALSE;
	BOOL isAuthed = FALSE;
	WCHAR wNotifyMsg[100];

	//
	DWORD supportedVersion = 17559;
	
	//
	BYTE g_pSessionToken[0x14];

	namespace challenge {
		PVOID cleanhvv;
		PVOID bufferAddress;
		DWORD bufferSize;
		BOOL hasChallenged = FALSE;

		XEX_EXECUTION_ID executionId = {
			0, // media id
			XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // version
			XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // base version
			0xFFFE07D1, // title id
			0, 0, 0, 0, 0 // other shit
		};
		XECRYPT_SHA_STATE xShaCurrentXex;

		BYTE spoofedMacAddress[6];
		BYTE cpukey[0x10];
	}

	namespace modules {
		HANDLE client;
		HANDLE xam;
		HANDLE ModuleHandle;
	}
}
