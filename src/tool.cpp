#include "../include/tool.hpp"

Tool::Tool(string id, bool is_stackable, int amount)
    : Item(id, is_stackable, amount) {}

Tool::Tool() : Item() {}