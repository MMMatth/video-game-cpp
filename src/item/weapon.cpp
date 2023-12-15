#include "../../include/item/weapon.hpp"

Weapon::Weapon(string name, int raduis, int damage, bool is_stackable,
               int amount)
    : Item(name, is_stackable, "WEAPON", amount) {}

Weapon::Weapon() : Item() {}