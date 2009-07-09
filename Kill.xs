#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "main.c"

MODULE = Win32::Process::Kill		PACKAGE = Win32::Process::Kill		
int
Terminate (int ProcessId)
