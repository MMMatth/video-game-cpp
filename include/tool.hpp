#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "const.hpp"
#include "item.hpp"
#include "point.hpp"
#include <map>

using namespace std;

class Tool : public Item {
private:
  Point m_spriteSheet;

public:
  // Provide default arguments only in the declaration
  Tool(string name, int id, int spiritSheetX, int spiritSheetY,
       bool is_stackable = false, int amount = 1);
  Tool();
  /* getters */
  Point getSpriteSheet() { return m_spriteSheet; }
};

// Do not provide default arguments in the definition
Tool::Tool(string name, int id, int spritSheetX, int spritSheetY,
           bool is_stackable, int amount)
    : Item(name, id, is_stackable, amount),
      m_spriteSheet(spritSheetX, spritSheetY) {}

// Provide a default constructor for the Tool class
Tool::Tool() : Item("", 0, false, 0) {}

enum toolType { IRON_PICKAXE, IRON_AXE };
static map<toolType, Tool> toolMap = {
    {IRON_PICKAXE, Tool("iron_pickaxe", 100, 0, 0)},
    {IRON_AXE, Tool("iron_axe", 101, 0, 16)}};

#endif /* TOOLS_HPP */