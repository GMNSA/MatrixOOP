CC=g++
CFLAGS=-g -p -Wall -Wextra -Werror -std=c++17
GCOVFLAGS:=-fprofile-arcs -ftest-coverage -fsanitize=address
LDFLAGS:=-lcheck -lgcov -fsanitize=address

ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck -fsanitize=address # -lsubunit -lrt -lm 
endif

SOURCES:= srcs/s21_matrix_oop.cpp
HEADERS_DIR:= ./includes
HEADERS:= includes/s21_matrix_oop.h

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean rebuild check

all: s21_matrix_oop.a  move_lib

#build: #test s21_matrix_oop.a 

s21_matrix_oop.a: $(OBJECTS)
	@echo "create static lib"
	ar -src $@ $(OBJECTS) ${HEADERS}

test: rebuild s21_matrix_oop.a
	./run.sh && ./tests/BUILD/bin/testMatrixOOP

.cpp.o:
	@echo "Compiling"
	$(CC) -g -Wall -Werror -Wextra -I ${HEADERS_DIR} -c $< -o $@

move_lib:
	mkdir -p lib && mv s21_matrix_oop.a ./lib && cp ./includes/s21_matrix_oop.h lib

rebuild: clean all

clean:
	rm -f ./a.out
	rm -rf ./lib
	rm -rf ./tests/BUILD
	rm -rf ./tests/Makefile

check:
	clang-format -n ./includes/*.h ./srcs/*.cpp ./tests/includes/*.h ./tests/srcs/test_matrix_oop.cpp
