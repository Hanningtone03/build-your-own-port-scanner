#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include "utils.h"

char *resolve_host(const char *host) {
    struct hostent *he;
    struct in_addr **addr_list;

#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    he = gethostbyname(host);
    if (he == NULL) return NULL;

    addr_list = (struct in_addr **)he->h_addr_list;
    char *ip = malloc(16);
    strcpy(ip, inet_ntoa(*addr_list[0]));
    return ip;
}

int scan_port(const char *ip, int port) {
#ifdef _WIN32
    SOCKET sock;
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return 0;
#else
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;
#endif

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));

    int result = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif

    return result == 0 ? 1 : 0;
}

void scan_range(const char *host, const char *ip, int start, int end) {
    int open_count = 0;
    int total = end - start + 1;

    print_banner(host, ip, start, end);

    clock_t begin = clock();

    for (int port = start; port <= end; port++) {
        int open = scan_port(ip, port);
        if (open) {
            ScanResult result = {(char *)host, port, open};
            print_result(&result);
            open_count++;
        }
    }

    clock_t end_time = clock();
    double elapsed = (double)(end_time - begin) / CLOCKS_PER_SEC;

    print_summary(open_count, total, elapsed);
}