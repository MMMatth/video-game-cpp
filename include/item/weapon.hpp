#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

/** @brief Represents a weapon in the game. */
class Weapon : public Item {
private:
  /* data */
public:
  /** @brief Parameterized constructor for Weapon.
   * @param name The name of the weapon.
   * @param is_stackable Whether the weapon is stackable.
   * @param amount The amount of the weapon (default is 1).
   */
  Weapon(string name, bool is_stackable = false, int amount = 1);

  /** @brief default constructor */
  Weapon();
};

/** @brief the map with all weapon */
static map<string, Weapon> weaponMap = {{"IRON_SWORD", Weapon("IRON_SWORD")}};

#endif /* WEAPON_HPP */