CC=gcc
SRC=s21_cat.c
CFLAGS=-Wall -Werror -Wextra

all: s21_cat clean

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) $^ -o s21_cat

s21_cat.o: $(SRC)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o 
