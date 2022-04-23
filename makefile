CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wconversion -pedantic -std=gnu11
OPENMP = -fopenmp

all: build_folders procedural distribuida

procedural: src/procedural.c src/include/bodies/utils.c
	$(CC) $(CFLAGS) $(OFLAGS) -o src/bin/procedural src/procedural.c src/include/bodies/utils.c

distribuida: src/procedural.c src/include/bodies/utils.c
	$(CC) $(CFLAGS) $(OFLAGS) -o src/bin/paralela src/parallel.c src/include/bodies/utils.c

build_folders:
	mkdir -p ./src/obj ./src/bin 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem src/ 2>err.txt

clean:
	rm -f -r ./src/bin ./src/obj /src/bin/* /src/obj/*