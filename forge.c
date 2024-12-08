#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_ATTACK 9999

void generate_weapon(char *weapon_name, unsigned short *weapon_attack,
                     unsigned int *weapon_cost) {
  unsigned short base_attack;
  unsigned int base_cost;
  float attack_modifier = 1;
  float cost_modifier = 1;
  char reforge[10];
  char quality[9];
  char material[8];
  char weapon[11];

  // Reforge
  switch (rand() % 4) {
    case 0: {
      strcpy(reforge, "Nasty");
      attack_modifier -= 0.15;
      break;
    }
    case 1: {
      strcpy(reforge, "Common");
      break;
    }
    case 2: {
      strcpy(reforge, "Epic");
      attack_modifier += 0.5;
      cost_modifier += 0.1;
      break;
    }
    case 3: {
      if (rand() % 2 == 0) {
        strcpy(reforge, "Legendary");
        attack_modifier += 1;
        cost_modifier += 0.2;
      } else {
        strcpy(reforge, "Godly");
        attack_modifier += 2;
        cost_modifier += 0.5;
      }
      break;
    }
  }

  // Quality
  switch (rand() % 4) {
    case 0: {
      strcpy(quality, "Bad");
      attack_modifier -= 0.15;
      cost_modifier -= 0.15;
      break;
    }
    case 1: {
      strcpy(quality, "Normal");
      break;
    }
    case 2: {
      strcpy(quality, "Good");
      attack_modifier += 0.5;
      cost_modifier += 0.25;
      break;
    }
    case 3: {
      if (rand() % 2 == 0) {
        strcpy(quality, "Perfect");
        attack_modifier += 1;
        cost_modifier += 0.5;
      } else {
        strcpy(quality, "Flawless");
        attack_modifier += 2;
        cost_modifier += 1.5;
      }
      break;
    }
  }

  // Material
  switch (rand() % 4) {
    case 0: {
      strcpy(material, "Wooden");
      attack_modifier -= 0.15;
      break;
    }
    case 1: {
      strcpy(material, "Copper");
      cost_modifier += 0.15;
      break;
    }
    case 2: {
      strcpy(material, "Iron");
      attack_modifier += 0.5;
      cost_modifier += 0.5;
      break;
    }
    case 3: {
      if (rand() % 2 == 0) {
        strcpy(material, "Steel");
        attack_modifier += 1;
        cost_modifier += 1;
      } else {
        strcpy(material, "Mithril");
        attack_modifier += 2;
        cost_modifier += 3;
      }
      break;
    }
  }

  // Weapon
  switch (rand() % 5) {
    case 0: {
      strcpy(weapon, "Stick");
      base_attack = 5;
      base_cost = 1;
      break;
    }
    case 1: {
      strcpy(weapon, "Dagger");
      base_attack = 15;
      base_cost = 10;
      break;
    }
    case 2: {
      strcpy(weapon, "Sword");
      base_attack = 20;
      base_cost = 20;
      break;
    }
    case 3: {
      strcpy(weapon, "Spear");
      base_attack = 30;
      base_cost = 25;
      break;
    }
    case 4: {
      switch (rand() % 3) {
        case 0: {
          strcpy(weapon, "Bow");
          base_attack = 50;
          base_cost = 40;
          break;
        }
        case 1: {
          strcpy(weapon, "Crossbow");
          base_attack = 60;
          base_cost = 60;
          break;
        }
        case 2: {
          if (rand() % 2 == 0) {
            strcpy(weapon, "Magic Wand");
            base_attack = 75;
            base_cost = 100;
          } else {
            strcpy(weapon, "Magic Gun");
            base_attack = 100;
            base_cost = 200;
          }
          break;
        }
      }
      break;
    }
  }

  sprintf(weapon_name, "%s %s %s %s", reforge, quality, material, weapon);
  *weapon_attack = base_attack * attack_modifier;
  *weapon_cost = base_cost * cost_modifier;

  if (*weapon_attack > MAX_ATTACK) *weapon_attack = MAX_ATTACK;
}

