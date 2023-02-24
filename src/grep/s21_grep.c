#include "s21_grep.h"

int main(int argc, char *argv[]) {
    start_flag_o = s21_calloc(sizeof(int));
    end_flag_o = s21_calloc(sizeof(int));
    int lit[64];
    for (int k = 0; k < 64; k++) {
        lit[k] = 0;
    }
    char regular[1024];
    args(lit, argc, argv, regular);
    cycle_files(lit, argv, argc, regular);
    s21_free(start_flag_o); s21_free(end_flag_o);
    return 0;
}

static void args(int *lit, int argc, char **argv, char *regular) {
    int k = 1;
    for (int g = 0; g < 14; g++) {
        flags[g] = '\0';
    }
    for (int g = 0; g < 1024; g++) {
        regular[g] = '\0';
    }
    k = cycle_flags(argc, argv, regular, lit, k);
    if (!strchr(flags, 's') && reg_error != 0) {
        printf("%s: No such file or directory\n", argv[reg_error]);
    }
    lit[0] = k;
}

static int cycle_flags(int argc, char **argv, char *regular, int *lit, int k) {
    int f = 0;
    while (n < argc) {
        if (argv[n][0] == '-') {
            k = one_flag(argv, regular, &f, k, lit);
        } else if (lit[0] != -1 && !flag_f && !flag_e) {
            lit[k] = n;
            lit[0] = -1;
        } else {
            multyfile++;
        }
        n++;
    }
    n = 1;
    return k;
}

static int one_flag(char **argv, char *regular, int *f, int k, int *lit) {
    int arf = 0;
    if (argv[n][1] == 'f') {
        parssing_f(argv, regular, f, arf);
    } else if (argv[n][1] == 'e') {
        k = parssing_e(k, lit, argv, arf);
    } else if (argv[n][0] == '-') {
        while (argv[n][arf + 1]) {
            if (argv[n][arf + 1] == 'f') {
                parssing_f(argv, regular, f, arf);
                break;
            }
            flags[*f] = argv[n][arf + 1];
            arf++;
            *f = *f + 1;
        }
    }
    return k;
}

static void parssing_f(char **argv, char *regular, int *f, int arf) {
    FILE *reg_file;
    if (argv[n][arf + 2]) {
        reg_file = fopen(&argv[n][2], "r");
        n--;
    } else {
        reg_file = fopen(argv[n + 1], "r");
    }
    n_f_file = n + 1;
    flags[*f] = 'f';
    *f = *f + 1;
    if (reg_file == NULL) {
        reg_error = n + 1;
    } else {
        size_reg_file = size_of_file(reg_file);
        fread(regular, sizeof(char), size_reg_file, reg_file);
    }
    fclose(reg_file);
    n += 1;
    flag_f = 1;
}

static int parssing_e(int k, int *lit, char **argv, int arf) {
    if (!argv[n][arf + 2]) {
        lit[k] = n + 1;
        n += 1;
    } else {
        lit[k] = -1 * n;
    }
    k++;
    flag_e = 1;
    return k;
}

static void cycle_files(int *lit, char **argv, int argc, char *regular) {
    while (n < argc) {
        if (argv[n][0] != '-' && n_not_lit(n, lit) && n != n_f_file) {
            flag_n = 0; flag_c = 0; flag_l = 0;
            FILE *file = fopen(argv[n], "r");
            if (file == NULL) {
                if (!strchr(flags, 's')) {
                    printf("grep: %s: No such file or directory\n", argv[n]);
                }
            } else {
                one_file(file, argv, lit, regular);
                fclose(file);
            }
        }
        n++;
    }
}

static int n_not_lit(int n, int *lit) {
    int result = 1;
    for (int k = lit[0]; k > 0; k--) {
        if (n == lit[k]) {
            result = 0;
            break;
        }
    }
    return result;
}

static void one_file(FILE *file, char **argv, int *lit, char *regular) {
    size_file = size_of_file(file);
    char *str = s21_calloc(sizeof(char) * (size_file + 1));
    one_str(regular, str, argv, lit, file);
    if (eof && (!strchr(flags, 'o') || (strchr(flags, 'o') && strchr(flags, 'v')))) {
        printf("\n");
    }
    if (strchr(flags, 'c')) {
        if (multyfile && !strchr(flags, 'h')) {
            printf("%s:", argv[n]);
        }
        printf("%d\n", flag_c);
    }
    if (flag_l) {
        printf("%s\n", argv[n]);
    }
    s21_free(str);
}

