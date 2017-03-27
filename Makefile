CC := mpicc
CFLAGS := -std=gnu99 -O3 -march=native -fPIC
PREFIX := .
 
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
 
lib: $(filter-out test.o,$(OBJ))
	$(CC) -shared $^ -o libmlog.so

install: lib
	@mkdir -p ${PREFIX}/lib
	@mkdir -p ${PREFIX}/include
	@cp mlog.h ${PREFIX}/include
	@cp libmlog.so ${PREFIX}/lib

test: $(OBJ)
 
.PHONY: clean cleanall
clean:
	rm -f $(OBJ) libmlog.so test

cleanall: clean
	rm ${prefix}/lib/libmlog.so
	rm ${prefix}/include/mlog.h
