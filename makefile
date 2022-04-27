CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11
OPENMP = -fopenmp
GPROF = -pg

all: build_folders procedural distribuida ambos

procedural: src/procedural.c 
	$(CC) $(CFLAGS) $(OFLAGS) $(GPROF) -o src/bin/procedural src/procedural.c $(OPENMP)

distribuida: src/procedural.c 
	$(CC) $(CFLAGS) $(OFLAGS) $(GPROF) -o src/bin/paralela src/parallel.c $(OPENMP)

build_folders:
	mkdir -p ./src/obj ./src/bin 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem src/ 2>err.txt

ambos: src/both.c
	$(CC) $(CFLAGS) $(OFLAGS) $(GPROF) -pg -o src/bin/both src/both.c $(OPENMP)

clean:
	rm -f -r ./src/bin ./src/obj /src/bin/* /src/obj/*