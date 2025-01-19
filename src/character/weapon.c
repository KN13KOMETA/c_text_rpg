#include "weapon.h"

#include <stdio.h>
#include <string.h>

#include "../functions.h"
#include "character.h"

struct Weapon generate_weapon(void) {
  struct Weapon weapon;
  unsigned short base_attack;
  unsigned int base_cost;
  float attack_modifier = 1;
  float cost_modifier = 1;
  char reforge[10];
  char quality[9];
  char material[8];
  char weapon_type[11];

  // Reforge
  switch (RND_MAX(3)) {
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
      if (RND_MAX(1) == 0) {
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
  switch (RND_MAX(3)) {
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
      if (RND_MAX(1) == 0) {
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
  switch (RND_MAX(3)) {
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
      if (RND_MAX(1) == 0) {
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
  switch (RND_MAX(4)) {
    case 0: {
      strcpy(weapon_type, "Stick");
      base_attack = 5;
      base_cost = 1;
      break;
    }
    case 1: {
      strcpy(weapon_type, "Dagger");
      base_attack = 15;
      base_cost = 10;
      break;
    }
    case 2: {
      strcpy(weapon_type, "Sword");
      base_attack = 20;
      base_cost = 20;
      break;
    }
    case 3: {
      strcpy(weapon_type, "Spear");
      base_attack = 30;
      base_cost = 25;
      break;
    }
    case 4: {
      switch (RND_MAX(2)) {
        case 0: {
          strcpy(weapon_type, "Bow");
          base_attack = 50;
          base_cost = 40;
          break;
        }
        case 1: {
          strcpy(weapon_type, "Crossbow");
          base_attack = 60;
          base_cost = 60;
          break;
        }
        case 2: {
          if (RND_MAX(1) == 0) {
            strcpy(weapon_type, "Magic Wand");
            base_attack = 75;
            base_cost = 100;
          } else {
            strcpy(weapon_type, "Magic Gun");
            base_attack = 100;
            base_cost = 200;
          }
          break;
        }
      }
      break;
    }
  }

  sprintf(weapon.name, "%s %s %s %s", reforge, quality, material, weapon_type);
  weapon.damage = base_attack * attack_modifier;
  weapon.price = base_cost * cost_modifier;
  weapon.upgrade_price = ((cost_modifier + attack_modifier) / 2) * 10;

  if (weapon.damage > WEAPON_MAX_DAMAGE) weapon.damage = WEAPON_MAX_DAMAGE;

  return weapon;
}

void upgrade_weapon(struct Weapon *weapon) {
  uint16_t new_damage = weapon->damage * 1.25;
  uint32_t new_upgrade_price = weapon->upgrade_price * 1.5;

  if (new_damage < weapon->damage)
    new_damage = WEAPON_MAX_DAMAGE;
  else if (new_damage == weapon->damage)
    new_damage += 1;

  if (new_upgrade_price < weapon->upgrade_price)
    new_upgrade_price = CHARACTER_MAX_GOLD;
  else if (new_upgrade_price == weapon->upgrade_price)
    new_upgrade_price += 1;

  weapon->damage = new_damage;
  weapon->upgrade_price = new_upgrade_price;
}
