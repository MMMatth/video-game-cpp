#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "const.hpp"
#include "item.hpp"
#include "point.hpp"
#include <map>

using namespace std;

class Tool : public Item {
private:
public:
  /* constructor */
  Tool(string name, int id, int spiritSheetX, int spiritSheetY,
       bool is_stackable = false, int amount = 1);
  Tool();
  /* destructor */
  ~Tool(){};
};

Tool::Tool(string name, int id, int spritSheetX, int spritSheetY,
           bool is_stackable, int amount)
    : Item(name, id, is_stackable, spritSheetX, spritSheetY, amount) {}

Tool::Tool() : Item() {}

/* enum */
enum toolType { IRON_PICKAXE, IRON_AXE };
static map<toolType, Tool> toolMap = {
    {IRON_PICKAXE, Tool("iron_pickaxe", 100, 0, 86)},
    {IRON_AXE, Tool("iron_axe", 101, 16, 86)}};

#endif /* TOOLS_HPP */