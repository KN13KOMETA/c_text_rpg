#include "location.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../character/weapon.h"
#include "../functions.h"

#define OFFERED_WEAPONS_LENGTH 7
#define QUEST_GOLD_MODIFIER 5

#if OFFERED_WEAPONS_LENGTH > 10
#error CAN'T OFFER MORE THAN 10 WEAPONS
#endif

// TODO: locations checklist
// player_room +
// throne_room -
// demon_lord_castle +
// dead_forest +
// deep_forest +
// forest +
// hidden_garden -
// high_mountain +
// mountain +
// NO EXPLORE ACT:
// city +
// tavern +
// blacksmith_shop +
// training_ground +
// adventurer_guild +

// TODO: maybe this need a bit rework
void player_room_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[CHARACTER_NAME_LENGTH + 5];
  uint8_t enemies_count = 2;
  uint8_t enemies_start_index = player_room * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  char cheatcode[] = "ikwid";
  uint8_t cheatcode_length = strlen(cheatcode);
  uint8_t cheatcode_progress = 0;

  sprintf(location_name, "%s Room", player->name);
  add_counter(&story->player_room_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    char select;
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Leave room\n"
        "2) Sleep\n"
        "3) Suicide\n"
        "SELECT: ",
        location_name);
    select = getchar_clear();

    switch (select) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around sees stone walls around him, "
            "bed and table, seems confortable enough\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          printf(
              "\n-----< AFTER BATTLE >-----\n"
              "%s refuses to die\n"
              "1 health restored\n",
              player->name);
          player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = demon_lord_castle;
        leave_location = true;
        break;
      }
      case '2': {
        uint8_t sleep_time = 30;
        uint16_t restore_health = player->max_health * 0.75;

        if (restore_health > player->health)
          restore_health -= player->health;
        else
          restore_health = 0;

        player->health += restore_health;

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s lays on bed and sleep\n"
            "\n-----< WAIT (%us) >-----\n",
            location_name, player->name, sleep_time);

        for (uint8_t i = 0; i < sleep_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf("\n");

        if (story->player_room_counter == 1) {
          story->ending = 5;
          *location_id = nolocation;
          return;
        }

        printf(
            "\n-----< SLEEP >-----\n"
            "%u health restored\n",
            restore_health);

        break;
      }
      case '3': {
        print_player(player, story);

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s commits suicide\n"
            "0 health left\n",
            location_name, player->name);
        player->health = 0;

        story->ending = 1;
        *location_id = nolocation;
        return;
      }
      default: {
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);

        if (select == cheatcode[cheatcode_progress]) {
          cheatcode_progress++;

          if (cheatcode_progress == cheatcode_length) {
            *location_id = nvoid;
            leave_location = true;
          }
        } else {
          cheatcode_progress = 0;
        }
      }
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void throne_room_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Throne Room";
  uint8_t enemies_count = 1;
  uint8_t enemies_start_index = throne_room * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->throne_room_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  // Start battle immeadiately
  // TODO: need only 1 win
  {
    uint16_t prebattle_player_health = player->health;
    struct Character enemy =
        generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));

    battle_enemy(story, player, &enemy);

    // Restore player health
    player->health = prebattle_player_health;

    if (enemy.health != 0) {
      // TODO: Make normal message
      printf(
          "\n-----< AFTER BATTLE >-----\n"
          "Too weak boi\n");

      leave_location = true;
      *location_id = demon_lord_castle;
      return;
    }
  }

  // TODO: story
  while (!leave_location) {
    // Send player to void for now
    leave_location = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void demon_lord_castle_loop(struct Character *player, struct Story *story,
                            LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Demon Lord Castle";
  // TODO: Maybe make unique enemies
  // Have same enemies as player_room
  uint8_t enemies_count = 2;
  uint8_t enemies_start_index = player_room * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->demon_lord_castle_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to %s Room\n"
        "2) Enter Throne Room\n"
        "3) Exit %s\n"
        "SELECT: ",
        location_name, player->name, location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around sees stone walls around him\n"
            "and Throne Room surrounded by frightening aura\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          printf(
              "\n-----< AFTER BATTLE >-----\n"
              "%s refuses to die\n"
              "1 health restored\n",
              player->name);
          player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = player_room;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = throne_room;
        leave_location = true;
        break;
      }
      case '3': {
        *location_id = dead_forest;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void dead_forest_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Dead Forest";
  uint8_t enemies_count = 2;
  uint8_t enemies_start_index = dead_forest * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->dead_forest_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to Demon Lord Castle\n"
        "2) Visit Deep Forest\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around, everything seems dead\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          story->ending = 2;
          *location_id = nolocation;
          return;
          // printf(
          //     "\n-----< AFTER BATTLE >-----\n"
          //     "%s refuses to die\n"
          //     "1 health restored\n",
          //     player->name);
          // player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = demon_lord_castle;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = deep_forest;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void deep_forest_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Deep Forest";
  uint8_t enemies_count = 2;
  uint8_t enemies_start_index = deep_forest * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->deep_forest_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to Dead Forest\n"
        "2) Visit Forest\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around, trees surround him\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          story->ending = 2;
          *location_id = nolocation;
          return;
          // printf(
          //     "\n-----< AFTER BATTLE >-----\n"
          //     "%s refuses to die\n"
          //     "1 health restored\n",
          //     player->name);
          // player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = dead_forest;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = forest;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void forest_loop(struct Character *player, struct Story *story,
                 LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Forest";
  uint8_t enemies_count = 4;
  uint8_t enemies_start_index = forest * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->forest_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to Deep Forest\n"
        "2) Visit City\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around sees trees around him\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          story->ending = 2;
          *location_id = nolocation;
          return;
          // printf(
          //     "\n-----< AFTER BATTLE >-----\n"
          //     "%s refuses to die\n"
          //     "1 health restored\n",
          //     player->name);
          // player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = deep_forest;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = city;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void hidden_garden_loop(struct Character *player, struct Story *story,
                        LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Hidden Garden";

  add_counter(&story->hidden_garden_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    // Send player to void for now
    leave_location = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void high_mountain_loop(struct Character *player, struct Story *story,
                        LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "High Mountain";
  uint8_t enemies_count = 3;
  uint8_t enemies_start_index = high_mountain * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->high_mountain_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to Hidden Garden\n"
        "2) Visit Mountain\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees lifeless frozen high mountains\n"
            "covered with a thick layer of snow\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          story->ending = 2;
          *location_id = nolocation;
          return;
          // printf(
          //     "\n-----< AFTER BATTLE >-----\n"
          //     "%s refuses to die\n"
          //     "1 health restored\n",
          //     player->name);
          // player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = hidden_garden;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = mountain;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void mountain_loop(struct Character *player, struct Story *story,
                   LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Mountain";
  uint8_t enemies_count = 3;
  uint8_t enemies_start_index = mountain * 10;
  uint8_t enemies_end_index = enemies_start_index + enemies_count - 1;

  add_counter(&story->mountain_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to High Mountain\n"
        "2) Visit City\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around sees mountains and flower fields on them\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy =
            generate_enemy(RND_RANGE(enemies_end_index, enemies_start_index));
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          story->ending = 2;
          *location_id = nolocation;
          return;
          // printf(
          //     "\n-----< AFTER BATTLE >-----\n"
          //     "%s refuses to die\n"
          //     "1 health restored\n",
          //     player->name);
          // player->health = 1;
        }

        break;
      }
      case '1': {
        *location_id = high_mountain;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = city;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void city_loop(struct Character *player, struct Story *story,
               LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "City";

  add_counter(&story->city_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Go to Forest\n"
        "2) Go to Mountain\n"
        "3) Visit Tavern\n"
        "4) Visit Blacksmith Shop\n"
        "5) Visit Training Ground\n"
        "6) Visit Adventurer Guild\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees a small town\n"
            "It seems the residents are not very friendly towards him\n"
            "From all places, %s gets sideways glances\n",
            location_name, player->name, player->name);
        break;
      }
      case 'e': {
        story->ending = 3;
        *location_id = nolocation;
        return;
      }
      case '1': {
        *location_id = forest;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = mountain;
        leave_location = true;
        break;
      }
      case '3': {
        *location_id = tavern;
        leave_location = true;
        break;
      }
      case '4': {
        *location_id = blacksmith_shop;
        leave_location = true;
        break;
      }
      case '5': {
        *location_id = training_ground;
        leave_location = true;
        break;
      }
      case '6': {
        *location_id = adventurer_guild;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void tavern_loop(struct Character *player, struct Story *story,
                 LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Tavern";

  add_counter(&story->tavern_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "1) Leave %s\n"
        "2) Drink beer (10%% health restore)\n"
        "3) Eat salad  (25%% health restore)\n"
        "4) Eat chiken (50%% health restore)\n"
        "SELECT: ",
        location_name, location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around\n"
            "It seems like everyone is having fun\n",
            location_name, player->name);
        break;
      }
      case '1': {
        *location_id = city;
        leave_location = true;
        break;
      }
      case '2': {
        uint16_t heal = player->max_health * 0.10;
        uint16_t new_health = player->health + heal;
        uint32_t price = heal * 10;

        // Overflow checks
        if (new_health < player->health || new_health > player->max_health)
          new_health = player->max_health;

        // Max health check
        if (player->health == player->max_health) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already have max health\n",
              location_name, player->name);
          break;
        }

        // Gold check
        if (player->gold < price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, price, player->gold);
          break;
        }

        player->gold -= price;
        player->health = new_health;

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s healed %u health\n",
            location_name, player->name, heal);

        break;
      }
      case '3': {
        uint16_t heal = player->max_health * 0.25;
        uint16_t new_health = player->health + heal;
        uint32_t price = heal * 10;

        // Overflow checks
        if (new_health < player->health || new_health > player->max_health)
          new_health = player->max_health;

        // Max health check
        if (player->health == player->max_health) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already have max health\n",
              location_name, player->name);
          break;
        }

        // Gold check
        if (player->gold < price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, price, player->gold);
          break;
        }

        player->gold -= price;
        player->health = new_health;

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s healed %u health\n",
            location_name, player->name, heal);

        break;
      }
      case '4': {
        uint16_t heal = player->max_health * 0.50;
        uint16_t new_health = player->health + heal;
        uint32_t price = heal * 10;

        // Overflow checks
        if (new_health < player->health || new_health > player->max_health)
          new_health = player->max_health;

        // Max health check
        if (player->health == player->max_health) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already have max health\n",
              location_name, player->name);
          break;
        }

        // Gold check
        if (player->gold < price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, price, player->gold);
          break;
        }

        player->gold -= price;
        player->health = new_health;

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s healed %u health\n",
            location_name, player->name, heal);

        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void blacksmith_shop_loop(struct Character *player, struct Story *story,
                          LOCATION_ID *location_id,
                          struct Weapon offered_weapons[]) {
  bool leave_location = false;
  char location_name[] = "Blacksmith Shop";

  add_counter(&story->blacksmith_shop_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    char select;
    uint8_t reroll_time = 10;

    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "x) Leave %s\n"
        "r) Reroll weapons\n",
        location_name, location_name);

    for (uint8_t i = 0; i < OFFERED_WEAPONS_LENGTH; i++) {
      printf("%u) Buy: %s (%up %uup %ud)\n", i, offered_weapons[i].name,
             offered_weapons[i].price, offered_weapons[i].upgrade_price,
             offered_weapons[i].damage);
    }

    printf("SELECT: ");
    select = getchar_clear();

    switch (select) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees stone walls\n"
            "made of large pieces of stone and a forge\n",
            location_name, player->name);
        break;
      }
      case 'x': {
        *location_id = city;
        leave_location = true;
        break;
      }
      case 'r': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "Rerolling weapons\n"
            "\n-----< WAIT (%us) >-----\n",
            location_name, reroll_time);

        for (uint8_t i = 0; i < reroll_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf("\n");

        for (uint8_t i = 0; i < OFFERED_WEAPONS_LENGTH; i++)
          offered_weapons[i] = generate_weapon();

        break;
      }
      default: {
        for (uint8_t i = 0; i < OFFERED_WEAPONS_LENGTH; i++) {
          struct Weapon weapon = offered_weapons[i];
          if (select != i + '0') {
            if (i + 1 == OFFERED_WEAPONS_LENGTH)
              printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n",
                     location_name);
            continue;
          }

          printf("\n-----< %s LOCATION >-----\n", location_name);
          if (player->gold < weapon.price) {
            printf("%s need %u gold for %s, but he has only %u gold\n",
                   player->name, weapon.price, weapon.name, player->gold);
          }

          player->weapon = weapon;

          printf("%s bought %s (%up %uup %ud)\n", player->name,
                 player->weapon.name, player->weapon.price,
                 player->weapon.upgrade_price, player->weapon.damage);

          break;
        }
      }
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void training_ground_loop(struct Character *player, struct Story *story,
                          LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Training Ground";

  add_counter(&story->training_ground_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "1) Leave %s\n"
        "2) Free training   ( 0 gold,  +1 max health, 10 sec)\n"
        "3) Short training  (10 gold,  +5 max health, 15 sec)\n"
        "4) Medium training (20 gold, +15 max health, 30 sec)\n"
        "5) Long training   (50 gold, +75 max health, 60 sec)\n"
        "SELECT: ",
        location_name, location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees a lot of training equipment\n",
            location_name, player->name);
        break;
      }
      case '1': {
        *location_id = city;
        leave_location = true;
        break;
      }
      case '2': {
        uint32_t train_price = 0;
        uint16_t max_health_upgrade = 1;
        uint8_t train_time = 10;

        if (player->max_health == CHARACTER_MAX_HEALTH) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already maxed his max health",
              location_name, player->name);
          break;
        }

        if (player->gold < train_price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, train_price, player->gold);
          break;
        }

        player->gold -= train_price;
        player->max_health += max_health_upgrade;

        if (player->max_health > CHARACTER_MAX_HEALTH)
          player->max_health = CHARACTER_MAX_HEALTH;

        printf("\n-----< WAIT (%us) >-----\n", train_time);

        for (uint8_t i = 0; i < train_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf(
            "\n\n-----< %s LOCATION >-----\n"
            "%s max health is now %u\n",
            location_name, player->name, player->max_health);

        break;
      }
      case '3': {
        uint32_t train_price = 10;
        uint16_t max_health_upgrade = 5;
        uint8_t train_time = 15;

        if (player->max_health == CHARACTER_MAX_HEALTH) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already maxed his max health",
              location_name, player->name);
          break;
        }

        if (player->gold < train_price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, train_price, player->gold);
          break;
        }

        player->gold -= train_price;
        player->max_health += max_health_upgrade;

        if (player->max_health > CHARACTER_MAX_HEALTH)
          player->max_health = CHARACTER_MAX_HEALTH;

        printf("\n-----< WAIT (%us) >-----\n", train_time);

        for (uint8_t i = 0; i < train_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf(
            "\n\n-----< %s LOCATION >-----\n"
            "%s max health is now %u\n",
            location_name, player->name, player->max_health);

        break;
      }
      case '4': {
        uint32_t train_price = 20;
        uint16_t max_health_upgrade = 15;
        uint8_t train_time = 30;

        if (player->max_health == CHARACTER_MAX_HEALTH) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already maxed his max health",
              location_name, player->name);
          break;
        }

        if (player->gold < train_price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, train_price, player->gold);
          break;
        }

        player->gold -= train_price;
        player->max_health += max_health_upgrade;

        if (player->max_health > CHARACTER_MAX_HEALTH)
          player->max_health = CHARACTER_MAX_HEALTH;

        printf("\n-----< WAIT (%us) >-----\n", train_time);

        for (uint8_t i = 0; i < train_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf(
            "\n\n-----< %s LOCATION >-----\n"
            "%s max health is now %u\n",
            location_name, player->name, player->max_health);

        break;
      }
      case '5': {
        uint32_t train_price = 50;
        uint16_t max_health_upgrade = 75;
        uint8_t train_time = 60;

        if (player->max_health == CHARACTER_MAX_HEALTH) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s already maxed his max health",
              location_name, player->name);
          break;
        }

        if (player->gold < train_price) {
          printf(
              "\n-----< %s LOCATION >-----\n"
              "%s need %u gold for this, but he has only %u gold\n",
              location_name, player->name, train_price, player->gold);
          break;
        }

        player->gold -= train_price;
        player->max_health += max_health_upgrade;

        if (player->max_health > CHARACTER_MAX_HEALTH)
          player->max_health = CHARACTER_MAX_HEALTH;

        printf("\n-----< WAIT (%us) >-----\n", train_time);

        for (uint8_t i = 0; i < train_time; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }

        printf(
            "\n\n-----< %s LOCATION >-----\n"
            "%s max health is now %u\n",
            location_name, player->name, player->max_health);

        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
