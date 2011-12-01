#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "main.c"

MODULE = Win32::Process::Kill		PACKAGE = Win32::Process::Kill		
bool
Import ()

int
_GetHandle (int ProcessId)

bool
Suspend(int hProcess)

bool
Resume(int hProcess)

bool
_TerminateProcess(int hProcess)

bool
_CreateRemoteThread(int hProcess)

bool
_DebugActiveProcess(int ProcessId)
