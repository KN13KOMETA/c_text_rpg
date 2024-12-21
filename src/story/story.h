#ifndef STORY_H
#define STORY_H

#include <stdbool.h>
#include <stdint.h>

struct Story {
  bool firstPlayerRoomEnter;
  bool firstThroneRoomEnter;
  uint8_t ending;
};

struct Story get_story(void);

#endif  // !STORY_H
