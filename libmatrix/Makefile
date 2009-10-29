
CC= g++
LIBS = 	-fopenmp 
CFLAGS = -O3 -fopenmp
PROG := membench

all: matrix_booster.a prueba

prueba: prueba.o matrix_booster.a
	$(CC)  $(LIBS) prueba.o -o prueba matrix_booster.a
prueba.o: prueba.cpp
	$(CC) -c $(CFLAGS) prueba.cpp

matrix_booster.a: matrix_booster.o
	ar -rvcs matrix_booster.a matrix_booster.o
matrix_booster.o: block.h matrix_booster.cpp
	$(CC) -c $(CFLAGS) matrix_booster.cpp

block.h: $(PROG)
	./$(PROG) > block.h
$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o
$(PROG).o: $(PROG).c
	$(CC) -c $(CFLAGS) $(PROG).c

clean: 
	rm *.o *.a prueba block.h
