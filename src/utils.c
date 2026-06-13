#include <stdio.h>
#include <string.h>
#include "utils.h"

typedef struct {
    int port;
    const char *service;
} ServiceMap;

static ServiceMap services[] = {
    {21, "FTP"}, {22, "SSH"}, {23, "Telnet"}, {25, "SMTP"},
    {53, "DNS"}, {80, "HTTP"}, {110, "POP3"}, {143, "IMAP"},
    {443, "HTTPS"}, {445, "SMB"}, {3306, "MySQL"}, {5432, "PostgreSQL"},
    {6379, "Redis"}, {8080, "HTTP-Alt"}, {8443, "HTTPS-Alt"},
    {27017, "MongoDB"}, {0, NULL}
};

const char *get_service_name(int port) {
    for (int i = 0; services[i].service != NULL; i++) {
        if (services[i].port == port) {
            return services[i].service;
        }
    }
    return "unknown";
}

void print_banner(const char *host, const char *ip, int start, int end) {
    printf("\n");
    printf("  Target : %s (%s)\n", host, ip);
    printf("  Ports  : %d - %d\n", start, end);
    printf("  ----------------------------------------\n");
    printf("  PORT      STATE   SERVICE\n");
    printf("  ----------------------------------------\n");
}

void print_result(ScanResult *result) {
    if (result->open) {
        printf("  %-8d  open    %s\n", result->port, get_service_name(result->port));
    }
}

void print_summary(int open_count, int total, double elapsed) {
    printf("  ----------------------------------------\n");
    printf("  %d open port(s) found out of %d scanned\n", open_count, total);
    printf("  Scan completed in %.2f seconds\n\n", elapsed);
}