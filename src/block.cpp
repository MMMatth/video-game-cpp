#include "../include/block.hpp"

/* constructor */
Block::Block() : m_isSolid(false), Item() {}

Block::Block(string id, bool isSolid, bool is_stackable, int amount)
    : m_isSolid(isSolid), Item(id, is_stackable, amount) {}

/* other */
std::string Block::toString() const {
  std::string s = "Block : ";
  s += toString();
  s += " isSolid : " + std::to_string(m_isSolid);
  return s;
}