#include "character.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../functions.h"
#include "../location/location.h"

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
void print_player_quest(struct Story *story) {
  bool completed = story->quest.target_count == story->quest.progress_count;

  if (story->quest.target_count == 0) return;

  printf(
      "\n-----< QUEST (%s) >-----\n"
      "Kill %s (%u/%u)\n"
      "Reward %ug\n",
      (completed ? "COMPLETED" : "NOT COMPLETED"), story->quest.target_name,
      story->quest.progress_count, story->quest.target_count,
      story->quest.reward_gold);
  if (completed) printf("Head to the Adventurer Guild for reward\n");
}
void print_player(struct Character *chr, struct Story *story) {
  printf("\n-----< PLAYER STATUS >-----\n");
#ifdef DEBUG
  debug_character(chr);
#else
  printf(
      "Character: %s (%ug %u/%uh)\n"
      "Weapon: %s (%up %uup %ud)\n",
      chr->name, chr->gold, chr->health, chr->max_health, chr->weapon.name,
      chr->weapon.price, chr->weapon.upgrade_price, chr->weapon.damage);
#endif /* ifdef DEBUG */

  print_player_quest(story);
}
void print_enemy(struct Character *chr, bool hide_gold,
                 bool hide_weapon_damage) {
  printf("\n-----< ENEMY STATUS >-----\n");
#ifdef DEBUG
  printf(
      "hide_gold = %d\n"
      "hide_weapon_damage = %d\n",
      hide_gold, hide_weapon_damage);
  debug_character(chr);
#else
  printf("Character: %s (", chr->name);
  if (hide_gold)
    printf("?");
  else
    printf("%u", chr->gold);

  printf(
      "g %u/%uh)\n"
      "Weapon: %s (%up %uup ",
      chr->health, chr->max_health, chr->weapon.name, chr->weapon.price,
      chr->weapon.upgrade_price);

  if (hide_weapon_damage)
    printf("?");
  else
    printf("%u", chr->weapon.damage);

  printf("d)\n");
#endif /* ifdef DEBUG */
}

