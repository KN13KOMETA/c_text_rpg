#include "location.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../functions.h"

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
        "1) Look around (doesn't waste turn)\n"
        "2) Leave\n"
        "3) Explore\n"
        "SELECT: ");

    switch (getchar_clear()) {
      case '1': {
        printf(
            "\n-----< LOCATION >-----\n"
            "%s looks around but see nothing\n",
            player->name);
        break;
      }
      case '2': {
        // Sending player home
        *location_id = 0;
        leaveLocation = true;
        break;
      }
      case '3': {
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
      // If something went wrong player will be sent in void location
      default:
        void_loop(player, &location_id);
    }
  }

  printf("\n-----< ADVENTURE END >-----\n");
}
