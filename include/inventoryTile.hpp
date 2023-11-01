#ifndef INVENTORY_TILE_HPP
#define INVENTORY_TILE_HPP

#include "block.hpp"
#include "item.hpp"
#include <iostream>
#include <string>

class InventoryTile {
private:
  bool m_is_empty;
  Item m_item;

public:
  InventoryTile(Block block);
  InventoryTile();
  ~InventoryTile();
  Item getItem() { return m_item; }
  void setItem(Item item) {
    m_item = item;
    m_is_empty = false;
  }
  bool isEmpty() { return m_is_empty; }
};

#endif /* TILE_HPP */