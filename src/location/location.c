#include "location.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "../functions.h"

void player_room_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[CHARACTER_NAME_LENGTH + 5];

  sprintf(location_name, "%s room", player->name);

  if (story->firstPlayerRoomEnter == true) {
    story->firstPlayerRoomEnter = false;
    printf(
        "\n-----< %s LOCATION >-----\n"
        "%s wakes up very drunk\n"
        "Not remembering what happened yesterday\n",
        player->name, player->name);
  } else
    printf(
        "\n-----< %s LOCATION  >-----\n"
        "%s enters %s\n",
        location_name, player->name, location_name);

  while (!leaveLocation) {
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

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
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
        struct Character enemy = generate_enemy(0);
        battle_enemy(player, &enemy);

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
        leaveLocation = true;
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

        printf(
            "\n-----< SLEEP >-----\n"
            "%u health restored\n",
            restore_health);

        break;
      }
      case '3': {
        print_player(player);

        printf(
            "\n-----< %s LOCATION >-----\n"
            "%s commits suicide\n"
            "0 health left\n",
            location_name, player->name);
        player->health = 0;
        return;
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
void throne_room_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void demon_lord_castle_loop(struct Character *player,
                            LOCATION_ID *location_id) {
  *location_id = nvoid;
}

void dead_forest_loop(struct Character *player, LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Dead Forest";

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Enter home\n"
        "2) Leave %s\n"
        "SELECT: ",
        location_name, location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
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
        struct Character enemy = generate_enemy(UINT8_MAX);
        battle_enemy(player, &enemy);

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
        *location_id = 0;
        leaveLocation = true;
        break;
      }
      case '2': {
        *location_id = 2;
        leaveLocation = true;
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
void deep_forest_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void forest_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}

void hidden_garden_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void high_mountain_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void mountain_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}

void city_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void tavern_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void blacksmith_shop_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void training_ground_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}
void adventurer_guild_loop(struct Character *player, LOCATION_ID *location_id) {
  *location_id = nvoid;
}

void nvoid_loop(struct Character *player, LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[9];

  sprintf(location_name, "void %u", *location_id);

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Return to location 0\n"
        "SELECT: ",
        location_name);

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
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
        battle_enemy(player, &enemy);

        if (player->health == 0) {
          printf(
              "\n-----< AFTER BATTLE >-----\n"
              "%s was completely erased by forces that do not belong to this "
              "world\n",
              player->name);
          return;
        }

        break;
      }
      case '1': {
        *location_id = 0;
        leaveLocation = true;
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

  while (current_location != nolocation) {
    switch (current_location) {
      case player_room: {
        player_room_loop(player, story, &current_location);
        break;
      }
      case throne_room: {
        throne_room_loop(player, &current_location);
        break;
      }
      case demon_lord_castle: {
        demon_lord_castle_loop(player, &current_location);
        break;
      }
      case dead_forest: {
        dead_forest_loop(player, &current_location);
        break;
      }
      case deep_forest: {
        deep_forest_loop(player, &current_location);
        break;
      }
      case forest: {
        forest_loop(player, &current_location);
        break;
      }
      case hidden_garden: {
        hidden_garden_loop(player, &current_location);
        break;
      }
      case high_mountain: {
        high_mountain_loop(player, &current_location);
        break;
      }
      case mountain: {
        mountain_loop(player, &current_location);
        break;
      }
      case city: {
        city_loop(player, &current_location);
        break;
      }
      case tavern: {
        tavern_loop(player, &current_location);
        break;
      }
      case blacksmith_shop: {
        blacksmith_shop_loop(player, &current_location);
        break;
      }
      case training_ground: {
        training_ground_loop(player, &current_location);
        break;
      }
      case adventurer_guild: {
        adventurer_guild_loop(player, &current_location);
        break;
      }
      // If something went wrong player will be sent in void location
      default:
        nvoid_loop(player, &current_location);
    }
  }

  printf("\n-----< ADVENTURE END >-----\n");
}
