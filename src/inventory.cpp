#include "../include/inventory.hpp"

Inventory::Inventory(string csvPath) {}

Inventory::Inventory() {
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      m_inventory[i][j] = InventoryTile();
    }
  }
}

void Inventory::swapItem(int x1, int y1, int x2, int y2) {
  assert(
      (x1 >= 0 && x1 < INVENTORY_HEIGHT && y1 >= 0 && y1 < INVENTORY_WIDTH) &&
      "swapItem : valeur depasse la taille de l'inventaire");
  assert(
      (x2 >= 0 && x2 < INVENTORY_HEIGHT && y2 >= 0 && y2 < INVENTORY_WIDTH) &&
      "swapItem : valeur depasse la taille de l'inventaire");
  InventoryTile tmp = m_inventory[x1][y1];
  m_inventory[x1][y1] = m_inventory[x2][y2];
  m_inventory[x2][y2] = tmp;
}
void Inventory::addItem(Item item) {
  bool itemAdded = false;
  int i = 0;
  while (i < INVENTORY_HEIGHT && !itemAdded) {
    int j = 0;
    while (j < INVENTORY_WIDTH && !itemAdded) {
      if (m_inventory[i][j].isEmpty()) {
        m_inventory[i][j].setItem(item);
        itemAdded = true;
      }
      j++;
    }
    i++;
  }
}

string Inventory::toString() {
  string str = "\n";
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      str += "[";
      str += m_inventory[i][j].getItem().getName();
      str += "] ";
    }
    str += "\n";
  }
  return str;
}

// void inventory::drawInv(){

// }
