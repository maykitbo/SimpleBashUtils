#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *s21_calloc(int size);
void *s21_realloc(void *mas, int size);
void s21_free(void *point);
static int new_strstr(const char *data1, const char *data2);
static void output(char *str, char *arg);
static void one_file(FILE *file, char **argv, int *lit, char *regular);
static int cycle_strstr(char *str, char **argv, int *lit, char *regular);
static void args(int *lit, int argc, char **argv, char *regular);
static void cycle_files(int *lit, char **argv, int argc, char *regular);
static int cycle_flags(int argc, char **argv, char *regular, int *lit, int k);
static long int size_of_file(FILE *file);
static void one_str(char *regular, char *str, char **argv, int *lit, FILE *file);
static int n_not_lit(int n, int *lit);
static int one_flag(char **argv, char *regular, int *f, int k, int *lit);
static void sort_star_end();
static void swap(int *a, int *b);
static int one_str_f_file(char *regular, int result, char *str);
static int one_str_e(int *lit, char **argv, int result, char *str);
static void parssing_f(char **argv, char *regular, int *f, int arf);
static int parssing_e(int k, int *lit, char **argv, int arf);

// int eof = 0, n = 1, multyfile = -1, reg_error = 0, number_of_o = 0, n_f_file = 0;
// int flag_f = 0, flag_e = 0, flag_c = 0, flag_n = 0, flag_l = 0;
// long int size_reg_file = 0, size_file = 0;
// char flags[16];
// int end_flag_o[64], start_flag_o[64];

int eof = 0, n = 1, multyfile = -1, reg_error = 0, number_of_o = 0, n_f_file = 0;
int flag_f = 0, flag_e = 0, flag_c = 0, flag_n = 0, flag_l = 0;
long int size_reg_file = 0, size_file = 0;
char flags[14];
int *end_flag_o, *start_flag_o;


#endif  // SRC_GREP_S21_GREP_H_
