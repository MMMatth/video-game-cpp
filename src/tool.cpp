#include "../include/tool.hpp"

Tool::Tool(int id, string name, int spriteX, int spriteY, int spriteW,
           int spriteH, bool is_stackable, int amount)
    : Item(id, name, spriteX, spriteY, spriteW, spriteH, is_stackable, amount) {
}

Tool::Tool() : Item() {}