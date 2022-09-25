CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = 
LDLIBS = -lm

ALL : convert solve

convert : convert.o matrice2d.o tsp.o memoire.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

solve : solve.o matrice2d.o tsp.o memoire.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

solve.o : solve.c tsp.h matrice2d.h
convert.o : convert.c tsp.h matrice2d.h
matrice2d.o : matrice2d.c matrice2d.h memoire.h
memoire.o: memoire.c memoire.h
tsp.o: tsp.c tsp.h matrice2d.h memoire.h

.PHONY : clean
clean :
	-rm -f *.o convert solve