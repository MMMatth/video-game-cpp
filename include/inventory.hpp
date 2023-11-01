/**
 * \file inventory.hpp
 * \author Matthieu Gaudel et Papa El Hadji G Cissé
 * \brief class Inventory
 *
 */

#ifndef inventory_hpp
#define inventory_hpp

#include "const.hpp"
#include "draw.hpp"
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
  int m_object_selected;

public:
  Inventory();
  Inventory(string csvPath);
  void swapItem(int x1, int y1, int x2, int y2);
  void addItem(Item item);
  void render(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
              int posCamX, int posCamY);
  void setItemSelected(int indice) { m_object_selected = indice; }
  int getItemSelected() { return m_object_selected; }
  void removeItem(int x, int y);
  string toString();
  // ~Inventory();
};

#endif /* inventory_hpp */