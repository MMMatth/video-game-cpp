#include "../include/block.hpp"

/* constructor */
Block::Block()
    : m_spriteSheet(Point(0, 0)), m_id(0), m_name(""), m_isSolid(false) {}

Block::Block(int spriteSheetX, int spriteSheetY, int id, std::string name,
             bool isSolid, bool is_stackable)
    : m_isSolid(isSolid),
      Item(name, id, is_stackable, spriteSheetX, spriteSheetY) {}

/* other */
std::string Block::toString() const {
  std::string s = "Block {";
  s += "id: " + std::to_string(m_id) + ",";
  s += "spriteSheet: (" + std::to_string(m_spriteSheet.getX()) + ", " +
       std::to_string(m_spriteSheet.getY()) + "), ";
  s += "number: " + std::to_string(m_id) + ", ";
  s += "name: " + m_name + ", ";
  s += "isSolid: " + std::to_string(m_isSolid) + "}";
  return s;
}