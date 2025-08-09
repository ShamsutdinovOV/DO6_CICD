CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE
all: s21_cat
s21_cat: s21_cat.o
	$(CC) $(FLAGS) s21_cat.c -o s21_cat
s21_cat.o: ./s21_cat.h s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c	
rebuild: clean s21_cat

clean:
	rm -rf s21_cat.o 
test: s21_cat
	bash s21_cat_test.sh
