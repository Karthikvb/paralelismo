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
LIBS = 	-lblas
CFLAGS = -O3

all:	benchmark-naive benchmark-blocked benchmark-blocked_ur

benchmark-naive: benchmark.o dgemm-naive.o
	$(CC) -o $@ benchmark.o dgemm-naive.o
benchmark-blocked: benchmark.o dgemm-blocked.o
	$(CC) -o $@ benchmark.o dgemm-blocked.o
benchmark-blocked_ur: benchmark.o dgemm-blocked_unrolling.o
	$(CC) -o $@ benchmark.o dgemm-blocked_unrolling.o
benchmark-blas: benchmark.o dgemm-blas.o
	$(CC) -o $@ benchmark.o dgemm-blas.o

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f benchmark-naive benchmark-blocked benchmark-blas *.o
