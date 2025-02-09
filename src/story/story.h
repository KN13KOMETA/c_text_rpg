#pragma once
#ifndef STORY_H
#define STORY_H

#include <stdbool.h>
#include <stdint.h>

#include "../character/character.h"

// #define STORY_HEADER "\n-----< STORY >-----\n"
//
// #define STORY_TEXT_PLAYER_ROOM1 \
//   STORY_HEADER                  \
//   "%s wakes up very drunk\n"    \
//   "Not remembering what happened yesterday\n"
//
// #define STORY_TEXT_THRONE_ROOM1    \
//   STORY_HEADER                     \
//   "As %s enters %s\n"              \
//   "he sees a terrible mess\n"      \
//   "He also sees a sleeping girl\n" \
//   "with horns on the throne\n"     \
//   "She looks very drunk\n"         \
//   "Looks like there was a fun party yesterday\n"
//
// #define STORY_TEXT_DEAD_FOREST1                        \
//   STORY_HEADER                                         \
//   "As %s exists Demon Lord Castle\n"                   \
//   "he sees a wasteland from which\n"                   \
//   "dead trees occasionally stick out\n"                \
//   "but the lake is clear as the sky\n"                 \
//   "%s walks to the lake and looks at his reflection\n" \
//   "He has horns too\n"

#define STORY_ENDING_ERROR                   \
  "\n-----< STORY ENDING: %u ERROR >-----\n" \
  "Something went wrong, the ending was not found\n"

// Demon Lord KAMILLA
// 0 - Void Dead
// 1 - Suicide
// 2 - Killed by monster
// 3 - enslaved
// 4 - was killed in hidden garden
// 5 - sleep without exiting room

struct Quest {
  uint32_t reward_gold;

  char target_name[CHARACTER_NAME_LENGTH];
  uint16_t target_count;
  uint16_t progress_count;
};

struct Story {
  uint16_t player_room_counter;
  uint16_t throne_room_counter;
  uint16_t demon_lord_castle_counter;

  uint16_t dead_forest_counter;
  uint16_t deep_forest_counter;
  uint16_t forest_counter;

  uint16_t hidden_garden_counter;
  uint16_t high_mountain_counter;
  uint16_t mountain_counter;

  uint16_t city_counter;
  uint16_t tavern_counter;
  uint16_t blacksmith_shop_counter;
  uint16_t training_ground_counter;
  uint16_t adventurer_guild_counter;

  struct Quest quest;

  uint8_t ending;
};

struct Story get_story(void);

void add_counter(uint16_t* counter);

#endif  // !STORY_H
