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

#define STORY_TEXT_CANT_RUN_AWAY \
  STORY_HEADER                   \
  "%s surrounded and can't run away\n"

// ENDINGS
#define STORY_ENDING_HEADER(num, name) \
  "\n-----< STORY ENDING: " #num "/5 " name " >-----\n"

#define STORY_ENDING_ERROR                   \
  "\n-----< STORY ENDING: %u ERROR >-----\n" \
  "Something went wrong, the ending was not found\n"

// Secret ending, normally u can't get this
// Until you somehow break a game and die in nvoid
#define STORY_ENDING0_NVOID_DEATH             \
  STORY_ENDING_HEADER(0, "NVOID DEATH")       \
  "After the complete disappearance of %s,\n" \
  "not a single quark of the %s body was found\n"

// Select suicide option in player_room
#define STORY_ENDING1_SUICIDE       \
  STORY_ENDING_HEADER(1, "SUICIDE") \
  "Without any reason %s commits suicide\n"

// Get killed in one of those locations:
// dead_forest,
// deep_forest,
// forest,
// high_mountain,
// mountain,
#define STORY_ENDING2_KILLED_BY_MONSTER                             \
  STORY_ENDING_HEADER(2, "KILLED BY MONSTER")                       \
  "%s miscalculated his strength and rushed into a losing battle\n" \
  "and was killed by monster\n"

// Explore in city
#define STORY_ENDING3_KNOCKED_OUT                                          \
  STORY_ENDING_HEADER(3, "KNOCKED OUT")                                    \
  "%s decides to explore the city, despite the city looking unfriendly.\n" \
  "%s wanders into an alley where he is struck from behind and knocked out.\n"

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

void add_counter(uint16_t *counter);

struct Quest generate_quest(void);

#endif  // !STORY_H
