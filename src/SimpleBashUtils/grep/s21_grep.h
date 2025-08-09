#ifndef S21_GREP_H
#define S21_GREP_H

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_MAX 4056
#define PAT_MAX 100

typedef struct Argument {
  int e, i, v, c, l, n;
  char *pattern[PAT_MAX];
  int pat_count;
} Argument;
void output(Argument arg, int argc, char **argv);
void e_output(Argument arg, regex_t reg, char *argv[], FILE *f, int argc,
              char filename[]);
int l_output(int argc, char *argv[]);
void n_output(char *len, int count, int count_f, char filename[]);
void c_output(Argument arg, int count, int count_f, int count_all,
              char filename[]);
void slash_n(Argument arg, FILE *f);
#endif