#pragma once
#ifndef STORY_H
#define STORY_H

#include <stdbool.h>
#include <stdint.h>

#include "../character/character.h"

// TODO: Location story checklist
// player_room,
// throne_room,
// demon_lord_castle,
//
// dead_forest,
// deep_forest,
// forest,
//
// hidden_garden,
// high_mountain,
// mountain,
//
// city,
// tavern,
// blacksmith_shop,
// training_ground,
// adventurer_guild,

#define STORY_HEADER "\n-----< STORY >-----\n"

#define STORY_DISCLAIMER                                                     \
  STORY_HEADER                                                               \
  "This game may contain scenes that are not suitable for young minds\n"     \
  "Also story will be probably edited, so do not expect it to be the same\n" \
  "Are you sure you want to continue?\n"                                     \
  "y) Yes, continue\n"                                                       \
  "n) No, exit game\n"                                                       \
  "SELECT: "

#define STORY_ENDING_ERROR                   \
  "\n-----< STORY ENDING: %u ERROR >-----\n" \
  "Something went wrong, the ending was not found\n"


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
