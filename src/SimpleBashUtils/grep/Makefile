CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE 
all: s21_grep
s21_grep: s21_grep.o
	$(CC) $(FLAGS) s21_grep.c -o s21_grep
s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(FLAGS) -c s21_grep.c 
rebuild: clean s21_grep
clean:
	-rm -rf s21_grep
test: s21_grep
	bash test_grep.sh
