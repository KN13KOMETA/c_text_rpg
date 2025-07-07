#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>

#define RND_RANGE(max, min) rand() % (max + 1 - min) + min
#define RND_MAX(max) RND_RANGE(max, 0)

// Reads char from stdin and clears it's buffer.
// Returns last char from input.
int getchar_clear(char* c);
// Reads string from stdin and clears it's buffer.
// len is including '\0'.
// Returns last char from input.
int getchars_clear(char* str, size_t len);

#endif  // !FUNCTIONS_H
