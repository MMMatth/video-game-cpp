#ifndef inventory_hpp
#define inventory_hpp

#include "const.hpp"
#include "inventoryTile.hpp"
#include <vector>

class inventory {
private:
  tile m_inventory[INVENTORY_HEIGHT][INVENTORY_WIDTH];

public:
  inventory(/* args */);
  ~inventory();
};

#endif /* inventory_hpp */