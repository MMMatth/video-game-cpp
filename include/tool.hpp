#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "const.hpp"
#include "coord.hpp"
#include "item.hpp"
#include <map>

using namespace std;

class Tool : public Item {
private:
public:
  /* constructor */
  Tool(string id, int spriteX, int spriteY, int spriteW, int spriteH,
       bool is_stackable = false, int amount = 1);
  Tool();
  /* destructor */
  // ~Tool(){};
};

static map<string, Tool> toolMap = {
    {"IRON_PICKAXE", Tool("IRON_PICKAXE", 0, 86, 16, 16)},
    {"IRON_AXE", Tool("IRON_AXE", 16, 86, 16, 16)}};

#endif /* TOOLS_HPP */