
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

/* what needs to be subtracted from the cam to get the lower bar position */
#define X_LOWER_BAR_OFFSET (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2
#define Y_LOWER_BAR_OFFSET -(CAM_HEIGHT / 2 - INVENTORY_TILE_SIZE * 2)
/* what needs to be subtracted from the cam to get the inv position */
#define X_INV_OFFSET (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2
#define Y_INV_OFFSET (INVENTORY_HEIGHT * INVENTORY_TILE_SIZE) / 2

#define TOP_LEFT_INV_TILE (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2

using namespace std;

class Inventory {
private:
  bool m_save;
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
  bool loadFromCSV(const std::string &csvPath);

  void swapItem(InventoryTile *t1, InventoryTile *t2);
  void addItem(Item item);
  void removeItem(Coord pos, int amount);

  /* handle */
  /** function who return if a coord is on a tile of the inv*/
  void handleClick(int mouseX, int mouseY, int persoX, int persoY);

  /* setters */
  void open();

  void setPosHand(int newPosHand);
  void nextPosHand();
  void prevPosHand();

  /* getters */

  /** function who return the selected object */
  bool isOverInv(int x, int y, int camX, int camY);
  Coord getTileCoord(int mouseX, int mouseY, int persoX, int persoY);
  InventoryTile getSelectedTile();
  InventoryTile getTile(Coord tile_coord);
  int getPosHand();
  Item getItemAt(Coord tile_coord);
  bool isOpen();
  Item getItemPosHand();
  /* other */
  void save(string csvPath);
  string toString();
};

#endif /* inventory_hpp */