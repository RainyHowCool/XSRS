#pragma once

#include <stdio.h>

#include "XSRSProductInfo.h"

#ifdef WINDOWS
	#include <WinSock2.h>
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	typedef int SOCKET;
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket close
	#define IPPROTO_TCP 0
#endif


#include "XSRSDataType.h"
#include "XSRSIO.h"

#pragma once
int xsrsSocketInitialize();
int xsrsSocketCleanup();
SOCKET* xsrsSocketCreateAndBind(int port);
SOCKET xsrsClientSocketCreateAndConnect(char* host, int port);
void xsrsSocketListen();
