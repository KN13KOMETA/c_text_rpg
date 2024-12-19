#include "character.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../functions.h"

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
      "\n-----< PLAYER STATUS >-----\n"
      "Character: %s (%ug %u/%uh)\n"
      "Weapon: %s (%up %uup %ud)\n",
      chr->name, chr->gold, chr->health, chr->max_health, chr->weapon.name,
      chr->weapon.price, chr->weapon.upgrade_price, chr->weapon.damage);
}
void print_enemy(struct Character *chr, bool hideGold, bool hideWeaponDamage) {
  printf(
      "\n-----< ENEMY STATUS >-----\n"
      "Character: %s (",
      chr->name);
  if (hideGold)
    printf("?");
  else
    printf("%u", chr->gold);

  printf(
      "g %u/%uh)\n"
      "Weapon: %s (%up %uup ",
      chr->health, chr->max_health, chr->weapon.name, chr->weapon.price,
      chr->weapon.upgrade_price);

  if (hideWeaponDamage)
    printf("?");
  else
    printf("%u", chr->weapon.damage);

  printf("d)\n");
}

void battle_enemy(struct Character *player, struct Character *enemy) {
  bool hideEnemyGold = true;
  bool hideEnemyWeaponDamage = true;
  while (1) {
    printf(
        "\n-----< BATTLE ACTION >-----\n"
        "s) Player and enemy status (doesn't waste turn)\n"
        "a) Attack enemy\n"
        "r) Run away\n"
        "SELECT: ");

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
        print_enemy(enemy, hideEnemyGold, hideEnemyWeaponDamage);
        break;
      }
      case 'a': {
        uint16_t player_new_health = player->health - enemy->weapon.damage;
        uint16_t enemy_new_health = enemy->health - player->weapon.damage;
        uint32_t winner_gold = player->gold + enemy->gold;

        // Prevent underflow and overflow
        if (player_new_health >= player->health) player_new_health = 0;
        if (enemy_new_health >= enemy->health) enemy_new_health = 0;
        if (winner_gold < player->gold || winner_gold > CHARACTER_MAX_GOLD)
          winner_gold = CHARACTER_MAX_GOLD;

        // After enemy attack, there is no sense in hiding enemy damage
        hideEnemyWeaponDamage = false;

        // Enemy turn
        player->health = player_new_health;

        printf(
            "\n-----< BATTLE ENEMY TURN >-----\n"
            "%s deals %u damage to %s using %s\n"
            "%s %u health left\n",
            enemy->name, enemy->weapon.damage, player->name, enemy->weapon.name,
            player->name, player->health);

        if (player->health == 0) {
          printf(
              "\n-----< BATTLE END >-----\n"
              "%s defeats %s using %s\n"
              "%s takes %u gold from %s\n",
              enemy->name, player->name, enemy->weapon.name, enemy->name,
              player->gold, player->name);

          enemy->gold = winner_gold;
          player->gold = 0;

          return;
        }

        // Player turn
        enemy->health = enemy_new_health;

        printf(
            "\n-----< BATTLE PLAYER TURN >-----\n"
            "%s deals %u damage to %s using %s\n"
            "%s %u health left\n",
            player->name, player->weapon.damage, enemy->name,
            player->weapon.name, enemy->name, enemy->health);

        if (enemy->health == 0) {
          printf(
              "\n-----< BATTLE END >-----\n"
              "%s defeats %s using %s\n"
              "%s takes %u gold from %s\n",
              player->name, enemy->name, player->weapon.name, player->name,
              enemy->gold, player->name);

          player->gold = winner_gold;
          enemy->gold = 0;

          return;
        }

        break;
      }
      case 'r': {
        printf(
            "\n-----< BATTLE END >-----\n"
            "%s decided to run away\n",
            player->name);
        return;
        break;
      }
      default:
        printf("\n-----< BATTLE UNKNOWN ACTION >-----\n");
    }
  }
}

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
struct Character generate_enemy(uint8_t enemy_id) {
  struct Character chr = {
      .name = "Glitter Glitch",
      .gold = RND_MAX(UINT16_MAX),
      .max_health = chr.gold,
      .health = chr.gold,
      {.name = "Shining Death Star Glitch ", .damage = UINT16_MAX}};

  switch (enemy_id) {
    case 0: {
      strcpy(chr.name, "Rat");
      chr.gold = RND_RANGE(5, 1);
      chr.max_health = 5;
      chr.health = RND_RANGE(5, 1);
      strcpy(chr.weapon.name, "Sharp Teeth");
      chr.weapon.damage = RND_RANGE(2, 1);
      break;
    }
    case 10: {
      strcpy(chr.name, "Slime");
      chr.gold = RND_RANGE(10, 1);
      chr.max_health = 10;
      chr.health = RND_RANGE(10, 5);
      strcpy(chr.weapon.name, "Slimy Tentacle");
      chr.weapon.damage = RND_RANGE(3, 1);
      break;
    }
    case 20: {
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
