#include "XSRSSocket.h"

SOCKET socketServer;

int xsrsSocketInitialize() 
{
#ifdef WINDOWS
	// Initialization code for XSRS Socket (Windows)
	WSADATA wsaData;
	int iResult;

	if ((iResult = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		// Handle error
		fprintf(stderr, "WSAStartup failed: %d\n", iResult);
		return iResult;
	}
#endif

	return 0; // Success
}

int xsrsSocketCleanup() 
{
	// Cleanup code for XSRS Socket
	closesocket(socketServer);
#ifdef WINDOWS
	int iResult;
	if ((iResult = WSACleanup()) != 0) {
		// Handle error
		fprintf(stderr, "WSACleanup failed: %d\n", iResult);
		return iResult;
	}
#endif
	return 0; // Success
}

SOCKET* xsrsSocketCreateAndBind(int port)
{
	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// SockAddr_in structure for binding
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
#ifdef WINDOWS
	serverAddr.sin_addr.s_addr = INADDR_ANY;
#else
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif

	// Bind it
	bind(socketServer, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	return &socketServer;
}

SOCKET* xsrsClientSocketCreateAndConnect(char *host, int port)
{
	// Create socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// SockAddr_in structure for connecting
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
#ifdef WINDOWS
	serverAddr.sin_addr.s_addr = inet_addr(host);
#else
	inet_pton(AF_INET, host, &serverAddr.sin_addr);
#endif
	// Connect to server
	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	return &clientSocket;
}

static void xsrsSocketHandle(SOCKET clientSocket)
{
	// Shake-Hand and receive data
	u8 buffer[1024] = {0};
	u8 sendBuffer[2048] = {0};
	int bytesReceived = recv(clientSocket, (char*)buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived > 0) {
		buffer[bytesReceived] = '\0'; // Null-terminate the received data
		xsrsPrintf("Received: %s\n", buffer);
	}
	if (strcmp((char*)buffer, "exit") == 0) {
		// If client sends "exit", close the connection
		xsrsPrintf("Closing connection with client.\n");
		closesocket(clientSocket);
		xsrsIOMode(2, NULL); // Set IO mode back to console
		return;
	}
}

void xsrsSocketListen()
{
	listen(socketServer, SOMAXCONN);
	// start to listen
	SOCKET clientSocket;
	while (True) {
		clientSocket = accept(socketServer, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			continue; // Accept failed, continue to next iteration
		}
		xsrsIOMode(1, &clientSocket); // Set IO mode to console for server messages
		// Handle client connection
		xsrsPrintf("XSSR0001");
		u8 buffer[64] = { 0 };
		int bytesReceived = recv(clientSocket, (char*)buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived > 0) {
			buffer[bytesReceived] = '\0'; // Null-terminate the received data
			if (strcmp((char*)buffer, "XSCT0001") != 0) {
				xsrsEPrintf("Invalid client handshake. Closing connection.\n");
				closesocket(clientSocket);
				xsrsIOMode(2, NULL); // Set IO mode back to console
				continue; // Invalid handshake, continue to next iteration
			}
		}
		while (True) {
			xsrsSocketHandle(clientSocket);
		}
	}
}