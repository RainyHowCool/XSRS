#include "XSRSIO.h"

FILE* xsrsIOFile = NULL;
SOCKET xsrsIOSocket = INVALID_SOCKET;
int gMode = 0;
void xsrsIOMode(int mode, void* param)
{
	gMode = mode;
	if (mode == 0) {
		xsrsIOFile = (FILE*)param;
	}
	else if (mode == 1) {
		xsrsIOSocket = *(SOCKET*)param;
	}
}

void xsrsPrintf(const char* format, ...)
{
	char buffer[4096];
	va_list aptr;

	va_start(aptr, format);
	vsprintf(buffer, format, aptr);
	va_end(aptr);

	if (gMode == 0 && xsrsIOFile != NULL) {
		fputs(buffer, xsrsIOFile);
	} else if (gMode == 1 && xsrsIOSocket != INVALID_SOCKET) {
		send(xsrsIOSocket, buffer, (int)strlen(buffer), 0);
	} else if (gMode == 2) {
		fputs(buffer, stdout);
	}
}

void xsrsEPrintf(const char* format, ...)
{
	char buffer[4096];
	va_list aptr;

	va_start(aptr, format);
	vsprintf(buffer, format, aptr);
	va_end(aptr);
	if (gMode == 0 && xsrsIOFile != NULL) {
		fputs(buffer, xsrsIOFile);
	} else if (gMode == 1 && xsrsIOSocket != INVALID_SOCKET) {
		send(xsrsIOSocket, buffer, (int)strlen(buffer), 0);
	} else if (gMode == 2) {
		fputs(buffer, stderr);
	}
}

void xsrsPuts(const char* str)
{
	if (gMode == 0 && xsrsIOFile != NULL) {
		fputs(str, xsrsIOFile);
		fputc('\n', xsrsIOFile);
	} else if (gMode == 1 && xsrsIOSocket != INVALID_SOCKET) {
		send(xsrsIOSocket, str, (int)strlen(str), 0);
		send(xsrsIOSocket, "\n", 1, 0);
	} else if (gMode == 2) {
		fputs(str, stdout);
		fputc('\n', stdout);
	}
}