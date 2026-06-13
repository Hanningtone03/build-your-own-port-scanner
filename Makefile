CC = gcc
CFLAGS = -Wall -O2
TARGET = scanner
SRCS = src/main.c src/scanner.c src/utils.c

ifeq ($(OS),Windows_NT)
    LIBS = -lws2_32
    TARGET = scanner.exe
else
    LIBS =
endif

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)