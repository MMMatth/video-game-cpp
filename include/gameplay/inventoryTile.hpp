#ifndef INVENTORY_TILE_HPP
#define INVENTORY_TILE_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"
#include "../item/tool.hpp"

#include "../utils/const.hpp"
#include <iostream>
#include <string>

class InventoryTile {
private:
  bool m_is_empty;
  Item m_item;

public:
  /* constructor */
  InventoryTile(Block block);
  InventoryTile(int x, int y);
  InventoryTile();
  /* destructor */
  ~InventoryTile();
  /* getters */
  Item *getItem() { return &m_item; }
  string getItemType() { return m_item.getType(); }
  bool isEmpty() { return m_is_empty; }
  /* setters */
  void setAmount(int amount) { m_item.setAmount(amount); }
  void setIsStackable(bool is_stackable) {
    m_item.setIsStackable(is_stackable);
  }
  void setIsEmpty(bool is_empty) { m_is_empty = is_empty; }
  void setItem(Item item) {
    m_item = item;
    m_is_empty = false;
  }

  void swapWith(InventoryTile &other) {
    // we use swap c++ function to swap the content of the two tiles
    swap(m_is_empty, other.m_is_empty);
    swap(m_item, other.m_item);
  }
};

#endif /* TILE_HPP */