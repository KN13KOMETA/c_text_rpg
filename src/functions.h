#include <stdlib.h>

#define RND_RANGE(max, min) rand() % (max + 1 - min) + min
#define RND_MAX(max) RND_RANGE(max, 0)

char getchar_clear(void);
