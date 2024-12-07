// TODO: City
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_nick(char *nick, size_t nick_len) {
  char c;
  int len;

  printf("Enter your nick(%zu): ", nick_len - 1);

  fgets(nick, nick_len, stdin);

  len = strlen(nick);

  if (nick[len - 1] == '\n')
    nick[len - 1] = '\0';
  else
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned int sum_chars(char *str) {
  size_t len = strlen(str);
  unsigned int sum = 0;

  for (size_t i = 0; i < len; i++) sum += str[i];

  return sum;
}

void print_status(char *nick, unsigned int coins, unsigned short max_hp,
                  int hp) {
  printf(
      "Welcome %s!\n"
      "You have %d coins.\n"
      "Your hp is %d/%d.\n",
      nick, coins, hp, max_hp);
}

int explore(char *nick, unsigned int *coins, unsigned short *max_hp, int *hp,
            char *weapon_name, unsigned short weapon_attack) {
  int r = rand() % 4;

  printf("%s begin exploring forest.\n", nick);

  if (r == 0) {
    unsigned char found_coins = rand() % 5;

    if (found_coins != 0) {
      *coins += found_coins;
      printf("Found %d(%d) coins.\n", found_coins, *coins);
    }

    if (*hp < *max_hp) {
      (*hp)++;
      printf("1(%d/%d) hp restored.\n", *hp, *max_hp);
    }
  } else {
    char enemy_name[7] = "Slime";
    unsigned short enemy_gold = 5 + rand() % 10;
    unsigned short enemy_attack = 1 + rand() % 2;
    int enemy_hp = 5 + rand() % 5;

    if (r == 2) {
      strcpy(enemy_name, "Goblin");
      enemy_gold = 15 + rand() % 35;
      enemy_attack = 3 + rand() % 7;
      enemy_hp = 10 + rand() % 15;
    } else if (r == 3) {
      strcpy(enemy_name, "Demon");
      enemy_gold = 100 + rand() % 900;
      enemy_attack = 50 + rand() % 200;
      enemy_hp = 100 + rand() % 900;
    }

    (*hp)--;

    if (*hp == 0) {
      printf(
          "%s was defeated by %s\n"
          "This is end of %s adventure.\n",
          nick, enemy_name, nick);
      return 1;
    }
    printf(
        "%s (%d hp) attacked %s.\n"
        "1(%d/%d) hp lost.\n",
        enemy_name, enemy_hp, nick, *hp, *max_hp);
    // Fight loop
    while (1) {
      char c;

      printf("'F'ight with monster, 'r'un away: ");
      c = getchar();
      if (c != 10) getchar();

      switch (c) {
        case 'f':
        case 'F': {
          // Attack enemy
          enemy_hp -= weapon_attack;
          printf(
              "%s hits %s with %s.\n"
              "%s loses %d(%d) hp.\n",
              nick, enemy_name, weapon_name, enemy_name, weapon_attack,
              enemy_hp);

          // Check enemy hp
          if (enemy_hp < 1) {
            printf("%s (%d hp) was defeated by %s using %s.\n", enemy_name,
                   enemy_hp, nick, weapon_name);
            *coins += enemy_gold;
            printf("%s got %d(%d) gold.\n", nick, enemy_gold, *coins);
            return 0;
          }

          *hp -= enemy_attack;
          printf(
              "%s attacks.\n"
              "%s loses %d(%d/%d) hp\n",
              enemy_name, nick, enemy_attack, *hp, *max_hp);
          break;
        }
        case 'r':
        case 'R': {
          printf("%s decided to ran away.\n", nick);
          return 0;
        }
        default:
          printf("Unknown action, choose one of suggested.\n");
      }
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  char nick[16];
  unsigned int coins;
  unsigned short max_hp = 10;
  int hp;
  char weapon_name[64] = "Hands";
  unsigned short weapon_attack = 5;
  unsigned short weapon_upgrade_cost = 5;

  get_nick(nick, sizeof(nick));

  srand(sum_chars(nick));
  coins = rand() % 50;
  hp = 1 + rand() % 9;

  print_status(nick, coins, max_hp, hp);

  while (1) {
    char c;
    printf(
        "Check 's'tatus, "
        "begin 'e'xplore (enter),"
        "visit 'c'ity, "
        "'q'uit game: ");
    switch (c = getchar()) {
      case 's':
      case 'S': {
        print_status(nick, coins, max_hp, hp);
        break;
      }
      case 'e':
      case 'E':
      case 10: {
        if (explore(nick, &coins, &max_hp, &hp, weapon_name, weapon_attack) ==
            1)
          return 0;
        break;
      }
      case 'c':
      case 'C':

      case 'q':
      case 'Q': {
        return 0;
      }
      default:
        printf("Unknown action, choose one of suggested.\n");
    }

    if (c != 10) getchar();
  }

  return 0;
}