void forge(char *nick, unsigned int *coins, char *weapon_name,
           unsigned short *weapon_attack, unsigned int *weapon_upgrade_cost) {
  unsigned short upgraded_weapon_attack =
      *weapon_attack + 1 +
      ((*weapon_attack / 10) + (*weapon_upgrade_cost / 5)) / 2;
  char wname1[64];
  char wname2[64];
  char wname3[64];
  unsigned short wattack1;
  unsigned short wattack2;
  unsigned short wattack3;
  unsigned int wcost1;
  unsigned int wcost2;
  unsigned int wcost3;

  if (*weapon_attack == MAX_ATTACK) *weapon_upgrade_cost = 0;
  if (upgraded_weapon_attack > MAX_ATTACK) upgraded_weapon_attack = MAX_ATTACK;

  generate_weapon(wname1, &wattack1, &wcost1);
  generate_weapon(wname2, &wattack2, &wcost2);
  generate_weapon(wname3, &wattack3, &wcost3);

  printf("%s enters forge.\n", nick);

  while (1) {
    printf("Blacksmith offers weapons:\n");
    printf("1) %s (%d attack) - %d coins\n", wname1, wattack1, wcost1);
    printf("2) %s (%d attack) - %d coins\n", wname2, wattack2, wcost2);
    printf("3) %s (%d attack) - %d coins\n", wname3, wattack3, wcost3);
    printf("u) Upgrade %s (%d -> %d attack) - %d coins\n", weapon_name,
           *weapon_attack, upgraded_weapon_attack, *weapon_upgrade_cost);
    printf("Select one of option, 'e'xit forge: ");

    switch (getchar_clear()) {
      case '1': {
        if (wcost1 > *coins) {
          printf("%s doesn't have enough coins for %s.\n", nick, wname1);
          break;
        }
        *coins -= wcost1;
        strcpy(weapon_name, wname1);
        *weapon_attack = wattack1;
        *weapon_upgrade_cost = wcost1 / 5 + 1;
        printf(
            "%s buys %s (%d attack)\n"
            "%s enters city.\n",
            nick, wname1, wattack1, nick);
        return;
      }
      case '2': {
        if (wcost2 > *coins) {
          printf("%s doesn't have enough coins for %s.\n", nick, wname2);
          break;
        }
        *coins -= wcost2;
        strcpy(weapon_name, wname2);
        *weapon_attack = wattack2;
        *weapon_upgrade_cost = wcost2 / 5 + 1;
        printf(
            "%s buys %s (%d attack)\n"
            "%s enters city.\n",
            nick, wname2, wattack2, nick);
        return;
      }
      case '3': {
        if (wcost3 > *coins) {
          printf("%s doesn't have enough coins for %s.\n", nick, wname3);
          break;
        }
        *coins -= wcost3;
        strcpy(weapon_name, wname3);
        *weapon_attack = wattack3;
        *weapon_upgrade_cost = wcost3 / 5 + 1;
        printf(
            "%s buys %s (%d attack)\n"
            "%s enters city.\n",
            nick, wname3, wattack3, nick);
        return;
      }
      case 'u':
      case 'U': {
        if (*weapon_upgrade_cost == 0) {
          printf("%s already have max attack.\n", weapon_name);
          break;
        }
        if (*weapon_upgrade_cost > *coins) {
          printf("%s doesn't have enough coins for weapon upgrade.\n", nick);
          break;
        }
        *coins -= *weapon_upgrade_cost;
        *weapon_attack = upgraded_weapon_attack;
        if (*weapon_attack == MAX_ATTACK)
          *weapon_upgrade_cost = 0;
        else
          *weapon_upgrade_cost =
              *weapon_upgrade_cost + (*weapon_upgrade_cost / 4);
        printf("%s (%d attack) was upgraded.", weapon_name, *weapon_attack);
        return;
      }
      case 'e':
      case 'E':
        return;
    }
  }
}
