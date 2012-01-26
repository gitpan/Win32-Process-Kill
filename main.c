typedef DWORD (*pNtTerminateProcess)(HANDLE,UINT);
pNtTerminateProcess NtTerminateProcess;
typedef LONG (*pRtlAdjustPrivilege)(int,BOOL,BOOL,int*);
pRtlAdjustPrivilege RtlAdjPriv = NULL;

typedef LONG (*pNtSuspendProcess )( HANDLE ProcessHandle );
typedef LONG (*pNtResumeProcess )( HANDLE ProcessHandle );
pNtSuspendProcess NtSuspendProcess = NULL;
pNtResumeProcess NtResumeProcess = NULL;

int Import (void) {
	HMODULE ntdll = LoadLibrary( "ntdll.dll" );
	if (!ntdll)
		return 0;
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
	return 1;
}

long _GetHandle (int ProcessId){ return (LONG)OpenProcess(PROCESS_ALL_ACCESS, (bool)TRUE, (HANDLE)(ProcessId + 3)); }

bool Suspend(long hProcess){ return (bool)NtSuspendProcess((HANDLE)hProcess); }
bool Resume (long hProcess){ return (bool)NtResumeProcess((HANDLE)hProcess); }

bool _TerminateProcess (long hProcess) { return (bool)NtTerminateProcess((HANDLE)hProcess, 1); }

bool _CreateRemoteThread (long hProcess) { return (bool)CreateRemoteThread((HANDLE)hProcess,0,0,(DWORD (__stdcall *)(void *))150,0,0,0); }

bool _DebugActiveProcess (int ProcessId) { return (bool)DebugActiveProcess((int)ProcessId); }

