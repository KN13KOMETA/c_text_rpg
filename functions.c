#include <stdio.h>

// Reads char from stdin and clears it's buffer
char getchar_clear() {
  char c = getchar();
  if (c != 10) getchar();
  return c;
}
