#include "../../include/item/tool.hpp"

Tool::Tool(string name, bool is_stackable, int amount)
    : Item(name, is_stackable, "TOOL", amount) {}

Tool::Tool() : Item() {}