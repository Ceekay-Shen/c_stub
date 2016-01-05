CC = gcc
CFLAGS = -g -W

HEADERS := $(wildcard *.h)
SRCS := c_stub.c
OBJS := ${patsubst %.c, %.o, $(SRCS)}
TARGETS := c_stub


all : $(TARGETS)

$(TARGETS) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJS)
distclean : clean
	rm -f $(TARGETS)

