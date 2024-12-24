#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdbool.h>
#include <stdint.h>

#include "weapon.h"

#define CHARACTER_NAME_LENGTH 21
#define CHARACTER_MAX_GOLD 4000000000
#define CHARACTER_MAX_HEALTH 50000

#include "../story/story.h"

// WARN: The whole story.h and character.h situation is horrible
// Rewrite this trash later

struct Character {
  char name[CHARACTER_NAME_LENGTH];
  uint32_t gold;
  uint16_t max_health;
  uint16_t health;
  struct Weapon weapon;
};

void debug_character(struct Character *chr);
void print_player(struct Character *chr, struct Story *story);
void print_enemy(struct Character *chr, bool hideGold, bool hideWeaponDamage);

void battle_enemy(struct Story *story, struct Character *player,
                  struct Character *enemy);

void fix_character(struct Character *chr);
struct Character generate_player(char *name);
struct Character generate_enemy(uint8_t enemy_id);

#endif  // !CHARACTER_H
