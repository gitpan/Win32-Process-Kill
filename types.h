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
