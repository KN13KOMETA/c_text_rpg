#include "character.h"

#include <stdio.h>
#include <string.h>

#include "functions.h"

void debug_character(struct Character *chr) {
  printf(
      "struct Character {\n"
      "  .name = %s\n"
      "  .gold = %u\n"
      "  .max_health = %u\n"
      "  .health = %u\n"
      "  .weapon = {\n"
      "    .name = %s\n"
      "    .price = %u\n"
      "    .upgrade_price = %u\n"
      "    .damage = %u\n"
      "  }\n"
      "}\n",
      chr->name, chr->gold, chr->max_health, chr->health, chr->weapon.name,
      chr->weapon.price, chr->weapon.upgrade_price, chr->weapon.damage);
}
void print_player(struct Character *chr) {
  printf(
      "-----< PLAYER STATUS >-----\n"
      "Character: %s (%ug %u/%uh)\n"
      "Weapon: %s (%up %uup %ud)\n",
      chr->name, chr->gold, chr->health, chr->max_health, chr->weapon.name,
      chr->weapon.price, chr->weapon.upgrade_price, chr->weapon.damage);
}

void print_enemy(struct Character *chr);
void battle_enemy(struct Character *player, struct Character *enemy);

void fix_character(struct Character *chr) {
  if (chr->gold > CHARACTER_MAX_GOLD) chr->gold = CHARACTER_MAX_GOLD;
  if (chr->max_health > CHARACTER_MAX_HEALTH)
    chr->max_health = CHARACTER_MAX_HEALTH;
  if (chr->health > chr->max_health) chr->health = chr->max_health;
}
struct Character generate_player(char *name) {
  struct Character chr = {.weapon = {"Hands", 0, 5, 5}};

  strcpy(chr.name, name);
  chr.gold = RND_MAX(50);
  chr.max_health = 10;
  chr.health = RND_RANGE(10, 1);

  fix_character(&chr);

  return chr;
}
struct Character generate_enemy(uint8_t difficulty) {
  struct Character chr = {
      .name = "Glitter Glitch",
      .gold = RND_MAX(UINT16_MAX),
      .max_health = chr.gold,
      .health = chr.gold,
      {.name = "Shining Death Star Glitch ", .damage = UINT16_MAX}};

  switch (difficulty) {
    case 0: {
      strcpy(chr.name, "Slime");
      chr.gold = RND_RANGE(10, 1);
      chr.max_health = 10;
      chr.health = RND_RANGE(10, 5);
      strcpy(chr.weapon.name, "Slimy Tentacle");
      chr.weapon.damage = RND_RANGE(3, 1);
      break;
    }
    case 1: {
      strcpy(chr.name, "Goblin");
      chr.gold = RND_RANGE(20, 10);
      chr.max_health = 25;
      chr.health = RND_RANGE(25, 10);
      strcpy(chr.weapon.name, "Rusty Knife");
      chr.weapon.damage = RND_RANGE(10, 3);
      break;
    }
  }

  fix_character(&chr);

  return chr;
}
