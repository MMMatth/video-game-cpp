#include "../../include/item/weapon.hpp"

Weapon::Weapon(string name, bool is_stackable, int amount)
    : Item(name, is_stackable, "WEAPON", amount) {}

Weapon::Weapon() : Item() {}