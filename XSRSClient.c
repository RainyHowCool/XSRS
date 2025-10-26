#include "XSRSClient.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>  // 确保包含bool类型定义

int main()
{
    xsrsIOMode(2, NULL); // 设置IO模式为控制台
    char buffer[256];
    int port = 0;
    xsrsLogoShow("Client");
    printf("XSRS Client started successfully.\n");

    // 获取服务器地址
    printf("Hostname or IP: ");
    fflush(stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        xsrsEPrintf("Input error for hostname.\n");
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = 0; // 移除换行符

    // 获取端口号
    printf("Port: ");
    fflush(stdout);
    int ret = scanf("%d", &port);
    if (ret != 1 || port < 1 || port > 65535) { // 检查端口有效性
        xsrsEPrintf("Invalid port input.\n");
        return 1;
    }
    // 清除输入缓冲区剩余的换行符
    while (getchar() != '\n');

    // 连接服务器
    printf("Connecting to %s:%d...\n", buffer, port);
    SOCKET socketClient = xsrsClientSocketCreateAndConnect(buffer, port);
    if (socketClient == INVALID_SOCKET) {
        xsrsEPrintf("Failed to connect to server.\n");
        return 1;
    }

    // 握手流程：先接收服务器响应，再发送客户端确认
    printf("Shaking hands...\n");
    char recvBuffer[256] = { 0 };
    // 循环接收完整的握手响应（处理TCP分包）
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
    recvBuffer[totalRead] = '\0'; // 确保字符串终止

    // 验证服务器响应
    if (strcmp(recvBuffer, "XSSR0001") != 0) {
        xsrsEPrintf("Handshake failed! Unexpected response: %s\n", recvBuffer);
        closesocket(socketClient);
        return 1;
    }

    // 发送客户端确认
    xsrsIOMode(1, &socketClient); // 切换IO模式到socket
    if (send(socketClient, "XSCT0001", strlen("XSCT0001"), 0) <= 0) {
        xsrsIOMode(2, NULL);
        xsrsEPrintf("Failed to send client handshake.\n");
        closesocket(socketClient);
        return 1;
    }

    printf("Handshake successful! Enter commands (Ctrl+C to exit).\n");
    while (true) { // 使用标准bool类型
        printf("XSRS Client> ");
        fflush(stdout);
        // 读取用户输入
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            xsrsEPrintf("Input error, exiting.\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0; // 移除换行符
        // 发送命令到服务器
        if (send(socketClient, buffer, strlen(buffer), 0) <= 0) {
            xsrsEPrintf("Failed to send data, connection closed.\n");
            break;
        }
    }

    // 清理资源
    xsrsIOMode(2, NULL);
    closesocket(socketClient);
    return 0;
}