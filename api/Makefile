CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
RM = rm -f
BIN = example
LDLIBS = -lhiredis

SRCS = zset_api.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)
