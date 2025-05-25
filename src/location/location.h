#ifndef LOCATION_H
#define LOCATION_H

#include <stdint.h>

#include "../character/character.h"
#include "../story/story.h"

typedef enum {
  player_room,
  throne_room,
  demon_lord_castle,

  dead_forest,
  deep_forest,
  forest,

  hidden_garden,
  high_mountain,
  mountain,

  city,
  tavern,
  blacksmith_shop,
  training_ground,
  adventurer_guild,

  dev_room = UINT8_MAX - 2,
  nolocation = UINT8_MAX - 1,
  nvoid = UINT8_MAX,
} LOCATION_ID;

void location_loop(struct Character *player, struct Story *story);

#endif  // !LOCATION_H
