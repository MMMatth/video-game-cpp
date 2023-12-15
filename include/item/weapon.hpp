#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

/** @brief Represents a weapon in the game. */
class Weapon : public Item {
private:
public:
  /** @brief Parameterized constructor for Weapon.
   */
  Weapon(string name, int raduis, int damage, bool is_stackable = false,
         int amount = 1);

  /** @brief default constructor */
  Weapon();
};

/** @brief the map with all weapon */
static map<string, Weapon> weaponMap = {
    {"IRON_SWORD", Weapon("IRON_SWORD", 5, 25)}};

#endif /* WEAPON_HPP */