#ifndef UTILS_H
#define UTILS_H

#define MAX_PORTS 65535
#define TIMEOUT_SEC 1
#define MAX_THREADS 100

typedef struct {
    char *host;
    int port;
    int open;
} ScanResult;

const char *get_service_name(int port);
char *resolve_host(const char *host);
void print_banner(const char *host, const char *ip, int start, int end);
void print_result(ScanResult *result);
void print_summary(int open_count, int total, double elapsed);

#endif