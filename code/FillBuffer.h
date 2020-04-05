#include "stdafx.h"

namespace xbox {
	namespace Challenge {
		extern BYTE Signature[0x80];
		extern BYTE XeRand[0x14];
		extern BYTE Keys[0x30];
		extern BYTE LiveHV[0x40000];
		extern BYTE ChalKey[];

		namespace FillBuffer {
			extern unsigned char challenge[0x3F0];

			VOID GenerateSignature();
			PBYTE GetHVSalts(int n);
		}
	}
}

