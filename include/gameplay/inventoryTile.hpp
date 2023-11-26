#ifndef INVENTORY_TILE_HPP
#define INVENTORY_TILE_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"
#include "../item/tool.hpp"

#include "../utils/const.hpp"
#include <iostream>
#include <string>

/**
 * @class InventoryTile
 * @brief Represents a single tile in the player's inventory.
 *
 * This class manages the content and state of a single tile in the player's inventory.
*/
class InventoryTile {
private:
  bool m_is_empty; /** Flag indicating whether the tile is empty. */
  Item m_item; /** Item stored in the inventory tile. */

public:
  /* constructor */

  /** Construct an InventoryTile with a specified block. */
  InventoryTile(Block block);
  /** Construct an empty InventoryTile with coordinates. */
  InventoryTile(int x, int y);
  /** Construct an empty InventoryTile. */
  InventoryTile();

  /* destructor */
  ~InventoryTile();

  /* getters */

  /** Get a pointer to the item in the inventory tile. */
  Item *getItem() { return &m_item; }

  /** Get the type of the item in the inventory tile. */
  string getItemType() { return m_item.getType(); }

  /** Check if the inventory tile is empty. */
  bool isEmpty() { return m_is_empty; }

  /* setters */

  /** Set the amount of items in the inventory tile. */
  void setAmount(int amount) { m_item.setAmount(amount); }

  /** Set whether the item in the inventory tile is stackable. */
  void setIsStackable(bool is_stackable) {
    m_item.setIsStackable(is_stackable);
  }

  /** Set whether the inventory tile is empty. */
  void setIsEmpty(bool is_empty) { m_is_empty = is_empty; }

  /** Set the item in the inventory tile. */
  void setItem(Item item) {
    m_item = item;
    m_is_empty = false;
  }

  /** Swap the content of the inventory tile with another inventory tile. */
  void swapWith(InventoryTile &other) {
    // we use swap c++ function to swap the content of the two tiles
    swap(m_is_empty, other.m_is_empty);
    swap(m_item, other.m_item);
  }
};

#endif /* TILE_HPP */