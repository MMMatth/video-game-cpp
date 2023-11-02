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
  Point m_item_position;

public:
  InventoryTile(Block block);
  InventoryTile();
  ~InventoryTile();
  Item getItem() { return m_item; }
  void setAmount(int amount) { m_item.setAmount(amount); }
  Point getItemPos() { return m_item_position; }
  void swapItem(InventoryTile &other) {
    Item tmp = m_item;
    m_item = other.getItem();
    other.setItem(tmp);
  }
  void setIsEmpty(bool is_empty) { m_is_empty = is_empty; }
  void setItem(Item item) {
    m_item = item;
    m_is_empty = false;
  }
  void setPos(int x, int y) {
    m_item_position.setX(x);
    m_item_position.setY(y);
  }
  bool isEmpty() { return m_is_empty; }
};

#endif /* TILE_HPP */