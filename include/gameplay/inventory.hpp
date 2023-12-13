#ifndef inventory_hpp
#define inventory_hpp

#include "../item/block.hpp"
#include "../item/item.hpp"
#include "../item/tool.hpp"
#include "../item/weapon.hpp"

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "craft.hpp"
#include "inventoryTile.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/** @brief class who implement the inv*/
class Inventory {
private:
  bool m_save; /** bool true if the inventory is save */
  InventoryTile m_inventory[INV_HEIGHT][INV_WIDTH]; /** 2D tab contain every
                                                       inventory tile*/
  InventoryTile m_selected_tile; /**  inventory tile temporarily contains the
                                    item which moves */
  int m_pos_item_hand;           /** int number included between 0 and 8*/
  bool m_is_open;                /** bool true if the inventory is open */
  Craft m_craft;                 /** craft object */

public:
  /** @brief a function who init a void inv*/
  void initVoidInventory();

  /** @brief default constructor */
  Inventory();

  /** @brief constructor who load the inventory from a csv file */
  Inventory(string csvPath, bool save);

  /** @brief destructor */
  ~Inventory();

  /** @brief function who init data from csv file */
  bool loadFromCSV(const string &csvPath);

  /** @brief function who swap two item in two tile
   * @param t1 the first tile
   * @param t2 the second tile
   */
  void swapItem(InventoryTile *t1, InventoryTile *t2);

  /** @brief function who add a item in the inv
   * @param item the item to add
   */
  void addItem(Item item);

  /** @brief function who removeItem
   * @param pos the coord of the tile to remove
   * @param amount the amount of item to remove
   */
  void removeItem(Coord pos, int amount);

  /** @brief function who handle the left click (mainly move item)
   * @param mouseX the x position of the mouse
   */
  void handleLeftClick(int mouseX, int mouseY, int camX, int camY);

  /** @brief function who handle the right click ( mainly craft part )*/
  void handleRightClick(int mouseX, int mouseY, int camX, int camY);

  /* setters */
  void open();
  void setPosHand(int newPosHand);
  void nextPosHand();
  void prevPosHand();

  /** @brief function who return true if the x and y is over the inv*/
  bool isOverInv(int x, int y, int camX, int camY);

  /** @brief function who return the pos of a tile depending on x and y
   * @return the coord of the tile (-1 , -1) if the tile is not in the inv
   */
  Coord getTileCoord(int mouseX, int mouseY, int camX, int camY);

  /** @brief function who return the Tile with the item selected */
  InventoryTile getSelectedTile() { return m_selected_tile; }

  /** @brief function who return the tile at the coord*/
  InventoryTile getTile(Coord tile_coord);

  /** @brief function who return the pos of the hand*/
  int getPosHand() { return m_pos_item_hand; }

  /** @brief function who return the item at the coord*/
  Item getItemAt(Coord tile_coord);

  /** @brief function who return true if the inv is open*/
  bool isOpen() { return m_is_open; }

  /** @brief function who return the item at the pos hand*/
  Item getItemPosHand();

  /** @brief function who reset the inv
   * @param save true if we want to save the inv
   * @param path the path of the file to save
   */
  void reset(bool save,
             string path = string(SAVE_PATH) + string(INV_FILE_NAME));

  /** @brief function who save the inv in a csv file */
  void save(string csvPath);

  /** @brief function for update the craft*/
  void update(bool day);
};

#endif /* inventory_hpp */