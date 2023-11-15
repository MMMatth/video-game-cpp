#include "../include/block.hpp"

/* constructor */
Block::Block() : m_isSolid(false), Item() {}

Block::Block(string id, string name, bool isSolid, int hardeness,
             bool is_stackable, int amount)
    : m_isSolid(isSolid), Item(name, is_stackable, "BLOCK", amount), m_id(id),
      m_time_to_break(hardeness) {}
/* other */
string Block::toString() const {
  string s = "Block : ";
  s += toString();
  s += " isSolid : " + std::to_string(m_isSolid);
  return s;
}