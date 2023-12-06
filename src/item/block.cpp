#include "../../include/item/block.hpp"

/* constructor */
Block::Block() : m_isSolid(false), Item(), m_id(""), m_time_to_break(0) {}

Block::Block(string id, string name, bool isSolid, int hardeness,
             bool is_stackable, int amount)
    : m_isSolid(isSolid), Item(name, is_stackable, "BLOCK", amount), m_id(id),
      m_time_to_break(hardeness) {}
/* other */
string Block::to_string() const {
  string s = "Block : ";
  s += to_string();
  s += " isSolid : " + std::to_string(m_isSolid);
  return s;
}
