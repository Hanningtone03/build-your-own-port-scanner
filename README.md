![CI](https://github.com/Hanningtone03/build-your-own-port-scanner/actions/workflows/ci.yml/badge.svg)

# Build Your Own Port Scanner

A TCP port scanner in C; service detection, customizable port ranges, and timeout handling.

## How it works

For each port in the range, a TCP socket is opened and a connection is attempted. If the connection succeeds the port is open. Each socket has a configurable timeout so dead ports don't block the scan. Known ports are mapped to service names.

## Project structure

```
src/
├── main.c
├── scanner.c
├── utils.c
└── utils.h
```

## Building

```bash
gcc -Wall -o scanner src/main.c src/scanner.c src/utils.c -lws2_32
```

## Usage

```bash
./scanner <host> [start_port] [end_port]
```

## Examples

```bash
./scanner localhost
./scanner localhost 1 1024
./scanner 127.0.0.1 80 443
```

## Detected services

FTP, SSH, Telnet, SMTP, DNS, HTTP, POP3, IMAP, HTTPS, SMB, MySQL, PostgreSQL, Redis, MongoDB and more.

## Tech

- C
- POSIX sockets (Linux) / Winsock2 (Windows)
- No external dependencies
