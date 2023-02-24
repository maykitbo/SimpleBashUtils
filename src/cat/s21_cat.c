#include "s21_cat.h"

int main(int argc, char *argv[]) {
    int fil[32];
    char flags[12];
    int ind_fil = find_flags(flags, argc, argv, fil);
    cycle_files(ind_fil, argv, fil, flags);
    return 0;
}

static void cycle_files(int ind_fil, char **argv, int *fil, char *flags) {
    for (int g = 0; g < ind_fil; g++) {
        FILE *file = fopen(argv[fil[g]], "r");
        if (file != NULL) {
            one_file(file, flags);
        } else {
            fprintf(stderr, "file error: %s\n", argv[fil[g]]);
        }
        fclose(file);
    }
}

static void one_file(FILE *file, char *flags) {
    char c;
    int s = 1, numstr_n = 1;
    while ((c = fgetc(file)) != EOF) {
        if (!flag_s(&s, flags, c, &numstr_n)) {
            if (!(c == '\n' && strchr(flags, 'b'))) {
                flag_n(flags, &numstr_n);
            }
            c = output(c, flags, file, &s);
            flag_e(flags, c);
        }
    }
}

static char output(char c, char *flags, FILE *file, int *s) {
    while (c != '\n' && c != EOF) {
        if (c >= 0 && c <= 31 && c != '\t' && c != ' ' && c != '\n' && strchr(flags, 'v')) {
            c += 64;
            printf("^");
        } else if (strchr(flags, 'v') && c == 127) {
            c -= 64;
            printf("^");
        }
        if ((strchr(flags, 't') || strchr(flags, 'T')) && c == '\t') {
            printf("^I");
        } else {
            printf("%c", c);
        }
        c = fgetc(file);
        *s = 1;
    }
    return c;
}

static int flag_s(int *s, char *flags, char c, int* numstr_n) {
    int res = 0;
    if (strchr(flags, 's') && c == '\n') {
        res = 1;
        if (*s == 1) {
            if (!strchr(flags, 'b')) {
                flag_n(flags, numstr_n);
            }
            flag_e(flags, c);
        }
        *s = 0;
    }
    return res;
}

static void flag_e(char *flags, char c) {
    if (c != EOF) {
        if (strchr(flags, 'e') || strchr(flags, 'E')) {
            printf("$");
        }
        printf("\n");
    }
}

static int find_flags(char *flags, int argc, char **argv, int *fil) {
    int n = 1, f = 0, ind_fil = 0;
    for (int k = 0; k < 12; k++) {
        flags[k] = '\0';
    }
    while (n < argc) {
        if (argv[n][0] == '-') {
            f = one_flag(argv, n, f, flags);
        } else {
            fil[ind_fil] = n;
            ind_fil++;
        }
        n++;
    }
    return ind_fil;
}

static int one_flag(char **argv, int n, int f, char *flags) {
    if (argv[n][1] == '-') {
        if (!strcmp(argv[n], "--number-nonblank")) {
            flags[f] = 'b';
            f++;
        } else if (!strcmp(argv[n], "--number")) {
            flags[f] = 'n';
            f++;
        } else if (!strcmp(argv[n], "--squeeze-blank")) {
            flags[f] = 's';
            f++;
        }
    } else {
        int u = 1;
        while (argv[n][u]) {
            flags[f] = argv[n][u];
            f++;
            if (flags[f - 1] == 'e' || flags[f - 1] == 't') {
                flags[f] = 'v';
                f++;
            }
            u++;
        }
    }
    return f;
}

static void flag_n(char *flags, int *numstr_n) {
    if (strchr(flags, 'n') || strchr(flags, 'b')) {
        printf("%6d\t", *numstr_n);
        *numstr_n = *numstr_n + 1;
    }
}
