#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

class Weapon : public Item {
private:
  /* data */
public:
  Weapon(string name, bool is_stackable = false, int amount = 1);

  Weapon();
};

static map<string, Weapon> weaponMap = {{"IRON_SWORD", Weapon("IRON_SWORD")}};

#endif /* WEAPON_HPP */