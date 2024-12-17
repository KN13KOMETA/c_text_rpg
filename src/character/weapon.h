#include <stdint.h>

#include "../const.h"

struct Weapon {
  char name[WEAPON_NAME_LENGTH];
  uint32_t price;
  uint32_t upgrade_price;
  uint16_t damage;
};
