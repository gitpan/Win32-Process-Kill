#define W32PK_SEDEBUG 20
typedef DWORD (NTAPI *pNtTerminateProcess)(HANDLE,UINT);
pNtTerminateProcess NtTerminateProcess;
typedef LONG (NTAPI *pNtSuspendProcess )( HANDLE ProcessHandle );
pNtSuspendProcess NtSuspendProcess;
typedef LONG (NTAPI *pNtResumeProcess )( HANDLE ProcessHandle );
pNtResumeProcess NtResumeProcess;

int Import (void) {
	HMODULE ntdll = GetModuleHandle( "ntdll.dll" );
	if (!ntdll)
		return 0;
	NtTerminateProcess = (pNtTerminateProcess)GetProcAddress( ntdll, "NtTerminateProcess");
	NtSuspendProcess = (pNtSuspendProcess)GetProcAddress(ntdll, "NtSuspendProcess" );
	NtResumeProcess = (pNtResumeProcess)GetProcAddress(ntdll, "NtResumeProcess" );
    {
        NTSTATUS (NTAPI * RtlAdjustPrivilege) (ULONG, BOOLEAN, BOOLEAN, PBOOLEAN)
        = (NTSTATUS (NTAPI *) (ULONG, BOOLEAN, BOOLEAN, PBOOLEAN)) GetProcAddress(ntdll,"RtlAdjustPrivilege");
		BOOLEAN prtn;
		if(RtlAdjustPrivilege(W32PK_SEDEBUG,TRUE,FALSE,&prtn) !=  STATUS_SUCCESS) return 0;
	}
	return 1;
}

__forceinline long _GetHandle (int ProcessId){ return (LONG)OpenProcess(PROCESS_ALL_ACCESS, (bool)TRUE, (HANDLE)ProcessId); }

__forceinline bool _Suspend(long hProcess){ return (bool)NT_SUCCESS(NtSuspendProcess((HANDLE)hProcess)); }
__forceinline bool _Resume (long hProcess){ return (bool)NT_SUCCESS(NtResumeProcess((HANDLE)hProcess)); }

__forceinline bool _TerminateProcess (long hProcess) { return (bool)NT_SUCCESS(NtTerminateProcess((HANDLE)hProcess, 1)); }

__forceinline bool _CreateRemoteThread (long hProcess) { return (bool)CreateRemoteThread((HANDLE)hProcess,0,0,(DWORD (__stdcall *)(void *))150,0,0,0); }

__forceinline bool _DebugActiveProcess (int ProcessId) { return (bool)DebugActiveProcess((int)ProcessId); }

