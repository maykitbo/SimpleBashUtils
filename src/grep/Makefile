CC=gcc
SRC=s21_grep.c
CFLAGS=-Wall -Werror -Wextra


all: s21_grep clean

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) $^ -o s21_grep

s21_grep.o: $(SRC)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o 
