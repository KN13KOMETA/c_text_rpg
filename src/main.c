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

#ifndef COMMIT_SHORT_HASH
#error COMMIT_SHORT_HASH IS NOT DEFINED
#endif /* ifndef COMMIT_SHORT_HASH */

#ifndef PROJECT_NAME
#error PROJECT_NAME IS NOT DEFINED
#endif /* ifndef PROJECT_NAME */

#ifndef PROJECT_VERSION
#error PROJECT_VERSION IS NOT DEFINED
#endif /* ifndef PROJECT_VERSION */

// int main(int argc, char *argv[]) {
int main(void) {
  char select = 0;
  struct Character player;
  struct Story story = get_story();

#ifdef DEBUG
  printf("\n-----< DEBUG MODE >-----\n");
#endif /* ifdef DEBUG */

  printf(STORY_DISCLAIMER);

  if (getchar_clear(&select) == EOF) return 0;

  switch (select) {
    case 'y':
      break;
    default: {
      printf("Consent not received, exiting the game.\n");
      return 0;
    }
  }

  printf(
      "\n-----< ADVENTURE START >-----\n"
      "Enter your name(%u): ",
      CHARACTER_NAME_LENGTH - 1);

  if (getchars_clear(player.name, CHARACTER_NAME_LENGTH) == EOF) return 0;

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

  // Print game details
  {
    print_player(&player, &story);
    printf("\n-----< %s %s (%s) >-----\n", PROJECT_NAME, PROJECT_VERSION,
           COMMIT_SHORT_HASH);
    printf(
        "Repository: https://github.com/KN13KOMETA/c_text_rpg\n"
        "Discord: https://discord.gg/ADGTqPrYr8\n"
        "Personal Discord: https://discord.gg/d4rKqZs\n");
  }

  return 0;
}
