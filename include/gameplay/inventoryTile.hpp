#ifndef INVENTORY_TILE_HPP
#define INVENTORY_TILE_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"
#include "../item/tool.hpp"

#include "../utils/const.hpp"
#include <iostream>
#include <string>

/** @brief Represents a single tile in the player's inventory. */
class InventoryTile {
private:
  bool m_is_empty; /** Flag indicating whether the tile is empty. */
  Item m_item;     /** Item stored in the inventory tile. */

public:
  /** @brief Construct an InventoryTile with a specified Item. */
  InventoryTile(Item item);

  /** @brief Construct an empty InventoryTile. */
  InventoryTile();

  /** @brief Destroy the InventoryTile. */
  ~InventoryTile();

  /** @brief function to get the item of the tile
   * @return a pointer to the item of the tile
   */
  Item *getItem() { return &m_item; }

  /** @brief function to get the item type
   * @return the item type
   */
  string getItemType() { return m_item.getType(); }

  /** @brief is emty function
   * @return true if the tile is empty, false otherwise
   */
  bool isEmpty() { return m_is_empty; }

  /** @brief function to set the amount of the item */
  void setAmount(int amount);

  /** @brief function to set the is stackable flag of the item */
  void setIsStackable(bool is_stackable) {
    m_item.setIsStackable(is_stackable);
  }

  /** @brief function to set the is empty flag of the tile */
  void setIsEmpty(bool is_empty) { m_is_empty = is_empty; }

  /** @brief function to set the item of the tile */
  void setItem(Item item) {
    m_item = item;
    m_is_empty = false;
  }

  /** @brief Swap the content of the inventory tile with another inventory tile.
   */
  void swapWith(InventoryTile &other) {
    // we use swap c++ function to swap the content of the two tiles
    swap(m_is_empty, other.m_is_empty);
    swap(m_item, other.m_item);
  }
};

#endif /* TILE_HPP */