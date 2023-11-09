#include "../include/tool.hpp"

Tool::Tool(string name, bool is_stackable, int amount)
    : Item(name, is_stackable, amount) {}

Tool::Tool() : Item() {}