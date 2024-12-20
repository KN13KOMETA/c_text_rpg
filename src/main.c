#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "character/character.h"
#include "const.h"
#include "location/location.h"

#if RAND_MAX < INT16_MAX
#error RAND_MAX IS LOWER THAN INT16_MAX
#endif

#define MAX_HP 55555

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

unsigned int sum_chars(char *str) {
  size_t len = strlen(str);
  unsigned int sum = 0;

  for (size_t i = 0; i < len; i++) sum += str[i];

  return sum;
}

/* int main(int argc, char *argv[]) { */
int main(void) {
  struct Character player;
  get_player_nick(&player);
  srand(sum_chars(player.name));

  player = generate_player(player.name);
  print_player(&player);
  location_loop(&player);

  return 0;
}
