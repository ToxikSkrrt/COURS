CC=gcc
LEX=flex
YACC=bison
YFLAGS=-d -v -t #-Wcounterexamples
LDLIBS=-ll -lm -lgmp
CFLAGS=-std=gnu99 -MMD -Wall -pedantic -Wextra -Wshadow -Wpointer-arith	\
-Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

# Pour MacOS (homebrew)
CPPFLAGS=-I/opt/homebrew/include
LDFLAGS=-L/opt/homebrew/lib

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:%.c=%.o)
DEPS := $(SOURCES:%.c=%.d)

# Compilation en mode debug par défaut, pour utiliser gdb et valgrind, et avec les warnings en erreur.
all: CFLAGS += -g -O0 -Werror
all: tp

# Une fois que le programme fonctionne, mode optimisé et sans erreur en cas de warning.
nowerror: CFLAGS += -O3
nowerror: tp

tp: parser.o scan.o $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^ $(LDLIBS)

# Inclusion des dépendances générées par gcc -MMD.
-include $(DEPS)

.PHONY: clean
clean:
	rm -f *.o *.d core tp parser.tab.h parser.tab.c parser.c parser.output y.tab.h y.output lex.yy.c
