#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

using namespace std;

/** @brief Represents a tool in the game. */
class Tool : public Item {
private:
  /* data */
public:
  /** @brief Parameterized constructor for Tool.
   * @param name The name of the tool.
   * @param is_stackable Whether the tool is stackable.
   * @param amount The amount of the tool (default is 1).
   */
  Tool(string name, bool is_stackable = false, int amount = 1);

  /** @brief default constructor */
  Tool();
};

/** @brief the map with all tool */
static map<string, Tool> toolMap = {{"IRON_PICKAXE", Tool("IRON_PICKAXE")},
                                    {"IRON_AXE", Tool("IRON_AXE")}};

#endif /* TOOLS_HPP */