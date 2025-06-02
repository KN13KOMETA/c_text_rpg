#include <stdio.h>

char getchar_clear(void) {
  char c = getchar();

  if (c != 10) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
  }

  return c;
}

void getchars_clear(char* str, size_t len) {
  size_t i = 0;
  char c = 0;

  while ((c = getchar()) != '\n' && c != EOF) {
    if (i != len - 1) {
      str[i++] = c;
    }
  }

  for (; i < len; i++) str[i] = '\0';
}
