CC=gcc
CXXFLAGS:=-g -std=c++17 -Wall -Wextra -Werror
GCOVFLAGS:=-ftest-coverage -fprofile-arcs
OS:=

ifeq ($(shell uname), Linux)
	LDFLAGS:=-lgcov -lpthread -lsubunit -lrt -lm
	OS=Linux
endif

ifeq ($(shell uname), Darwin)
	# LDFLAGS:=-lgcov -lpthread -fprofile-args -lm
	OS=Darwin
endif

HEADERS_DIR:= ./includes

all: s21_matrix_oop.a s21_matrix_oop_gcov.a move_lib

s21_matrix_oop_gcov.a: s21_matrix_oop_gcov.o
	@echo "create static lib gcov"
	ar -src $@ ./gcov_obj/s21_matrix_oop_gcov.o

s21_matrix_oop.a: s21_matrix_oop.o
	@echo "create static lib"
	ar -src $@ ./objects/s21_matrix_oop.o

test: rebuild
	cd ./tests && rm -rf BUILD && cmake -B ./BUILD && make -C ./BUILD
	./test_matrix_oop # --gtest_filter=TestMatrixOOP.ForSingle

s21_matrix_oop.o:
	$(CC) -g $(CXXFLAGS) -I ${HEADERS_DIR} -c srcs/s21_matrix_oop.cpp -o objects/s21_matrix_oop.o

s21_matrix_oop_gcov.o:
	$(CC) -g $(CXXFLAGS) $(GCOVFLAGS) $(LDFLAGS) -I ${HEADERS_DIR} -c srcs/s21_matrix_oop.cpp -o gcov_obj/s21_matrix_oop_gcov.o

move_lib:
	cp ./includes/s21_matrix_oop.h ./
	mkdir -p lib && cp s21_matrix_oop.a ./lib && cp ./includes/s21_matrix_oop.h ./lib && mv s21_matrix_oop_gcov.a ./lib

rebuild: clean all

gcov_report: test
	lcov -c -d  gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
ifeq ($(OS), Linux)
	firefox ./out/index.html
else
	open ./out/index.html
endif



clean:
	rm -f ./test_matrix_oop
	rm -f ./s21_matrix_oop.a
	rm -f ./s21_matrix_oop.h
	rm -rf ./lib
	rm -rf ./objects/*
	rm -rf ./tests/BUILD
	rm -rf ./tests/Makefile
	rm -rf ./out
	rm -rf ./gcov_obj/*

check:
	echo "processing..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~";

fix:
	echo "processing..."
	./clang_custom.sh i
	echo "~~~ $@ DONE ~~~";

.PHONY: all clean rebuild s21_matrix_oop.a s21_matrix_oop_gcov.a check fix test
