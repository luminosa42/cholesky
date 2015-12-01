SHELL=/bin/bash

CC=mpiicc
CCFLAGS = -std=c99 -O2

SRC=cholesky_serial.c cholesky_1d.c cholesky_2d.c
EXE=$(SRC:.c=.exe)
MIC=$(SRC:.c=.mic)

all: $(EXE) $(MIC)

%.exe: %.c
	$(CC) $(CCFLAGS) -fopenmp $< -o $@

%.mic: %.c
	$(CC) $(CCFLAGS) -openmp -mmic $< -o $@

clean:
      	rm -f *.o $(EXE) $(MIC) out_taub.txt out_mic.txt
