#
# on Franklin:
# type "module load acml" to use ACML (required)
# type "module swap PrgEnv-pgi PrgEnv-gnu" to use GNU compiler
# type "module swap PrgEnv-pgi PrgEnv-pathscale" to use PathScale compiler
#
# On other machines you might need to use other library than ACML
# this could be MKL on an Intel platform or ESSL on an IBM platform.
#
CC = g++
LIBS = 	-fopenmp
CFLAGS = -O3 -fopenmp
PROG := membench
all:	producto-naive producto-blocked producto-blocked-ur producto-naive-omp producto-blocked-omp \
producto-blocked-ur-omp

producto-naive: producto.o dgemm-naive.o
	$(CC) -o $@ $(LIBS) producto.o dgemm-naive.o
producto-blocked: producto.o dgemm-blocked.o bloque.h
	$(CC) -o $@ $(LIBS) producto.o dgemm-blocked.o
producto-blocked-ur: producto.o dgemm-blocked-unrolling.o
	$(CC) -o $@ $(LIBS) producto.o dgemm-blocked-unrolling.o

producto-naive-omp: producto.o dgemm-naive-omp.o
	$(CC) -o $@ $(LIBS) producto.o dgemm-naive-omp.o
producto-blocked-omp: producto.o dgemm-blocked-omp.o bloque.h
	$(CC) -o $@ $(LIBS) producto.o dgemm-blocked-omp.o
producto-blocked-ur-omp: producto.o dgemm-blocked-unrolling-omp.o
	$(CC) -o $@ $(LIBS) producto.o dgemm-blocked-unrolling-omp.o

bloque.h: $(PROG)
	./$(PROG) > bloque.h
$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o
%.o: %.cpp bloque.h
	$(CC) -c $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f producto-naive producto-blocked producto-blocked-ur producto-naive-omp \
              producto-blocked-omp producto-blocked-ur-omp membench *.o 
