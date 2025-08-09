#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef S21_CAT_H
#define S21_CAT_H
typedef struct Argument {
  int b, e, n, s, t, v, E, T;

} Argument;
void v_output(char ch);

void output(Argument arg, char **argv);

#endif