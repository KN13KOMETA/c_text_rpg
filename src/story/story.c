#include "story.h"

#include <string.h>

#include "../functions.h"
#include "../location/location.h"

struct Story get_story(void) {
  struct Story story = {.ending = 0xff};

  return story;
}

void add_counter(uint16_t* counter) {
  if (*counter == UINT16_MAX) return;

  (*counter)++;
}

struct Quest generate_quest(void) {
  struct Quest quest = {.progress_count = 0, .target_count = RND_RANGE(25, 5)};
  struct Character chr = {.name = CHARACTER_ERROR_ENEMY_NAME};

  while (strcmp(chr.name, CHARACTER_ERROR_ENEMY_NAME) == 0) {
    uint8_t x = RND_MAX(UINT8_MAX);

    switch (x) {
      case throne_room * 10 + 0:
      case hidden_garden * 10 + 0:
        continue;
      default:
        chr = generate_enemy(x);
    }
  }

  strcpy(quest.target_name, chr.name);
  quest.reward_gold = quest.target_count * chr.gold;

  return quest;
}
