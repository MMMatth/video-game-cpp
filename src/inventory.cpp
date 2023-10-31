#include "../include/inventory.hpp"

inventory::inventory(/* args */) {}

inventory::~inventory() {
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      m_inventory[i][j] = tile();
    }
  }
}
