#include "../include/tool.hpp"

Tool::Tool(string id, int spriteX, int spriteY, int spriteW, int spriteH,
           bool is_stackable, int amount)
    : Item(id, spriteX, spriteY, spriteW, spriteH, is_stackable, amount) {}

Tool::Tool() : Item() {}