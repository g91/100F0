#include "stdafx.h"

SOCKET Socket = INVALID_SOCKET;
BYTE TempBuffer[0x4800] = { 0 };
BOOL Pending = FALSE, Connected = FALSE, Authenticated = FALSE;
BYTE IPAddress[4] = { 198, 251, 89, 94 }; //IP GO HERE
WORD Port = 2526;

BOOL Connect() {
	XNetStartupParams XNSP = { 0 };
	XNSP.cfgSizeOfStruct = sizeof(XNetStartupParams);
	XNSP.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;
	if (NetDll_XNetStartup(XNCALLER_SYSAPP, &XNSP) != 0) 
		return FALSE;

	WSADATA WsaData = { 0 };
	if (NetDll_WSAStartupEx(XNCALLER_SYSAPP, WINSOCK_VERSION, &WsaData, WINSOCK_VERSION) != 0) 
		return FALSE;

	if ((Socket = NetDll_socket(XNCALLER_SYSAPP, AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
		return FALSE;

	BOOL SockOpt = TRUE;
	if (NetDll_setsockopt(XNCALLER_SYSAPP, Socket, SOL_SOCKET, SO_MARKINSECURE, (CONST PCHAR)&SockOpt, sizeof(BOOL)) != 0) 
		return FALSE;

	DWORD MaxPacketSize = 0x800;
	if (NetDll_setsockopt(XNCALLER_SYSAPP, Socket, SOL_SOCKET, SO_SNDBUF, (CONST PCHAR)&MaxPacketSize, sizeof(DWORD)) != 0) 
		return FALSE;

	if (NetDll_setsockopt(XNCALLER_SYSAPP, Socket, SOL_SOCKET, SO_RCVBUF, (CONST PCHAR)&MaxPacketSize, sizeof(DWORD)) != 0) 
		return FALSE;

	sockaddr_in sockAddr = { 0 };
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.S_un.S_addr = *(PDWORD)IPAddress;
	sockAddr.sin_port = htons(Port);
	if (NetDll_connect(XNCALLER_SYSAPP, Socket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) 
		return FALSE;

	return Connected = TRUE;
}

VOID Disconnect() {
	if ((Socket != INVALID_SOCKET) && Connected) {
		NetDll_closesocket(XNCALLER_SYSAPP, Socket);
		Socket = INVALID_SOCKET;
		Connected = FALSE;
	}
}

BOOL Send(DWORD Command, PVOID Buffer, DWORD Size) {
	memset(TempBuffer, 0, sizeof(TempBuffer));
	memcpy(TempBuffer, &Command, sizeof(DWORD));
	memcpy(TempBuffer + 4, &Size, sizeof(DWORD));
	XeCryptRc4(NetworkKey, 0x10, (PBYTE)Buffer, Size);
	memcpy(TempBuffer + 8, Buffer, Size);

	DWORD Remaining = (Size + 8);
	PCHAR Current = (PCHAR)TempBuffer;
	while (Remaining > 0){
		DWORD Result = NetDll_send(XNCALLER_SYSAPP, Socket, Current, min(0x800, Remaining), 0);
		if (Result <= 0) return FALSE;
		Remaining -= Result;
		Current += Result;
	}

	return TRUE;
}

BOOL Receive(PVOID Buffer, DWORD Size) {
	DWORD Received = 0;
	DWORD Remaining = Size;
	while (Remaining > 0)
	{
		DWORD Result = NetDll_recv(XNCALLER_SYSAPP, Socket, (PCHAR)Buffer + Received, min(0x800, Remaining), 0);
		if (Result <= 0) return FALSE;
		Remaining -= Result;
		Received += Result;
	}
	XeCryptRc4(NetworkKey, 0x10, (PBYTE)Buffer, Size);
	return (Received == Size);
}

BOOL Process(DWORD Command, PVOID Request, DWORD RequestSize, PVOID Response, DWORD ResponseSize, BOOL Close) {
	while (Pending) Sleep(1);
	Pending = TRUE;
	for (DWORD i = 0; i < 3; i++)
		if (Connect()) break;
	if (!Connected) return FALSE;
	if (!Send(Command, Request, RequestSize)) return FALSE;
	if (!Receive(Response, ResponseSize)) return FALSE;
	if (Close) Disconnect();
	Pending = FALSE;
	return TRUE;
}

VOID Update(BOOL Reboot) {
	DWORD ModuleSize = 0;
	if (!Receive(&ModuleSize, sizeof(DWORD))){
		Disconnect();
		return;
	}

	PBYTE ModuleBuffer = (PBYTE)XPhysicalAlloc(ModuleSize, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(ModuleBuffer, 0, ModuleSize);
	if (!Receive(ModuleBuffer, ModuleSize)){
		XPhysicalFree(ModuleBuffer);
		Disconnect();
		return;
	}

	if (!xbox::utilities::writeFile(PATH_XEX, ModuleBuffer, ModuleSize)){
		XPhysicalFree(ModuleBuffer);
		Disconnect();
		return;
	}

	XPhysicalFree(ModuleBuffer);
	Sleep(10000);

	if (Reboot) 
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
	else 
		xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_UPDATING, L"Client.xex");//NAME OF THE XEX
}

void get_xex(DWORD CODE) {
	XEX_REQUEST* Request = (XEX_REQUEST*)XPhysicalAlloc(sizeof(XEX_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Request, 0, sizeof(XEX_REQUEST));

	memcpy(Request->CPUKey, global::challenge::cpukey, 0x10);
	Request->CODE = CODE;

	XEX_RESPONSE* Response = (XEX_RESPONSE*)XPhysicalAlloc(sizeof(XEX_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Response, 0, sizeof(XEX_RESPONSE));

	Process(COMMAND_XEX, Request, sizeof(XEX_REQUEST), Response, sizeof(XEX_RESPONSE), FALSE);
	
	if (Response->Status == 0x4A000000) {
		DWORD ModuleSize = 0;
		if (!Receive(&ModuleSize, sizeof(DWORD))) {
			Disconnect();
			return;
		}

		PBYTE ModuleBuffer = (PBYTE)XPhysicalAlloc(ModuleSize, MAXULONG_PTR, 0, PAGE_READWRITE);
		memset(ModuleBuffer, 0, ModuleSize);
		if (!Receive(ModuleBuffer, ModuleSize)) {
			XPhysicalFree(ModuleBuffer);
			Disconnect();
			return;
		}

		XexLoadImageFromMemory(ModuleBuffer, ModuleSize, "text.xex", 8, 0, &global::modules::ModuleHandle);
	}

	Disconnect();
	XPhysicalFree(Request);
	XPhysicalFree(Response);
	return;
}


void MSG(char* txt, DWORD CODE) {
	//MSG_REQUEST* Request = (MSG_REQUEST*)XPhysicalAlloc(sizeof(MSG_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
	//memset(Request, 0, sizeof(MSG_REQUEST));

	//MSG_RESPONSE* Response = (MSG_RESPONSE*)XPhysicalAlloc(sizeof(MSG_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
	//memset(Response, 0, sizeof(MSG_RESPONSE));

	//Request->CODE = CODE;
	//Process(COMMAND_MSG, Request, sizeof(MSG_REQUEST), Response, sizeof(MSG_RESPONSE), FALSE);
	//Disconnect();
	return;
}

DASH_RESPONSE* SET_DASH_COLOR() {
	DASH_REQUEST* Request = (DASH_REQUEST*)XPhysicalAlloc(sizeof(DASH_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Request, 0, sizeof(DASH_REQUEST));

	memcpy(Request->CPUKey, global::challenge::cpukey, 0x10);
	DASH_RESPONSE* Response = (DASH_RESPONSE*)XPhysicalAlloc(sizeof(DASH_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Response, 0, sizeof(DASH_RESPONSE));

	Process(COMMAND_COLOR, Request, sizeof(DASH_REQUEST), Response, sizeof(DASH_RESPONSE), FALSE);

	Disconnect();
	XPhysicalFree(Request);
	XPhysicalFree(Response);
	return Response;
}

VOID Update(BOOL Reboot, char* xex) {
	DWORD ModuleSize = 0;
	if (!Receive(&ModuleSize, sizeof(DWORD))){
		Disconnect();
		return;
	}

	PBYTE ModuleBuffer = (PBYTE)XPhysicalAlloc(ModuleSize, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(ModuleBuffer, 0, ModuleSize);
	if (!Receive(ModuleBuffer, ModuleSize)){
		XPhysicalFree(ModuleBuffer);
		Disconnect();
		return;
	}

	if (!xbox::utilities::writeFile(xex, ModuleBuffer, ModuleSize)){
		XPhysicalFree(ModuleBuffer);
		Disconnect();
		return;
	}

	XPhysicalFree(ModuleBuffer);
	Sleep(10000);
	if (Reboot) 
		HalReturnToFirmware(HalFatalErrorRebootRoutine);
	else 
		xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_UPDATING, L"update");

	return;
}

BOOL XBDMFiX() {
start:
	XBDM_REQUEST* Request = (XBDM_REQUEST*)XPhysicalAlloc(sizeof(XBDM_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Request, 0, sizeof(XBDM_REQUEST));

	XBDM_RESPONSE* Response = (XBDM_RESPONSE*)XPhysicalAlloc(sizeof(XBDM_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Response, 0, sizeof(XBDM_RESPONSE));

	Request->Version = 1;
	memcpy(Request->CPUKey, global::challenge::cpukey, 0x10);
	
	MemoryBuffer mbXBDMModule;
	if (!xbox::utilities::readFile("hdd:\\XBDM.xex", mbXBDMModule)) {
		return FALSE;
	}
	XeCryptSha(mbXBDMModule.GetData(), mbXBDMModule.GetDataLength(), 0, 0, 0, 0, Request->ModuleDigest, 0x14);

	if (Process(COMMAND_XBDM, Request, sizeof(XBDM_REQUEST), Response, sizeof(XBDM_RESPONSE), FALSE)) {
		if (Response->Status == 0x40000000) Update(TRUE, "hdd:\\XBDM.xex");
		else if (Authenticated = (Response->Status == 0x4A000000)) {
			
		}else{
			goto start;
		}
	}

	Disconnect();
	XPhysicalFree(Request);
	XPhysicalFree(Response);
	return TRUE;
}

BOOL Authenticate() {
start:
	AUTH_REQUEST* Request = (AUTH_REQUEST*)XPhysicalAlloc(sizeof(AUTH_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Request, 0, sizeof(AUTH_REQUEST));

	AUTH_RESPONSE* Response = (AUTH_RESPONSE*)XPhysicalAlloc(sizeof(AUTH_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(Response, 0, sizeof(AUTH_RESPONSE));

	Request->Version = 1;
	memcpy(Request->CPUKey, global::challenge::cpukey, 0x10);

	MemoryBuffer mbModule;
	if (!xbox::utilities::readFile(PATH_XEX, mbModule)) {
		xbox::utilities::DbgOut("#7 FALSE");
		return FALSE;
	}
	XeCryptSha(mbModule.GetData(), mbModule.GetDataLength(), 0, 0, 0, 0, Request->ModuleDigest, 0x14);
	

	if (Process(COMMAND_AUTH, Request, sizeof(AUTH_REQUEST), Response, sizeof(AUTH_RESPONSE), FALSE)) {
		if (Response->Status == 0x40000000) Update(TRUE);
		else if (Authenticated = (Response->Status == 0x4A000000)) {
			xbox::utilities::MakeThread((LPTHREAD_START_ROUTINE)Presence);
		}else{
			goto start;
		}
	}

	Disconnect();
	XPhysicalFree(Request);
	XPhysicalFree(Response);
	return TRUE;
}

VOID Presence() {
	DWORD Attempt = 0;
	while (!DashLoaded) 
		Sleep(1);

	xbox::utilities::setLiveBlock(FALSE);

	for (;;) {
		Sleep(60000);
		Attempt++;

		PRES_REQUEST* Request = (PRES_REQUEST*)XPhysicalAlloc(sizeof(PRES_REQUEST), MAXULONG_PTR, 0, PAGE_READWRITE);
		memset(Request, 0, sizeof(PRES_REQUEST));

		PRES_RESPONSE* Response = (PRES_RESPONSE*)XPhysicalAlloc(sizeof(PRES_RESPONSE), MAXULONG_PTR, 0, PAGE_READWRITE);
		memset(Response, 0, sizeof(PRES_RESPONSE));

		Request->Title = XamGetCurrentTitleId();
		memcpy(Request->CPUKey, global::challenge::cpukey, 0x10);

		MemoryBuffer mbModule;
		if (!xbox::utilities::readFile(PATH_XEX, mbModule)) HalReturnToFirmware(HalRebootQuiesceRoutine);
		XeCryptSha(mbModule.GetData(), mbModule.GetDataLength(), 0, 0, 0, 0, Request->ModuleDigest, 0x14);

		XUSER_SIGNIN_INFO XUserSigninInfo = { 0 };
		if (NT_SUCCESS(XamUserGetSigninInfo(0, 0, &XUserSigninInfo))) memcpy(Request->Gamertag, XUserSigninInfo.szUserName, 0x10);

		if (Process(COMMAND_PRES, Request, sizeof(PRES_REQUEST), Response, sizeof(PRES_RESPONSE), FALSE)) {
			if (Response->Status == 0x40000000) Update(FALSE);
			else if (Authenticated = (Response->Status == 0x4A000000))
			xbox::utilities::setLiveBlock(!Authenticated);
			Attempt = 0;
		} else {
			Authenticated = FALSE;
			xbox::utilities::setLiveBlock(TRUE);
			if (Attempt >= 2) return;
		}

		Disconnect();
		XPhysicalFree(Request);
		XPhysicalFree(Response);
	}
}