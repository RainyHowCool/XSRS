#include "XSRSClient.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>  // ȷ������bool���Ͷ���

int main()
{
    xsrsIOMode(2, NULL); // ����IOģʽΪ����̨
    char buffer[256];
    int port = 0;
    xsrsLogoShow("Client");
    printf("XSRS Client started successfully.\n");

    // ��ȡ��������ַ
    printf("Hostname or IP: ");
    fflush(stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        xsrsEPrintf("Input error for hostname.\n");
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = 0; // �Ƴ����з�

    // ��ȡ�˿ں�
    printf("Port: ");
    fflush(stdout);
    int ret = scanf("%d", &port);
    if (ret != 1 || port < 1 || port > 65535) { // ���˿���Ч��
        xsrsEPrintf("Invalid port input.\n");
        return 1;
    }
    // ������뻺����ʣ��Ļ��з�
    while (getchar() != '\n');

    // ���ӷ�����
    printf("Connecting to %s:%d...\n", buffer, port);
    SOCKET socketClient = xsrsClientSocketCreateAndConnect(buffer, port);
    if (socketClient == INVALID_SOCKET) {
        xsrsEPrintf("Failed to connect to server.\n");
        return 1;
    }

    // �������̣��Ƚ��շ�������Ӧ���ٷ��Ϳͻ���ȷ��
    printf("Shaking hands...\n");
    char recvBuffer[256] = { 0 };
    // ѭ������������������Ӧ������TCP�ְ���
    int totalRead = 0;
    int expectedLen = strlen("XSSR0001");
    while (totalRead < expectedLen) {
        int nBytesRead = recv(socketClient, recvBuffer + totalRead, expectedLen - totalRead, 0);
        if (nBytesRead == SOCKET_ERROR) {
            xsrsEPrintf("Failed to receive handshake (recv error).\n");
            closesocket(socketClient);
            return 1;
        }
        else if (nBytesRead == 0) {
            xsrsEPrintf("Server closed connection during handshake.\n");
            closesocket(socketClient);
            return 1;
        }
        totalRead += nBytesRead;
    }
    recvBuffer[totalRead] = '\0'; // ȷ���ַ�����ֹ

    // ��֤��������Ӧ
    if (strcmp(recvBuffer, "XSSR0001") != 0) {
        xsrsEPrintf("Handshake failed! Unexpected response: %s\n", recvBuffer);
        closesocket(socketClient);
        return 1;
    }

    // ���Ϳͻ���ȷ��
    xsrsIOMode(1, &socketClient); // �л�IOģʽ��socket
    if (send(socketClient, "XSCT0001", strlen("XSCT0001"), 0) <= 0) {
        xsrsIOMode(2, NULL);
        xsrsEPrintf("Failed to send client handshake.\n");
        closesocket(socketClient);
        return 1;
    }

    printf("Handshake successful! Enter commands (Ctrl+C to exit).\n");
    while (true) { // ʹ�ñ�׼bool����
        printf("XSRS Client> ");
        fflush(stdout);
        // ��ȡ�û�����
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            xsrsEPrintf("Input error, exiting.\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0; // �Ƴ����з�
        // �������������
        if (send(socketClient, buffer, strlen(buffer), 0) <= 0) {
            xsrsEPrintf("Failed to send data, connection closed.\n");
            break;
        }
    }

    // ������Դ
    xsrsIOMode(2, NULL);
    closesocket(socketClient);
    return 0;
}