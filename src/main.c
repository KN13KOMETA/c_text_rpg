#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character/character.h"
#include "functions.h"
#include "location/location.h"
#include "story/story.h"

#if RAND_MAX < INT16_MAX
#error RAND_MAX IS LOWER THAN INT16_MAX
#endif

void get_player_nick(struct Character *player) {
  char c;
  int len;

  printf(
      "\n-----< ADVENTURE START >-----\n"
      "Enter your nick(%u): ",
      CHARACTER_NAME_LENGTH - 1);

  getchars_clear(player->name, CHARACTER_NAME_LENGTH);
}

/* int main(int argc, char *argv[]) { */
int main(void) {
  struct Character player;
  struct Story story = get_story();

#ifdef DEBUG
  printf("\n-----< DEBUG MODE >-----\n");
#endif /* ifdef DEBUG */

  printf(STORY_DISCLAIMER);
  switch (getchar_clear()) {
    case 'y':
      break;
    default: {
      printf("Consent not received, exiting the game.\n");
      return 0;
    }
  }

  get_player_nick(&player);

  // Init seed using nick
  {
    unsigned int new_seed = 0;
    size_t len = strlen(player.name);

    for (size_t i = 0; i < len; i++) new_seed += player.name[i];

    srand(new_seed);
  }

  player = generate_player(player.name);
  print_player(&player, &story);
  location_loop(&player, &story);

  printf("\n-----< ADVENTURE END >-----\n");

  return 0;
}
