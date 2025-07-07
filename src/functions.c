#include <stdio.h>

int getchar_clear(char* ch) {
  int c = 0;

  *ch = getchar();

  if (*ch != '\n')
    while ((c = getchar()) != '\n' && c != EOF);

  return c;
}

int getchars_clear(char* str, size_t len) {
  size_t i = 0;
  int c = 0;

  while ((c = getchar()) != '\n' && c != EOF) {
    if (i != len - 1) {
      str[i++] = c;
    }
  }

  for (; i < len; i++) str[i] = '\0';

  return c;
}
