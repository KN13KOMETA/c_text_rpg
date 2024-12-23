#ifndef STORY_H
#define STORY_H

#include <stdbool.h>
#include <stdint.h>

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

  uint8_t ending;
};

struct Story get_story(void);

void add_counter(uint16_t* counter);

#endif  // !STORY_H