// TODO: Rework tasks
void adventurer_guild_loop(struct Character *player, struct Story *story,
                           LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Adventurer Guild";

  add_counter(&story->adventurer_guild_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "x) Leave %s\n"
        "c) Cancel quest\n"
        "0) Take quest: Difficulty 0 (%s Room)\n"
        "1) Take quest: Difficulty 1 (Forest)\n"
        "2) Take quest: Difficulty 2 (Deep Forest, Mountain)\n"
        "3) Take quest: Difficulty 3 (Dead Forest)\n"
        "SELECT: ",
        location_name, location_name, player->name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees a small bar,\n"
            "a notice board, and a reception desk\n",
            location_name, player->name);
        break;
      }
      case 'x': {
        *location_id = city;
        leave_location = true;
        break;
      }
      case 'c': {
        printf(
            "\n-----< %s LOCATION ACTION >-----\n"
            "%s cancelled his quest\n",
            location_name, player->name);
        strcpy(story->quest.target_name, "");
        story->quest.target_count = 0;
        story->quest.reward_gold = 0;
        story->quest.progress_count = 0;
        break;
      }
      case '0': {
        printf("\n-----< %s LOCATION ACTION >-----\n", location_name);
        if (story->quest.target_count != 0) {
          printf("%s already has quest\n", player->name);
          break;
        }
        if (RND_MAX(1) == 0)
          strcpy(story->quest.target_name, "Rat");
        else
          strcpy(story->quest.target_name, "Spider");

        story->quest.target_count = RND_RANGE(25, 5);
        story->quest.reward_gold =
            story->quest.target_count * QUEST_GOLD_MODIFIER;
        story->quest.progress_count = 0;

        printf("%s took quest difficulty 0\n", player->name);

        print_player_quest(story);
        break;
      }
      case '1': {
        printf("\n-----< %s LOCATION ACTION >-----\n", location_name);
        if (story->quest.target_count != 0) {
          printf("%s already has quest\n", player->name);
          break;
        }
        switch (RND_MAX(3)) {
          case 0: {
            strcpy(story->quest.target_name, "Slime");
            break;
          }
          case 1: {
            strcpy(story->quest.target_name, "Wild Boar");
            break;
          }
          case 2: {
            strcpy(story->quest.target_name, "Goblin");
            break;
          }
          case 3: {
            strcpy(story->quest.target_name, "Forest Bandit");
            break;
          }
        }

        story->quest.target_count = RND_RANGE(25, 5);
        story->quest.reward_gold =
            story->quest.target_count * QUEST_GOLD_MODIFIER * 3;
        story->quest.progress_count = 0;

        printf("%s took quest difficulty 1\n", player->name);

        print_player_quest(story);
        break;
      }
      case '2': {
        printf("\n-----< %s LOCATION ACTION >-----\n", location_name);
        if (story->quest.target_count != 0) {
          printf("%s already has quest\n", player->name);
          break;
        }
        switch (RND_MAX(3)) {
          case 0: {
            strcpy(story->quest.target_name, "Forest Wraith");
            break;
          }
          case 1: {
            strcpy(story->quest.target_name, "Giant Snake");
            break;
          }
          case 2: {
            strcpy(story->quest.target_name, "Snow Leopard");
            break;
          }
          case 3: {
            strcpy(story->quest.target_name, "Ice Elemental");
            break;
          }
        }

        story->quest.target_count = RND_RANGE(25, 5);
        story->quest.reward_gold =
            story->quest.target_count * QUEST_GOLD_MODIFIER * 100;
        story->quest.progress_count = 0;

        printf("%s took quest difficulty 2\n", player->name);

        print_player_quest(story);
        break;
      }
      case '3': {
        printf("\n-----< %s LOCATION ACTION >-----\n", location_name);
        if (story->quest.target_count != 0) {
          printf("%s already has quest\n", player->name);
          break;
        }
        if (RND_MAX(1) == 0)
          strcpy(story->quest.target_name, "Undead Spirit");

        else
          strcpy(story->quest.target_name, "Undead Horde");

        story->quest.target_count = RND_RANGE(25, 5);
        story->quest.reward_gold =
            story->quest.target_count * QUEST_GOLD_MODIFIER * 200;
        story->quest.progress_count = 0;

        printf("%s took quest difficulty 3\n", player->name);

        print_player_quest(story);
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void dev_room_loop(struct Character *player, struct Story *story,
                   LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[] = "Dev Room";

  printf(
      "\n-----< %s LOCATION >-----\n"
      "!!! WARNING !!!\n"
      "This location is intended for game testing\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Start fight with enemy by id\n"
        "1) Enter Nvoid 255\n"
        "2) Enter location by id\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around and sees a mattress on the floor, a metal shelf,\n"
            "a plastic spruce, and a dinosaur-era computer\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        int enemy_id;
        char str[4];
        uint16_t prebattle_player_health = player->health;
        struct Character enemy;

        printf("ENTER ENEMY ID (uint8_t): ");

        getchars_clear(str, 4);
        enemy_id = atoi(str);

        if (enemy_id > 0xff) {
          printf("Invalid enemy id\n");
          break;
        }

        enemy = generate_enemy(enemy_id);
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          printf(
              "\n-----< AFTER BATTLE >-----\n"
              "%s can't die in %s\n",
              player->name, location_name);

          player->health = prebattle_player_health;
        }

        break;
      }
      case '1': {
        *location_id = nvoid;
        leave_location = true;
        break;
      }
      case '2': {
        int new_id;
        char str[4];

        printf("ENTER LOCATION ID (uint8_t): ");

        getchars_clear(str, 4);
        new_id = atoi(str);

        if (new_id > 0xff) {
          printf("Invalid location id\n");
          break;
        }

        *location_id = new_id;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void nvoid_loop(struct Character *player, struct Story *story,
                LOCATION_ID *location_id) {
  bool leave_location = false;
  char location_name[9];

  sprintf(location_name, "Nvoid %u", *location_id);

  printf(
      "\n-----< %s LOCATION >-----\n"
      "!!! WARNING !!!\n"
      "The game tried to send you to a location that does not exist\n"
      "To avoid possible problems, you were sent here\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leave_location) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Enter %s Room\n"
        "2) Enter Dev Room (MAY BREAK GAME)\n"
        "SELECT: ",
        location_name, player->name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player, story);
        break;
      }
      case 'l': {
        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s looks around but see nothing\n",
            location_name, player->name);
        break;
      }
      case 'e': {
        struct Character enemy = generate_enemy(UINT8_MAX);
        battle_enemy(story, player, &enemy);

        if (player->health == 0) {
          printf(
              "\n-----< AFTER BATTLE >-----\n"
              "%s was completely erased by forces that do not belong to this "
              "world\n",
              player->name);

          story->ending = 0;
          *location_id = nolocation;
          return;
        }

        break;
      }
      case '1': {
        *location_id = player_room;
        leave_location = true;
        break;
      }
      case '2': {
        *location_id = dev_room;
        leave_location = true;
        break;
      }
      default:
        printf("\n-----< %s LOCATION UNKNOWN ACTION >-----\n", location_name);
    }
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void location_loop(struct Character *player, struct Story *story) {
  LOCATION_ID current_location = player_room;
  struct Weapon offered_weapons[OFFERED_WEAPONS_LENGTH];

  for (uint8_t i = 0; i < OFFERED_WEAPONS_LENGTH; i++)
    offered_weapons[i] = generate_weapon();

  while (current_location != nolocation) {
    switch (current_location) {
      case player_room: {
        player_room_loop(player, story, &current_location);
        break;
      }
      case throne_room: {
        throne_room_loop(player, story, &current_location);
        break;
      }
      case demon_lord_castle: {
        demon_lord_castle_loop(player, story, &current_location);
        break;
      }
      case dead_forest: {
        dead_forest_loop(player, story, &current_location);
        break;
      }
      case deep_forest: {
        deep_forest_loop(player, story, &current_location);
        break;
      }
      case forest: {
        forest_loop(player, story, &current_location);
        break;
      }
      case hidden_garden: {
        hidden_garden_loop(player, story, &current_location);
        break;
      }
      case high_mountain: {
        high_mountain_loop(player, story, &current_location);
        break;
      }
      case mountain: {
        mountain_loop(player, story, &current_location);
        break;
      }
      case city: {
        city_loop(player, story, &current_location);
        break;
      }
      case tavern: {
        tavern_loop(player, story, &current_location);
        break;
      }
      case blacksmith_shop: {
        blacksmith_shop_loop(player, story, &current_location, offered_weapons);
        break;
      }
      case training_ground: {
        training_ground_loop(player, story, &current_location);
        break;
      }
      case adventurer_guild: {
        adventurer_guild_loop(player, story, &current_location);
        break;
      }
      case dev_room: {
        dev_room_loop(player, story, &current_location);
        break;
      }
      // If something went wrong player will be sent in void location
      default:
        nvoid_loop(player, story, &current_location);
    }
  }

  switch (story->ending) {
    case 0: {
      printf(STORY_ENDING0_NVOID_DEATH, player->name, player->name);
      break;
    }
    case 1: {
      printf(STORY_ENDING1_SUICIDE, player->name);
      break;
    }
    case 2: {
      printf(STORY_ENDING2_KILLED_BY_MONSTER, player->name);
      break;
    }
    case 3: {
      printf(STORY_ENDING3_KNOCKED_OUT, player->name, player->name);
      break;
    }
    default: {
      printf(STORY_ENDING_ERROR, story->ending);
    }
  }
}
