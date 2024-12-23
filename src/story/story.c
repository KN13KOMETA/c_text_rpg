#include "story.h"

struct Story get_story(void) {
  struct Story story = {.ending = 0xff};

  return story;
}

void add_counter(uint16_t* counter) {
  if (*counter == UINT16_MAX) return;

  (*counter)++;
}
