
CC= g++
LIBS = 	-fopenmp
CFLAGS = -O3 -fopenmp
PROG := membench

all: matrix_booster.o prueba

prueba: prueba.cpp matrix_booster.o
	$(CC)  -O3 -fopenmp matrix_booster.o prueba.cpp -o prueba

matrix_booster.o: block.h matrix_booster.cpp
	$(CC) -c  -O3 -fopenmp matrix_booster.cpp

block.h: $(PROG)
	./$(PROG) > block.h
$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o
%.o: %.cpp block.h
	$(CC) -c $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(CFLAGS) $<
