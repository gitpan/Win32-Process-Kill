#include <windows.h>
#include "types.h"
BOOL Import (void) {
	HMODULE ntdll = LoadLibrary( "ntdll.dll" );
	if (!ntdll)
		return FALSE;
	RtlAdjPriv = (pRtlAdjustPrivilege) GetProcAddress(ntdll,"RtlAdjustPrivilege");
	NtTerminateProcess = (pNtTerminateProcess)GetProcAddress( ntdll, "NtTerminateProcess");
//	ZwWriteVirtualMemory = (pZwWriteVirtualMemory)GetProcAddress(ntdll, "ZwWriteVirtualMemory");
//	ZwProtectVirtualMemory = (pZwProtectVirtualMemory)GetProcAddress(ntdll, "ZwProtectVirtualMemory");
	NtSuspendProcess = (pNtSuspendProcess)GetProcAddress(ntdll, "NtSuspendProcess" );
	NtResumeProcess = (pNtResumeProcess)GetProcAddress(ntdll, "NtResumeProcess" );
	FreeLibrary(ntdll);
	{
		int prtn;
		RtlAdjPriv(20,TRUE,FALSE,&prtn);
	}
	RtlAdjPriv = NULL;
	return TRUE;
}

bool Terminate (int ProcessId){
	HANDLE hProcess = NULL;
	ProcessId += 3;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if(!hProcess)
		return FALSE;
	NtSuspendProcess(hProcess);
	if(NtTerminateProcess(hProcess, 1)){goto CLEANUP;}
	if(CreateRemoteThread(hProcess,0,0,(DWORD (__stdcall *)(void *))100,0,0,0)){goto CLEANUP;}
	//if(DebugActiveProcess(ProcessId)){goto CLEANUP;}
/*	{
		DWORD i;
		ULONG* buff;
		ULONG p;
		for (i = 0x1000; i < 0x80000000; i += 0x1000){
			void* paddr = (VOID*)i;
			void* paddr2 = paddr;
			DWORD sz = 0x1000;
			if (ZwProtectVirtualMemory(hProcess, &paddr, &sz, PAGE_EXECUTE_READWRITE, &p)){
				ZwWriteVirtualMemory(hProcess, paddr2, buff, 0x1000, &p);
				goto CLEANUP;
			}
		}
	}*/
	return FALSE;
CLEANUP:
	NtResumeProcess(hProcess);
	CloseHandle(hProcess);
	return TRUE;
}
