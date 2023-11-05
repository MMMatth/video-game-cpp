
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
  InventoryTile m_inventory[INVENTORY_HEIGHT][INVENTORY_WIDTH];
  InventoryTile m_selected_tile;
  int m_pos_hand;
  bool m_is_open;

public:
  /* Constructeur */
  Inventory();
  Inventory(string csvPath);
  /* Destruceur */
  ~Inventory();

  void swapItem(Coord p1, Coord p2);

  void swapItem(InventoryTile *t1, InventoryTile *t2);

  void addItem(Item item);

  void removeItem(Coord pos);

  /* handle */
  void handleClick(int mouseX, int mouseY, int persoX, int persoY);

  /* setters */
  void open() {
    if (m_is_open) {
      m_is_open = false;
      addItem(m_selected_tile.getItem());
      m_selected_tile = InventoryTile();
    } else {
      m_is_open = true;
    }
  }

  void setPosHand(int indice) { m_pos_hand = indice; }

  /* getters */
  InventoryTile getSelectedTile() { return m_selected_tile; }
  Coord getInventoryPosition(int mouseX, int mouseY, int persoX, int persoY);
  InventoryTile getTile(Coord pos) {
    return m_inventory[pos.getX()][pos.getY()];
  }
  int getPosHand() { return m_pos_hand; }
  Item getItemAt(Coord pos) {
    return m_inventory[pos.getX()][pos.getY()].getItem();
  }
  bool isOpen() { return m_is_open; }

  /* other */
  void save(string csvPath);

  string toString();
};

#endif /* inventory_hpp */