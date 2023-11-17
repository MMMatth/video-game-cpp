#include "../include/inventoryTile.hpp"

InventoryTile::InventoryTile(Block block) : m_is_empty(false), m_item(block) {}

InventoryTile::InventoryTile() : m_is_empty(true), m_item() {}

InventoryTile::~InventoryTile() {}