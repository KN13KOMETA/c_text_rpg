#include "location.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "../const.h"
#include "../functions.h"

void home_loop(struct Character *player, uint8_t *location_id) {
  bool leaveLocation = false;

  char location_name[CHARACTER_NAME_LENGTH + 5];

  sprintf(location_name, "%s home", player->name);

  printf(
      "\n-----< LOCATION >-----\n"
      "%s enters %s\n",
      player->name, location_name);

  while (!leaveLocation) {
    printf(
        "\n-----< LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Leave home\n"
        "2) Sleep\n"
        "SELECT: ");

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
        break;
      }
      case 'l': {
        printf(
            "\n-----< LOCATION >-----\n"
            "%s looks around sees stone walls around him, "
            "bed and table, seems confortable enough\n",
            player->name);
        break;
      }
      case 'e': {
        // TODO:
        printf(
            "\n-----< NOCONTENT >-----\n"
            "Sending player to void.\n"
            "Good luck\n");

        *location_id = UINT8_MAX;
        leaveLocation = true;
        break;
      }
      case '1': {
        *location_id = 1;
        leaveLocation = true;
        break;
      }
      case '2': {
        uint8_t sleep_time = 30;
        uint16_t restore_health = player->max_health * 0.75;

        if (restore_health < player->health)
          restore_health = player->health - restore_health;
        else
          restore_health = 0;

        player->health += restore_health;

        printf(
            "\n-----< LOCATION >-----\n"
            "%s lays on bed and sleep\n"
            "\n-----< WAIT (%us) >-----\n",
            player->name, sleep_time);

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
      default:
        printf("\n-----< LOCATION UNKNOWN ACTION >-----\n");
    }
  }

  printf(
      "\n-----< LOCATION >-----\n"
      "%s leaves %s\n",
      player->name, location_name);
}

void void_loop(struct Character *player, uint8_t *location_id) {
  bool leaveLocation = false;
  char location_name[9];

  sprintf(location_name, "void %u", *location_id);

  printf(
      "\n-----< LOCATION >-----\n"
      "%s enters %s\n",
      player->name, location_name);

  while (!leaveLocation) {
    printf(
        "\n-----< LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Return to home\n"
        "SELECT: ");

    switch (getchar_clear()) {
      case 's': {
        print_player(player);
        break;
      }
      case 'l': {
        printf(
            "\n-----< LOCATION >-----\n"
            "%s looks around but see nothing\n",
            player->name);
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
        printf("\n-----< LOCATION UNKNOWN ACTION >-----\n");
    }
  }

  printf(
      "\n-----< LOCATION >-----\n"
      "%s leaves %s\n",
      player->name, location_name);
}

void location_loop(struct Character *player) {
  uint8_t location_id = 0;
  while (player->health != 0) {
    switch (location_id) {
      case 0: {
        home_loop(player, &location_id);
        break;
      }
      // If something went wrong player will be sent in void location
      default:
        void_loop(player, &location_id);
    }
  }

  printf("\n-----< ADVENTURE END >-----\n");
}
