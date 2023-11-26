#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <map>

using namespace std;

/**
 * @class Tool
 * @brief Represents a tool item in the game.
 *
 * This class is derived from the Item class and represents tools that can be used
 * for specific actions in the game.
*/
class Tool : public Item {
private:
public:
  /* constructor */

  /**
   * Parameterized constructor for Tool.
   * @param name The name of the tool.
   * @param is_stackable Whether the tool is stackable (default is false).
   * @param amount The amount of the tool (default is 1).
  */
  Tool(string name, bool is_stackable = false, int amount = 1);

  /** Default constructor for Tool. */
  Tool();
  /* destructor */
  // ~Tool(){};


};

/**
 * @brief A map that associates tool names with Tool objects.
 *
 * This map is used to store predefined tool objects for easy access.
*/
static map<string, Tool> toolMap = {{"IRON_PICKAXE", Tool("IRON_PICKAXE")},
                                    {"IRON_AXE", Tool("IRON_AXE")}};

#endif /* TOOLS_HPP */