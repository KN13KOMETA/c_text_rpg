#include <stdbool.h>
#include <stdint.h>

#include "const.h"
#include "weapon.h"

struct Character {
  char name[CHARACTER_NAME_LENGTH];
  uint32_t gold;
  uint16_t max_health;
  uint16_t health;
  struct Weapon weapon;
};

void debug_character(struct Character *chr);
void print_player(struct Character *chr);
void print_enemy(struct Character *chr, bool hideGold, bool hideWeaponDamage);

void battle_enemy(struct Character *player, struct Character *enemy);

void fix_character(struct Character *chr);
struct Character generate_player(char *name);
struct Character generate_enemy(uint8_t difficulty);
