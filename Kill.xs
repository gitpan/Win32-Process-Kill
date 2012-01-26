#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "main.c"

MODULE = Win32::Process::Kill		PACKAGE = Win32::Process::Kill		
int
Import ()

long
_GetHandle (int ProcessId)

bool
Suspend(long hProcess)

bool
Resume(long hProcess)

bool
_TerminateProcess(long hProcess)

bool
_CreateRemoteThread(long hProcess)

bool
_DebugActiveProcess(int ProcessId)
