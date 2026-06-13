#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern char *resolve_host(const char *host);
extern void scan_range(const char *host, const char *ip, int start, int end);

void usage(const char *program) {
    printf("\nUsage: %s <host> [start_port] [end_port]\n", program);
    printf("  host        Target hostname or IP\n");
    printf("  start_port  Start of port range (default: 1)\n");
    printf("  end_port    End of port range (default: 1024)\n");
    printf("\nExamples:\n");
    printf("  %s localhost\n", program);
    printf("  %s localhost 1 1024\n", program);
    printf("  %s 127.0.0.1 80 443\n\n", program);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    char *host = argv[1];
    int start_port = argc >= 3 ? atoi(argv[2]) : 1;
    int end_port = argc >= 4 ? atoi(argv[3]) : 1024;

    if (start_port < 1 || end_port > MAX_PORTS || start_port > end_port) {
        printf("Invalid port range. Use 1-%d.\n", MAX_PORTS);
        return 1;
    }

    char *ip = resolve_host(host);
    if (ip == NULL) {
        printf("Could not resolve host: %s\n", host);
        return 1;
    }

    scan_range(host, ip, start_port, end_port);
    free(ip);
    return 0;
}