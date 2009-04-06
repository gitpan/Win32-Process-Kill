#include <windows.h>

typedef DWORD (CALLBACK* NTTERMINATEPROCESS)(HANDLE,UINT);
NTTERMINATEPROCESS NtTerminateProcess;

int pTerminate (int ProcessId){
	HANDLE hProcess = NULL;
	HMODULE hNtdll = NULL;
	hNtdll = LoadLibrary( "ntdll.dll" ); 
	if ( !hNtdll ){
	        return 2;
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
