NAME = "app"
CC = g++
CFLAGS =-Wall -Wextra -Werror -std=c++17
CFLAGS_GCOV =-fprofile-arcs --coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=
  CHECK_LEAKS=CK_FORK=no valgrind --leak-check=full -s --log-file=log.txt
else
  LIBS=
  CHECK_LEAKS=no leaks -atExit --
endif

all: install

install:
	rm -rf build
	mkdir build
	$(CC) $(CFLAGS) liquid.cpp main.cpp -o build/$(NAME)

clean:
	rm -rf build

tests:

style:
	cp ../.clang-format .
	clang-format -n *.cpp *.hpp
	clang-format -i *.cpp *.hpp
	rm .clang-format

#gcov_report: tests
#	gcovr --html-details coverage.html
#	open coverage.html
