#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character/character.h"
#include "const.h"
#include "location/location.h"

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

  fgets(player->name, CHARACTER_NAME_LENGTH, stdin);

  len = strlen(player->name);

  if (player->name[len - 1] == '\n')
    player->name[len - 1] = '\0';
  else
    while ((c = getchar()) != '\n' && c != EOF);
}

/* int main(int argc, char *argv[]) { */
int main(void) {
  struct Character player;
  get_player_nick(&player);

  {
    unsigned int new_seed = 0;
    size_t len = strlen(player.name);

    for (size_t i = 0; i < len; i++) new_seed += player.name[i];

    srand(new_seed);
  }

  player = generate_player(player.name);
  print_player(&player);
  location_loop(&player);

  return 0;
}
