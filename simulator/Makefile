CC = gcc
CFLAGS = -g
SRCS = memory.c simulator.c
TARGET = simulator

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

