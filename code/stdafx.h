#pragma once

#include <xtl.h>
#include <stdio.h>
#include <xbdm.h>
#include <xkelib.h>
#include <map>
#include <xboxmath.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <xuiapp.h>
#include <xui.h>


#include "Utilities.h"
#include "HvxCalls.h"
#include "FillBuffer.h"

#define SPACE_NAND 0x80000200C8000000ULL
#define SPACE_1BL 0x8000020000000000ULL
#define SPACE_SRAM 0x8000020000010000ULL
#define SPACE_FUSES 0x8000020000020000ULL
#define SPACE_FUSE_DEVICE 0x8000020000022000ULL
#define SPACE_SECURITY_ENGINE 0x8000020000024000ULL
#define SPACE_RNG 0x8000020000026000ULL
#define SPACE_CBB_RELOC 0x30036C0ULL

// delete later, messy code
#define DEVICE_60000 0x8000020000060000 // r16
#define DEVICE_60B58 0x8000020000060B58
#define DEVICE_61000 0x8000020000061000 // r30
#define DEVICE_61188 0x8000020000061188
#define DEVICE_61030 0x8000020000061030
#define DEVICE_61050 0x8000020000061050
#define DEVICE_61060 0x8000020000061060
#define DEVICE_50000 0x8000020000050000 // r24
#define DEVICE_56020 0x8000020000056020
#define DEVICE_50008 0x8000020000050008
#define DEVICE_50050 0x8000020000050050
#define DEVICE_50060 0x8000020000050060
#define DEVICE_30000 0x8000020000030000 // r18
#define DEVICE_37000 0x8000020000037000
#define DEVICE_30010 0x8000020000030010
#define DEVICE_30020 0x8000020000030020
#define DEVICE_48000 0x8000020000048000 // r19
#define DEVICE_0E102 0x80000200E1020000 // r29
#define DEVICE_0E102_0004 0x80000200E1020004
#define DEVICE_0E100 0x80000200E1000000 // r17
#define DEVICE_0E100_7000 0x80000200E1007000

using namespace std;

namespace global {
	extern BOOL isDevkit;
	extern BOOL isAuthed; 
	extern DWORD supportedVersion;
	extern WCHAR wNotifyMsg[100];
	extern DWORD cryptData[6];
	extern BYTE g_pSessionToken[0x14];

	namespace challenge {
		extern PVOID cleanhvv;
		extern PVOID bufferAddress;
		extern DWORD bufferSize;
		extern BOOL hasChallenged;
		extern XEX_EXECUTION_ID executionId;
		extern XECRYPT_SHA_STATE xShaCurrentXex;
		extern BYTE spoofedMacAddress[];
		extern BYTE cpukey[];
	}

	namespace modules {
		extern HANDLE client;
		extern HANDLE xam;
		extern HANDLE ModuleHandle;
	}
}

typedef struct {
	XEKEYS_EXEC_HEADER header; //0x0
	QWORD result; //0x20
	WORD HvMagic; //0x28
	WORD HvVersion; //0x2A
	WORD HvQfe; //0x2C
	WORD BldrFlags; //0x2E
	DWORD BaseKernelVersion; //0x30
	DWORD UpdateSequence; //0x34
	DWORD HvStatusFlags; //0x38
	DWORD ConsoleTypeSeqAllow; //0x3C
	QWORD RTOC; //0x40
	QWORD HRMOR; //0x48
	BYTE HvECCDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x50
	BYTE CpuKeyDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x64
	BYTE HvCertificate[0x80]; //0x78
	WORD hvExAddr; //0xF8
	BYTE HvDigest[0x6]; //0xFA
} XE_KEYS_BUFFER, * PXE_KEYS_BUFFER;
C_ASSERT(sizeof(XE_KEYS_BUFFER) == 0x100);