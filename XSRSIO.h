#pragma once
#include <stdio.h>
#include <stdarg.h>
#include "XSRSSocket.h"
void xsrsIOMode(int mode, void* param);
void xsrsPrintf(const char* format, ...);
void xsrsEPrintf(const char* format, ...);
void xsrsPuts(const char* str);