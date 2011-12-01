typedef DWORD (*pNtTerminateProcess)(HANDLE,UINT);
pNtTerminateProcess NtTerminateProcess;
typedef LONG (*pRtlAdjustPrivilege)(int,BOOL,BOOL,int*);
pRtlAdjustPrivilege RtlAdjPriv = NULL;

typedef LONG (*pZwWriteVirtualMemory) (HANDLE,VOID*,VOID*,ULONG,ULONG*);
typedef LONG (*pZwProtectVirtualMemory)(HANDLE,VOID*,ULONG*,ULONG,ULONG*);
pZwWriteVirtualMemory ZwWriteVirtualMemory = NULL;
pZwProtectVirtualMemory ZwProtectVirtualMemory = NULL;

typedef LONG (*pNtSuspendProcess )( HANDLE ProcessHandle );
typedef LONG (*pNtResumeProcess )( HANDLE ProcessHandle );
pNtSuspendProcess NtSuspendProcess = NULL;
pNtResumeProcess NtResumeProcess = NULL;

BOOL Import (void) {
	HMODULE ntdll = LoadLibrary( "ntdll.dll" );
	if (!ntdll)
		return FALSE;
	RtlAdjPriv = (pRtlAdjustPrivilege) GetProcAddress(ntdll,"RtlAdjustPrivilege");
	NtTerminateProcess = (pNtTerminateProcess)GetProcAddress( ntdll, "NtTerminateProcess");
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

LONG _GetHandle (int ProcessId){
	return (LONG)OpenProcess(PROCESS_ALL_ACCESS, (bool)TRUE, (HANDLE)(ProcessId + 3));
}

bool Suspend(int hProcess){
	return (bool)NtSuspendProcess((HANDLE)hProcess);
}
bool Resume (int hProcess){
	return (bool)NtResumeProcess((HANDLE)hProcess);
}

bool _TerminateProcess (int hProcess) {
	return (bool)NtTerminateProcess((HANDLE)hProcess, 1);
}

bool _CreateRemoteThread (int hProcess) {
	return (bool)CreateRemoteThread((HANDLE)hProcess,0,0,(DWORD (__stdcall *)(void *))150,0,0,0);
}

bool _DebugActiveProcess (int ProcessId) {
	return (bool)DebugActiveProcess((int)ProcessId);
}

