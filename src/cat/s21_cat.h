#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void flag_n(char *flags, int *numstr_n);
static int find_flags(char *flags, int argc, char **argv, int *fil);
static int one_flag(char **argv, int n, int f, char *flags);
static void cycle_files(int ind_fil, char **argv, int *fil, char *flags);
static void one_file(FILE *file, char *flags);
static int flag_s(int *s, char *flags, char c, int* numstr_n);
static void flag_e(char *flags, char c);
static char output(char c, char *flags, FILE *file, int *s);

// void *s21_calloc(int size);
// void *s21_realloc(void *mas, int size);
// void s21_free(void *point);

#endif  // SRC_CAT_S21_CAT_H_
