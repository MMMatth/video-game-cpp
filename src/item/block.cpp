#include "../../include/item/block.hpp"

Block::Block() : m_isSolid(false), Item(), m_id(""), m_time_to_break(0) {}

Block::Block(string id, string name, bool isSolid, int hardeness,
             bool is_stackable, int amount)
    : m_isSolid(isSolid), Item(name, is_stackable, "BLOCK", amount), m_id(id),
      m_time_to_break(hardeness) {}