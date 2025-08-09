
#include "s21_cat.h"

struct Argument parser(int argc, char **argv) {
  Argument arg = {0};
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squezzy-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}

  };
  int key;
  key = getopt_long(argc, argv, "benstvET", long_options, 0);
  switch (key) {
    case 'b':
      arg.b = 1;
      break;
    case 'e':
      arg.e = 1;
      arg.v = 1;
      break;
    case 'E':
      arg.e = 1;
      break;
    case 'n':
      arg.n = 1;
      break;
    case 's':
      arg.s = 1;
      break;
    case 't':
      arg.t = 1;
      arg.v = 1;
      break;
    case 'T':
      arg.t = 1;
      break;
    case 'v':
      arg.v = 1;
      break;
    case '?':
      fprintf(stderr, "Error\n");
      break;
    default:
      break;
  }
  return arg;
}
void v_output(char ch) {
  if (!isprint(ch) && !isascii(ch)) {
    putchar('M');
    putchar('-');
    ch = toascii(ch);
  }
  if (iscntrl(ch) && ch != '\n') {
    putchar('^');
    putchar((ch) == 127 ? '?' : ch + 64);
  }
}

void output(Argument arg, char **argv) {
  FILE *f = fopen(argv[optind], "r");
  if (f == NULL) {
    perror("Ошибка открытия файла");
    return;
  }
  char *len = NULL;
  size_t memlen = 0;
  int read = 0;
  read = getline(&len, &memlen, f);
  int count_str = 1;
  int empty_str = 0;

  while (read != -1) {
    if (strcspn(len, "\n") == 0) {
      empty_str++;
    } else
      empty_str = 0;
    if (arg.s && empty_str > 1) {
    } else {
      if (arg.n) {
        printf("%6d\t", count_str++);
      }
      if (arg.b && !arg.n && strcspn(len, "\n") != 0 &&
          strcspn(len, "\00") != 0) {
        printf("%6d\t", count_str++);
      }
      for (int i = 0; i < read; i++) {
        if (arg.t && len[i] == '\t') {
          printf("^I");
          continue;
        } else if (arg.e && len[i] == '\n') {
          printf("$\n");
        } else if (arg.v && len[i] != '\t' && len[i] != '\n' &&
                   (!isprint(len[i]))) {
          v_output(len[i]);
        } else
          putchar(len[i]);
      }
    }
    read = getline(&len, &memlen, f);
  }
  free(len);
  fclose(f);
}
int main(int argc, char *argv[]) {
  Argument arg = parser(argc, argv);
  output(arg, argv);
  return 0;
}