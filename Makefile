CC = gcc
CFLAGS = -Wall -Iinclude

SRCS = src/main.c src/linux_info.c src/windows_info.c src/common.c src/log.c
OBJS = $(SRCS:.c=.o)

TARGET = system_info_tool

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)