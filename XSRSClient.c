#include "XSRSClient.h"

int main()
{
	xsrsIOMode(2, NULL); // Set IO mode to console
	char buffer[256];
	int port = 0;
	xsrsLogoShow("Client");
	printf("XSRS Client started successfully.\n");
	printf("Hostname or IP: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
	fflush(stdout);
	printf("Port: ");
	fflush(stdout);
	int ret = scanf("%d", &port);
	printf("Connecting to %s:%d...\n", buffer, port);
	SOCKET socketClient = xsrsClientSocketCreateAndConnect(buffer, port);
	if (socketClient == INVALID_SOCKET) {
		xsrsEPrintf("Failed to connect to server.\n");
		return 1;
	}
	xsrsIOMode(1, socketClient); // Set IO mode to socket
	printf("Shakehaning...\n");
	char recvBuffer[256] = { 0 };
	int nBytesRead = recv(socketClient, recvBuffer, sizeof(recvBuffer), 0);
	if (nBytesRead <= 0) {
		xsrsIOMode(2, NULL); // Set IO mode back to console
		xsrsEPrintf("Failed to receive handshake response.\n");
		return 1;
	}
	if (nBytesRead > 255) return 0;
	recvBuffer[nBytesRead] = 0; // Null-terminate the received data
	if (strcmp(recvBuffer, "XSSR0001") != 0) {
		xsrsIOMode(2, NULL); // Set IO mode back to console
		xsrsEPrintf("Handshake failed!\n");
		return 1;
	}
	xsrsPrintf("XSCT0001");
	printf("Done!\n");
	while (True) {
		printf("XSRS Client> ");
		fflush(stdout);
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
		xsrsPrintf(buffer);
	}
	return 0;
}