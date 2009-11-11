
CC= g++
LIBS = 	-fopenmp 
CFLAGS = -O3 -fopenmp
PROG := membench

all: matrix_booster.a prueba

prueba: prueba.o matrix_booster.a
	$(CC) -O3 $(LIBS) prueba.o -o prueba matrix_booster.a
prueba.o: prueba.cpp
	$(CC) -c $(CFLAGS) prueba.cpp

matrix_booster.a: matrix_booster.o matrix.o 
	ar -rvcs matrix_booster.a matrix_booster.o matrix.o
matrix_booster.o: block.h matrix_booster.cpp matrix_booster.hpp 
	$(CC) -c -O3 -fopenmp matrix_booster.cpp 
matrix.o: matrix.cpp matrix.hpp
	$(CC) -c -O3 matrix.cpp 
block.h: $(PROG)
	./$(PROG) > block.h
$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o
$(PROG).o: $(PROG).c
	$(CC) -c $(CFLAGS) $(PROG).c

clean: 
	rm *.o *.a prueba block.h
