#include "../../include/gameplay/inventoryTile.hpp"

InventoryTile::InventoryTile(Item item) : m_is_empty(false), m_item(item) {}

InventoryTile::InventoryTile() : m_is_empty(true), m_item() {}

InventoryTile::~InventoryTile() {}

void InventoryTile::setAmount(int amount) {
  if (amount <= 0) {
    m_is_empty = true;
  } else if (amount > MAX_STACK_SIZE) {
    m_item.setAmount(MAX_STACK_SIZE);
  } else {
    m_item.setAmount(amount);
  }
}