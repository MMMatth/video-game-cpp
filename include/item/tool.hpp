#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

using namespace std;

class Tool : public Item {
private:
public:
  Tool(string name, bool is_stackable = false, int amount = 1);
  Tool();
};

static map<string, Tool> toolMap = {{"IRON_PICKAXE", Tool("IRON_PICKAXE")},
                                    {"IRON_AXE", Tool("IRON_AXE")}};

#endif /* TOOLS_HPP */