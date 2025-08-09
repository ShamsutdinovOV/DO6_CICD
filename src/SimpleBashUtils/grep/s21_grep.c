#include "s21_grep.h"

Argument parser(int argc, char *argv[]) {
  Argument arg = {0};
  int key;
  struct option long_options[] = {0};
  while ((key = getopt_long(argc, argv, "e:ivcln", long_options, 0)) != -1) {
    switch (key) {
      case 'e':
        arg.e = 1;
        if (arg.pat_count < PAT_MAX) {
          arg.pattern[arg.pat_count] = optarg;
          arg.pat_count++;
        } else {
          fprintf(stderr, "Превышено количество паттернов\n");
        }
        break;
      case 'i':
        arg.i = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case '?':
        fprintf(stderr, "Флаг не найден\n");
        break;
      default:
        break;
    }
  }

  if (!arg.e && optind < argc) {
    arg.pattern[arg.pat_count] = argv[optind];
    optind++;
    arg.pat_count++;
  }

  return arg;
}

int l_output(int argc, char *argv[]) {
  int count_f = 0;
  for (int i = optind; i < argc; i++) {
    if (strncmp(argv[i], "-", 1) != 0) ++count_f;
  }
  return count_f;
}

void n_output(char *len, int count, int count_f, char filename[]) {
  if (count_f > 1)
    printf("%s:%d:%s", filename, count, len);
  else
    printf("%d:%s", count, len);
}
void c_output(Argument arg, int count, int count_f, int count_all,
              char filename[]) {
  if (arg.c && arg.l && (count > 0)) {
    count_f > 1 ? printf("%s:1\n%s\n", filename, filename)
                : printf("1\n%s\n", filename);

  } else if (arg.c && arg.l && (count == 0)) {
    printf("%d\n", count);
  }

  if ((arg.c && !arg.l && !arg.v && !arg.n) || (arg.c && arg.n && !arg.v)) {
    count_f > 1 ? printf("%s:%d\n", filename, count) : printf("%d\n", count);
  }

  if ((arg.c && arg.v)) {
    if ((count_all - count) > 0) {
      count_f > 1 ? printf("%s:%d", filename, count_all - count)
                  : printf("%d\n", count_all - count);
    }
  }
}

void e_output(Argument arg, regex_t reg, char *argv[], FILE *f, int argc,
              char filename[]) {
  char len[STR_MAX];
  int count = 0;
  int count_all = 0;
  int count_f = l_output(argc, argv);
  for (int i = 0; i < arg.pat_count; i++) {
    regcomp(&reg, arg.pattern[i], arg.i ? REG_ICASE : 0);

    while (fgets(len, sizeof(len), f) != NULL) {
      ++count_all;
      regmatch_t pmatch[1];

      if (arg.l && arg.v) {
        if (regexec(&reg, len, 1, pmatch, 0) != 0) {
          printf("%s\n", filename);
          break;
        }
      }
      if (arg.v && !arg.l && !arg.c) {
        if (regexec(&reg, len, 1, pmatch, 0) != 0) {
          if (arg.n || (arg.n && arg.c)) {
            count_f > 1 ? printf("%s:%d:%s", filename, count_all, len)
                        : printf("%d:%s", count_all, len);
          } else
            count_f > 1 ? printf("%s:%s", filename, len) : printf("%s", len);
        }
        continue;
      }
      if (regexec(&reg, len, 1, pmatch, 0) == 0) {
        ++count;

        if ((arg.l && !arg.c)) {
          printf("%s\n", filename);
          break;
        }
        if (!arg.c && !arg.n) {
          count_f > 1 ? printf("%s:%s", filename, len) : printf("%s", len);
        }
        if (arg.n && !arg.c) n_output(len, count_all, count_f, filename);
      }
    }
    c_output(arg, count, count_f, count_all, filename);
    regfree(&reg);
  }
}

void slash_n(Argument arg, FILE *f) {
  if ((arg.v && !arg.c && !arg.l) || (arg.n && arg.e)) {
    fseek(f, -1, SEEK_END);
    int lastChar = fgetc(f);
    if (lastChar != '\n') printf("\n");
  }
}
void output(Argument arg, int argc, char *argv[]) {
  int count_f = 0;

  for (int i = optind; i < argc; i++) {
    if (strncmp(argv[i], "-", 1) != 0) {
      FILE *f = fopen(argv[i], "r");
      char *filename = argv[i];
      count_f++;
      if (f == NULL) {
        fprintf(stderr, "grep: %s: No such file or directory\n", filename);
        continue;
      } else {
        regex_t reg;
        e_output(arg, reg, argv, f, argc, filename);
        slash_n(arg, f);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  Argument arg = parser(argc, argv);
  output(arg, argc, argv);

  return 0;
}
