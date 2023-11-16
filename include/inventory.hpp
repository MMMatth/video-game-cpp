
#ifndef inventory_hpp
#define inventory_hpp

#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "inventoryTile.hpp"
#include "item.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Inventory {
private:
  InventoryTile
      m_inventory[INVENTORY_HEIGHT]
                 [INVENTORY_WIDTH]; /** 2D tab contain every inventory tile*/
  InventoryTile m_selected_tile;    /**  inventory tile temporarily contains the
                                       item which moves */
  int m_pos_item_hand;              /** int number included between 0 and 8*/
  bool m_is_open;                   /** bool true if the inventory is open */

public:
  /* Constructeur */
  Inventory();
  Inventory(string csvPath);
  void loadFromCSV(const std::string &csvPath);

  void swapItem(Coord p1, Coord p2);
  void swapItem(InventoryTile *t1, InventoryTile *t2);
  void addItem(Item item);
  void removeItem(Coord pos, int amount);

  /* handle */
  void handleClick(int mouseX, int mouseY, int persoX, int persoY);

  /* setters */
  void open() {
    if (m_is_open) {
      m_is_open = false;
      addItem(*m_selected_tile.getItem());
      m_selected_tile = InventoryTile();
    } else {
      m_is_open = true;
    }
  }

  void setPosHand(int indice) {
    if (indice >= 0 && indice < INVENTORY_WIDTH) {
      m_pos_item_hand = indice;
    } else {
      cerr << "setPosHand : the indice is not in the inventory" << endl;
    }
  }

  /* getters */
  InventoryTile getSelectedTile() { return m_selected_tile; }
  Coord getInventoryPosition(int mouseX, int mouseY, int persoX, int persoY);
  InventoryTile getTile(Coord pos) {
    return m_inventory[pos.getX()][pos.getY()];
  }
  int getPosHand() { return m_pos_item_hand; }
  Item getItemAt(Coord pos) {
    return *m_inventory[pos.getX()][pos.getY()].getItem();
  }
  bool isOpen() { return m_is_open; }
  Item getItemPosHand() {
    return *m_inventory[INVENTORY_HEIGHT - 1][m_pos_item_hand].getItem();
  }

  /* other */
  void save(string csvPath);

  string toString();
};

#endif /* inventory_hpp */