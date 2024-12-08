// TODO: City/forge
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"

#define MAX_HP 55555

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

void print_status(char *nick, unsigned int coins, unsigned short max_hp, int hp,
                  char *weapon_name, unsigned short weapon_attack) {
  printf(
      "Welcome %s!\n"
      "You have %d coins.\n"
      "Your hp is %d/%d.\n"
      "Your weapon is %s (%d attack)\n",
      nick, coins, hp, max_hp, weapon_name, weapon_attack);
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
      printf("1 (%d/%d) hp restored.\n", *hp, *max_hp);
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

    if (*hp < 1) {
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
      printf("'F'ight with monster, 'r'un away: ");

      switch (getchar_clear()) {
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
          if (*hp < 0) {
            printf(
                "%s was defeated by %s\n"
                "This is end of %s adventure.\n",
                nick, enemy_name, nick);
            return 1;
          }
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

int tavern(char *nick, unsigned int *coins, int *hp, unsigned short *max_hp) {
  char dish_name[8] = "Beer";
  unsigned short dish_cost = 2;
  unsigned short dish_hp_restore = 0;

  printf("%s enters tavern.\n", nick);

  while (1) {
    if (*max_hp == *hp) {
      printf("%s (%d hp) already have max hp.\n", nick, *hp);
      printf("%s enters city.\n", nick);
      return 0;
    }

    printf(
        "'B'eer (-2 c=+1 max hp)\n"
        "'S'alad (-10 c=+7 max hp)\n"
        "'C'hicken (-50 c=+40 max hp)\n"
        "'e'xit tavern: ");

    switch (getchar_clear()) {
      case 'b':
      case 'B': {
        dish_hp_restore = 1;
        break;
      }
      case 's':
      case 'S': {
        strcpy(dish_name, "Salad");
        dish_cost = 10;
        dish_hp_restore = 7;
        break;
      }
      case 'c':
      case 'C': {
        strcpy(dish_name, "Chicken");
        dish_cost = 50;
        dish_hp_restore = 40;
        break;
      }
      case 'e':
      case 'E': {
        printf("%s enters city.\n", nick);
        return 0;
      }
      default:
        printf("Unknown action, choose one of suggested.\n");
    }

    if (dish_hp_restore == 0) continue;
    if (dish_cost > *coins) {
      printf("%s (%d c) doesn't have enough coins for %s.\n", nick, *coins,
             dish_name);
      continue;
    }

    *coins -= dish_cost;
    *hp += dish_hp_restore;
    if (*hp > *max_hp) *hp = *max_hp;
    printf(
        "%s consume %s.\n"
        "Hp now is %d. %d coins left.\n",
        nick, dish_name, *hp, *coins);
  }

  return 0;
}

int training_ground(char *nick, unsigned int *coins, unsigned short *max_hp) {
  char train_name[7] = "Short";
  unsigned short train_cost = 2;
  unsigned short train_hp_upgrade = 0;

  printf("%s enters training ground.\n", nick);

  while (1) {
    if (*max_hp == MAX_HP) {
      printf("%s (%d max hp) already maxed hp.\n", nick, *max_hp);
      printf("%s enters city.\n", nick);
      return 0;
    }

    printf(
        "'S'hort train (-2 c=+1 max hp)\n"
        "'m'edium train (-10 c=+7 max hp)\n"
        "'l'ong train (-50 c=+40 max hp)\n"
        "'e'xit training ground: ");

    switch (getchar_clear()) {
      case 's':
      case 'S': {
        train_hp_upgrade = 1;
        break;
      }
      case 'm':
      case 'M': {
        strcpy(train_name, "Medium");
        train_cost = 10;
        train_hp_upgrade = 7;
        break;
      }
      case 'l':
      case 'L': {
        strcpy(train_name, "Long");
        train_cost = 50;
        train_hp_upgrade = 40;
        break;
      }
      case 'e':
      case 'E': {
        printf("%s enters city.\n", nick);
        return 0;
      }
      default:
        printf("Unknown action, choose one of suggested.\n");
    }

    if (train_hp_upgrade == 0) continue;
    if (train_cost > *coins) {
      printf("%s (%d c) doesn't have enough coins for %s train.\n", nick,
             *coins, train_name);
      continue;
    }

    *coins -= train_cost;
    *max_hp += train_hp_upgrade;
    if (*max_hp > MAX_HP) *max_hp = MAX_HP;
    printf(
        "%s did %s train.\n"
        "Max hp now is %d. %d coins left.\n",
        nick, train_name, *max_hp, *coins);
  }

  return 0;
}

int visit_city(char *nick, unsigned int *coins, unsigned short *max_hp, int *hp,
               char *weapon_name, unsigned short *weapon_attack,
               unsigned short *weapon_upgrade_cost) {
  printf("%s enters city.\n", nick);

  while (1) {
    printf(
        "Check 's'tatus, "
        "Sit on 'b'ench, "
        "visit 't'avern,\n"
        "visit 'f'orge, "
        "training 'g'round, "
        "'l'eave city: ");
    switch (getchar_clear()) {
      case 's':
      case 'S': {
        print_status(nick, *coins, *max_hp, *hp, weapon_name, *weapon_attack);
        break;
      }
      case 'b':
      case 'B': {
        printf("%s sits on bench and enjoy city view", nick);
        fflush(stdout);
        for (int i = 0; i < 10; i++) {
          sleep(1);
          printf(".");
          fflush(stdout);
        }
        printf("\n");
        if (*hp == *max_hp) break;

        (*hp)++;
        printf("%s restored 1 hp (%d/%d) hp.\n", nick, *hp, *max_hp);
        break;
      }
      case 't':
      case 'T': {
        tavern(nick, coins, hp, max_hp);
        break;
      }
      case 'f':
      case 'F': {
        break;
      }
      case 'g':
      case 'G': {
        training_ground(nick, coins, max_hp);
        break;
      }
      case 'l':
      case 'L': {
        return 0;
      }
      default:
        printf("Unknown action, choose one of suggested.\n");
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

  print_status(nick, coins, max_hp, hp, weapon_name, weapon_attack);

  while (1) {
    printf(
        "Check 's'tatus, "
        "begin 'e'xplore (enter), "
        "visit 'c'ity, "
        "'q'uit game: ");

    switch (getchar_clear()) {
      case 's':
      case 'S': {
        print_status(nick, coins, max_hp, hp, weapon_name, weapon_attack);
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
      case 'C': {
        visit_city(nick, &coins, &max_hp, &hp, weapon_name, &weapon_attack,
                   &weapon_upgrade_cost);
        break;
      }

      case 'q':
      case 'Q': {
        return 0;
      }
      default:
        printf("Unknown action, choose one of suggested.\n");
    }
  }

  return 0;
}
