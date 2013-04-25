#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "SubAuth.h"
#include "main.c"

/* remove CRT dependency if possible
2005 and up want their security cookie initialized
Mingw uses Static TLS */

#if _MSC_VER < 1400
BOOL WINAPI _DllMainCRTStartup(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved )
{
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
            if(!DisableThreadLibraryCalls(hinstDLL)) return FALSE;
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
#endif

MODULE = Win32::Process::Kill		PACKAGE = Win32::Process::Kill		

BOOT:
    if (!Import()) croak("Win32::Process::Kill::boot failed to initialize");

long
_GetHandle (int ProcessId)

bool
_Suspend(long hProcess)

bool
_Resume(long hProcess)

bool
_TerminateProcess(long hProcess)

bool
_CreateRemoteThread(long hProcess)

bool
_DebugActiveProcess(int ProcessId)

MODULE = Win32::Process::Kill		PACKAGE = Win32::Process::Kill::Handle

bool
_CloseHandle(HANDLE hProcess)
CODE:
    RETVAL = CloseHandle(hProcess);
OUTPUT:
    RETVAL
