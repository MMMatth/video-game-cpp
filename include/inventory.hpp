/**
 * \file inventory.hpp
 * \author Matthieu Gaudel et Papa El Hadji G Cissé
 * \brief class Inventory
 *
 */

#ifndef inventory_hpp
#define inventory_hpp

#include "const.hpp"
#include "inventoryTile.hpp"
#include <cassert>
#include <string>
#include <vector>

using namespace std;

/**
 * \brief class Inventory
 * la premiere ligne de l'inventaire contient les objet dans la main du joueur
 */
class Inventory {
private:
  InventoryTile m_inventory[INVENTORY_HEIGHT][INVENTORY_WIDTH];

public:
  Inventory();
  Inventory(string csvPath);
  void swapItem(int x1, int y1, int x2, int y2);
  void addItem(Item item);

  string toString();
  // ~Inventory();
};

#endif /* inventory_hpp */