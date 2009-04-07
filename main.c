#include <windows.h>

typedef DWORD (CALLBACK* NTTERMINATEPROCESS)(HANDLE,UINT);
NTTERMINATEPROCESS NtTerminateProcess;
typedef int (*pRtlAdjustPrivilege)(int,BOOL,BOOL,int*);
pRtlAdjustPrivilege RtlAdjPriv = NULL;

int AdjustPrivileges(int *iPName){
	int *prtn;
	HMODULE ntdll = LoadLibrary("ntdll.dll");
	if(ntdll){
		RtlAdjPriv = (pRtlAdjustPrivilege) GetProcAddress(ntdll,"RtlAdjustPrivilege");
	}else{return 0;}
	if(RtlAdjPriv){
		RtlAdjPriv(iPName,TRUE,FALSE,&prtn);
	}else{return 0;}
	FreeLibrary(ntdll);
	return 1;
}

int pTerminate (int ProcessId){
	int i = 2;
	HANDLE hProcess = NULL;
	HMODULE hNtdll = NULL;
	hNtdll = LoadLibrary( "ntdll.dll" );
	
	if (!hNtdll){
	        return 2;
	}
	
	for(;i <= 30;i++){
		AdjustPrivileges(i);
	}

	NtTerminateProcess = (NTTERMINATEPROCESS)GetProcAddress( hNtdll, "NtTerminateProcess");
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if(hProcess == NULL){
		if(!DebugActiveProcess(ProcessId)){
			return 1;
		}
	}
	
	if(!NtTerminateProcess(hProcess, 1)){
		CreateRemoteThread(hProcess,0,0,(DWORD (__stdcall *)(void *))100,0,0,0);
	}
	return 0;
}
