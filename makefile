CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11
OPENMP = -fopenmp
DEBUG = -g

all: build_folders procedural distribuida

procedural: src/procedural.c 
	$(CC) $(CFLAGS) -o src/bin/procedural src/procedural.c $(OPENMP)

distribuida: src/parallel.c 
	$(CC) $(CFLAGS) -o src/bin/paralela src/parallel.c $(OPENMP)

procedural_debug: src/procedural.c 
	$(CC) $(CFLAGS) $(DEBUG) -o src/bin/debug/procedural_dbg src/procedural.c $(OPENMP)

distribuida_debug: src/parallel.c 
	$(CC) $(CFLAGS) $(DEBUG) -o src/bin/debug/paralela_dbg src/parallel.c $(OPENMP)

build_folders:
	mkdir -p ./src/obj ./src/bin ./src/bin/debug

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem src/ 2>err.txt

clean:
	rm -f -r ./src/bin ./src/obj /src/bin/* /src/obj/*