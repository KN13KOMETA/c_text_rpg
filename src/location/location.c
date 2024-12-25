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

  sprintf(location_name, "%s Room", player->name);
  add_counter(&story->player_room_counter);

  if (story->player_room_counter == 1) {
    printf(STORY_TEXT_PLAYER_ROOM1, player->name);
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
        struct Character enemy = generate_enemy(0);
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
        print_player(player, story);

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
void throne_room_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Throne Room";

  add_counter(&story->throne_room_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void demon_lord_castle_loop(struct Character *player, struct Story *story,
                            LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Demon Lord Castle";

  add_counter(&story->demon_lord_castle_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void dead_forest_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Dead Forest";

  add_counter(&story->dead_forest_counter);

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
        struct Character enemy = generate_enemy(UINT8_MAX);
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
void deep_forest_loop(struct Character *player, struct Story *story,
                      LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Deep Forest";

  add_counter(&story->deep_forest_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void forest_loop(struct Character *player, struct Story *story,
                 LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Forest";

  add_counter(&story->forest_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void hidden_garden_loop(struct Character *player, struct Story *story,
                        LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Hidden Garden";

  add_counter(&story->hidden_garden_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void high_mountain_loop(struct Character *player, struct Story *story,
                        LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "High Mountain";

  add_counter(&story->high_mountain_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void mountain_loop(struct Character *player, struct Story *story,
                   LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Mountain";

  add_counter(&story->mountain_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void city_loop(struct Character *player, struct Story *story,
               LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "City";

  add_counter(&story->city_counter);

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
        // TODO: CITY EXPLORE ACTIVITY
        printf("\nTODO: CITY EXPLORE ACTIVITY\n");
        break;
      }
      case '1': {
        *location_id = forest;
        leaveLocation = true;
        break;
      }
      case '2': {
        *location_id = mountain;
        leaveLocation = true;
        break;
      }
      case '3': {
        *location_id = tavern;
        leaveLocation = true;
        break;
      }
      case '4': {
        *location_id = blacksmith_shop;
        leaveLocation = true;
        break;
      }
      case '5': {
        *location_id = training_ground;
        leaveLocation = true;
        break;
      }
      case '6': {
        *location_id = adventurer_guild;
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
}  // DONE
void tavern_loop(struct Character *player, struct Story *story,
                 LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Tavern";

  add_counter(&story->tavern_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void blacksmith_shop_loop(struct Character *player, struct Story *story,
                          LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Blacksmith Shop";

  add_counter(&story->blacksmith_shop_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void training_ground_loop(struct Character *player, struct Story *story,
                          LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[] = "Training Ground";

  add_counter(&story->training_ground_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // Send player to void for now
    leaveLocation = true;
    *location_id = nvoid;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}
void adventurer_guild_loop(struct Character *player, struct Story *story,
                           LOCATION_ID *location_id) {
  // TODO: Write adventurer guild after adding all enemies
  bool leaveLocation = false;
  char location_name[] = "Adventurer Guild";

  add_counter(&story->adventurer_guild_counter);

  printf(
      "\n-----< %s LOCATION  >-----\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    // TODO: ADVENTURE GUILD FUNCTIONAL
    printf("\nTODO: ADVENTURE GUILD FUNCTIONAL\n");
    leaveLocation = true;
    *location_id = city;
  }

  printf(
      "\n-----< %s LOCATION >-----\n"
      "%s leaves %s\n",
      location_name, player->name, location_name);
}

void nvoid_loop(struct Character *player, struct Story *story,
                LOCATION_ID *location_id) {
  bool leaveLocation = false;
  char location_name[9];

  sprintf(location_name, "Nvoid %u", *location_id);

  printf(
      "\n-----< %s LOCATION >-----\n"
      "!!! WARNING !!!\n"
      "The game tried to send you to a location that does not exist\n"
      "To avoid possible problems, you were sent here\n"
      "%s enters %s\n",
      location_name, player->name, location_name);

  while (!leaveLocation) {
    printf(
        "\n-----< %s LOCATION ACTION >-----\n"
        "s) Status\n"
        "l) Look around\n"
        "e) Explore\n"
        "1) Return to location 0 (Recommended for player)\n"
        "2) Enter location id (!!! MAY BREAK GAME !!!)\n"
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
          return;
        }

        break;
      }
      case '1': {
        *location_id = 0;
        leaveLocation = true;
        break;
      }
      case '2': {
        LOCATION_ID new_id = *location_id;
        printf("LOCATION ID (uint 8): ");

        scanf("%u", location_id);
        if (new_id > 0xff) *location_id = 0xff;

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
        blacksmith_shop_loop(player, story, &current_location);
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
      // If something went wrong player will be sent in void location
      default:
        nvoid_loop(player, story, &current_location);
    }
  }

  printf("\n-----< ADVENTURE END >-----\n");
}
