#include <stdio.h>

// Reads char from stdin and clears it's buffer
char getchar_clear(void) {
  char c = getchar();

  if (c != 10) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
  }

  return c;
}
