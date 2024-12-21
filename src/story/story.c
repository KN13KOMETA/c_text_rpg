#include "story.h"

struct Story get_story(void) {
  struct Story story = {
      .firstPlayerRoomEnter = true, .firstThroneRoomEnter = true, .ending = 0};

  return story;
}
