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
  Tool(int id, string name, int spriteX, int spriteY, int spriteW, int spriteH,
       bool is_stackable = false, int amount = 1);
  Tool();
  /* destructor */
  // ~Tool(){};
};

Tool::Tool(int id, string name, int spriteX, int spriteY, int spriteW,
           int spriteH, bool is_stackable, int amount)
    : Item(id, name, spriteX, spriteY, spriteW, spriteH, is_stackable, amount) {
}

Tool::Tool() : Item() {}

/* enum */
enum toolType { IRON_PICKAXE, IRON_AXE };
static map<toolType, Tool> toolMap = {
    {IRON_PICKAXE, Tool(100, "iron_pickaxe", 0, 86, 16, 16)},
    {IRON_AXE, Tool(101, "iron_axe", 16, 86, 16, 16)}};

#endif /* TOOLS_HPP */