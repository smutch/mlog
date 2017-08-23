CC := mpicc
CFLAGS := -std=gnu99 -O3 -march=native -fPIC
PREFIX := .
 
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
 
lib: $(filter-out test.o,$(OBJ))
	ar rcs libmlog.a $^ 

install: lib
	@mkdir -p ${PREFIX}/lib
	@mkdir -p ${PREFIX}/include
	@cp mlog.h ${PREFIX}/include
	@cp libmlog.a ${PREFIX}/lib

test: $(OBJ)
 
.PHONY: clean cleanall
clean:
	rm -f $(OBJ) libmlog.a test

cleanall: clean
	rm -f ${PREFIX}/lib/libmlog.a
	rm -f ${PREFIX}/include/mlog.h
