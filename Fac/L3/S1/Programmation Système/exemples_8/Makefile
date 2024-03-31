.PHONY: clean all

SOURCES	:= $(wildcard *.c)
PROGS	:= $(SOURCES:%.c=%)

CC		:= gcc
CFLAGS	:= -Wall -fopenmp

all: $(PROGS)

clean:
	rm -fr $(PROGS) *.dSYM