void battle_enemy(struct Story *story, struct Character *player,
                  struct Character *enemy) {
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
        print_player(player, story);
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
              enemy->gold, enemy->name);

          player->gold = winner_gold;
          enemy->gold = 0;

          if (strcmp(enemy->name, story->quest.target_name) == 0) {
            if (story->quest.progress_count < story->quest.target_count)
              story->quest.progress_count++;

            print_player_quest(story);
          }

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
      {.name = "Shining Death Star Glitch", .damage = UINT16_MAX}};

  // Max 10 enemies per location
  switch (enemy_id) {
    // player_room
    case player_room * 10 + 0: {
      strcpy(chr.name, "Rat");
      chr.gold = RND_RANGE(5, 1);
      chr.max_health = 5;
      chr.health = RND_RANGE(5, 1);
      strcpy(chr.weapon.name, "Sharp Teeth");
      chr.weapon.damage = RND_RANGE(2, 1);
      break;
    }
    case player_room * 10 + 1: {
      strcpy(chr.name, "Spider");
      chr.gold = RND_RANGE(3, 1);
      chr.max_health = 4;
      chr.health = RND_RANGE(4, 2);
      strcpy(chr.weapon.name, "Venomous Fangs");
      chr.weapon.damage = RND_RANGE(2, 1);
      break;
    }
    // throne_room
    case throne_room * 10 + 0: {
      strcpy(chr.name, "Frightening Aura");
      chr.gold = 0;
      chr.max_health = 30000;
      chr.health = 30000;
      // TODO: Rename this
      strcpy(chr.weapon.name, "Frightening Aura");
      chr.weapon.damage = 15000;
      break;
    }
    // demon_lord_castle

    // dead_forest
    case dead_forest * 10 + 0: {
      strcpy(chr.name, "Undead Spirit");
      chr.gold = RND_RANGE(1600, 1200);
      chr.max_health = 16000;
      chr.health = RND_RANGE(16000, 14000);
      strcpy(chr.weapon.name, "Ethereal Scythe");
      chr.weapon.damage = RND_RANGE(11700, 8000);
      break;
    }
    case dead_forest * 10 + 1: {
      strcpy(chr.name, "Undead Horde");
      chr.gold = RND_RANGE(1700, 1300);
      chr.max_health = 18000;
      chr.health = RND_RANGE(18000, 15000);
      strcpy(chr.weapon.name, "Rusty Weapons");
      chr.weapon.damage = RND_RANGE(12000, 1900);
      break;
    }
    // deep_forest
    case deep_forest * 10 + 0: {
      strcpy(chr.name, "Forest Wraith");
      chr.gold = RND_RANGE(800, 300);
      chr.max_health = 3000;
      chr.health = RND_RANGE(3000, 2000);
      strcpy(chr.weapon.name, "Shadowy Whip");
      chr.weapon.damage = RND_RANGE(1200, 500);
      break;
    }
    case deep_forest * 10 + 1: {
      strcpy(chr.name, "Giant Snake");
      chr.gold = RND_RANGE(900, 400);
      chr.max_health = 3500;
      chr.health = RND_RANGE(3500, 2500);
      strcpy(chr.weapon.name, "Shadowy Whip");
      chr.weapon.damage = RND_RANGE(1500, 700);
      break;
    }
    // forest
    case forest * 10 + 0: {
      strcpy(chr.name, "Slime");
      chr.gold = RND_RANGE(10, 1);
      chr.max_health = 10;
      chr.health = RND_RANGE(10, 5);
      strcpy(chr.weapon.name, "Slimy Tentacle");
      chr.weapon.damage = RND_RANGE(3, 1);
      break;
    }
    case forest * 10 + 1: {
      strcpy(chr.name, "Wild Boar");
      chr.gold = RND_RANGE(10, 4);
      chr.max_health = 20;
      chr.health = RND_RANGE(20, 12);
      strcpy(chr.weapon.name, "Sharp Tusks");
      chr.weapon.damage = RND_RANGE(8, 6);
      break;
    }
    case forest * 10 + 2: {
      strcpy(chr.name, "Goblin");
      chr.gold = RND_RANGE(12, 6);
      chr.max_health = 18;
      chr.health = RND_RANGE(18, 10);
      strcpy(chr.weapon.name, "Rusty Knife");
      chr.weapon.damage = RND_RANGE(15, 6);
      break;
    }
    case forest * 10 + 3: {
      strcpy(chr.name, "Forest Bandit");
      chr.gold = RND_RANGE(20, 10);
      chr.max_health = 25;
      chr.health = RND_RANGE(25, 10);
      strcpy(chr.weapon.name, "Wooden Bow");
      chr.weapon.damage = RND_RANGE(10, 3);
      break;
    }

    // hidden_garden
    // high_mountain
    case high_mountain * 10 + 0: {
      strcpy(chr.name, "Elven Archer");
      chr.gold = RND_RANGE(2800, 2600);
      chr.max_health = 10000;
      chr.health = RND_RANGE(10000, 8000);
      strcpy(chr.weapon.name, "Mithril Bow");
      chr.weapon.damage = RND_RANGE(14000, 12000);
      break;
    }
    case high_mountain * 10 + 1: {
      strcpy(chr.name, "Elven Mage");
      chr.gold = RND_RANGE(4000, 3000);
      chr.max_health = 8000;
      chr.health = RND_RANGE(8000, 6000);
      strcpy(chr.weapon.name, "Mithril Staff");
      chr.weapon.damage = RND_RANGE(18000, 16000);
      break;
    }
    case high_mountain * 10 + 2: {
      strcpy(chr.name, "Elven Warrior");
      chr.gold = RND_RANGE(10000, 8000);
      chr.max_health = 20000;
      chr.health = RND_RANGE(20000, 18000);
      strcpy(chr.weapon.name, "Mithril Sword");
      chr.weapon.damage = RND_RANGE(16000, 14000);
      break;
    }
    // mountain
    case mountain * 10 + 0: {
      strcpy(chr.name, "Snow Leopard");
      chr.gold = RND_RANGE(1000, 500);
      chr.max_health = 2800;
      chr.health = RND_RANGE(2800, 2000);
      strcpy(chr.weapon.name, "Claws");
      chr.weapon.damage = RND_RANGE(1300, 600);
      break;
    }
    case mountain * 10 + 1: {
      strcpy(chr.name, "Ice Elemental");
      chr.gold = RND_RANGE(1200, 600);
      chr.max_health = 4000;
      chr.health = RND_RANGE(4000, 3000);
      strcpy(chr.weapon.name, "Ice Shard");
      chr.weapon.damage = RND_RANGE(1700, 800);
      break;
    }
    case mountain * 10 + 2: {
      strcpy(chr.name, "Elven Scout");
      chr.gold = RND_RANGE(1800, 600);
      chr.max_health = 2400;
      chr.health = RND_RANGE(2400, 2000);
      strcpy(chr.weapon.name, "Mithril Dagger");
      chr.weapon.damage = RND_RANGE(2000, 1500);
      break;
    }
  }

  fix_character(&chr);

  return chr;
}
