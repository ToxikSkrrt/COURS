# Makefile correction of foobar

# standard variables
CC= gcc
AR= ar
CPPFLAGS=
CFLAGS= -Wall -std=c99
LDFLAGS= -L.
LDLIBS= -lfb -lm # -lm is required for sqrt()

# main target
ALL: foobar

# explicit compilation rules
libfb.a: bar.o foo.o
	$(AR) rcs $@ $^

foobar: foobar.o libfb.a
	$(CC) $(LDFLAGS) $< -o $@ $(LDLIBS)

# implicit compilation rules
foobar.o: foobar.c bar.h foo.h
bar.o: bar.c bar.h
foo.o: foo.c foo.h

# clean rule
.PHONY : clean
clean :
	-rm -f *.o *.a foobar