static void one_str(char *regular, char *str, char **argv, int *lit, FILE *file) {
    while (fgets(str, size_file + 1, file) && size_file) {
        eof = 0;
        flag_n++;
        if (strchr(flags, 'l')) {
            if (cycle_strstr(str, argv, lit, regular)) {
                flag_l++;
                flag_c++;
                break;
            }
        } else if (cycle_strstr(str, argv, lit, regular)) {
            if (!strchr(flags, 'c')) {
                output(str, argv[n]);
            }
            flag_c++;
        }
        for (int i = 0; i < size_file; i++) {
            str[i] = '\0';
        }
    }
}

static long int size_of_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

static int cycle_strstr(char *str, char **argv, int *lit, char *regular) {
    int result = 0;
    number_of_o = 0;
    if (strchr(flags, 'f')) {
        if (!reg_error) {
            result = one_str_f_file(regular, result, str);
        }
    }
    result = one_str_e(lit, argv, result, str);
    if (strchr(flags, 'v')) {
        if (result == 0) {
            result = 1; number_of_o++;
        } else {
            result = 0;
        }
    }
    return result;
}

static int one_str_e(int *lit, char **argv, int result, char *str) {
    for (int k = 1; k <= lit[0]; k++) {
        int together = 0;
        if (lit[k] < 0) {
            lit[k] *= -1;
            together = 2;
        }
        if (new_strstr(str, &argv[lit[k]][together])) {
            result++;
        }
        if (together == 2) {
            lit[k] *= -1;
        }
    }
    return result;
}

static int one_str_f_file(char *regular, int result, char *str) {
    int k = 0, length = 0;
    while (regular[k] != '\0') {
        char *buff = s21_calloc(sizeof(char) * strlen(regular));
        while (regular[k] != '\n' && regular[k] != '\0' && regular[k] != EOF) {
            buff[k - length] = regular[k];
            k++;
        }
        if (new_strstr(str, buff)) {
            result++;
        }
        k++;
        length = k;
        s21_free(buff);
    }
    return result;
}

static void output(char *str, char *arg) {
    sort_star_end();
    if (!strchr(str, '\n')) {
        eof = 1;
    }
    for (int j = 0; j < number_of_o; j++) {
        if (multyfile && !strchr(flags, 'h')) {
            printf("%s:", arg);
        }
        if (strchr(flags, 'n')) {
            printf("%d:", flag_n);
        }
        if (strchr(flags, 'o') && !strchr(flags, 'v')) {
            for (int k = start_flag_o[j]; k < end_flag_o[j]; k++) {
                printf("%c", str[k]);
            }
            printf("\n");
        } else {
            printf("%s", str);
            break;
        }
    }
}

static void sort_star_end() {
    for (int j = 0; j < number_of_o; j++) {
        for (int k = j + 1; k < number_of_o; k++) {
            if (start_flag_o[j] > start_flag_o[k]) {
                swap(&start_flag_o[j], &start_flag_o[k]);
                swap(&end_flag_o[j], &end_flag_o[k]);
            }
        }
    }
}

static void swap(int *a, int *b) {
    int r = *a;
    *a = *b;
    *b = r;
}

static int new_strstr(const char *data1, const char *data2) {
    int result = 0;
    regex_t compiled;
    regmatch_t pmatch[1];
    int comp_flag = 0;
    if (strchr(flags, 'i')) {
        comp_flag = REG_ICASE;
    }
    regcomp(&compiled, data2, comp_flag);
    int start = 0;
    while (!regexec(&compiled, &data1[start], 1, pmatch, 0) && start < (int)strlen(data1)) {
        start_flag_o = s21_realloc(start_flag_o, (number_of_o + 1) * sizeof(int));
        end_flag_o = s21_realloc(end_flag_o, (number_of_o + 1) * sizeof(int));
        result = 1;
        start_flag_o[number_of_o] = pmatch->rm_so + start;
        end_flag_o[number_of_o] = pmatch->rm_eo + start;
        number_of_o++;
        start = pmatch->rm_eo + start;
    }
    regfree(&compiled);
    return result;
}

void *s21_calloc(int size) {
    void *mas = calloc(size, 1);
    if (mas == NULL) {
        exit(1);
    }
    return mas;
}

void *s21_realloc(void *mas, int size) {
    mas = realloc(mas, size);
    if (mas == NULL) {
        exit(1);
    }
    return mas;
}

void s21_free(void *point) {
    if (point != NULL) {
        free(point);
    }
}
