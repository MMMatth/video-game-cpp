#include "../include/block.hpp"

// Constructeur par défaut
Block::Block()
    : m_spriteSheet(Point(0, 0)), m_id(0), m_name(""), m_isSolid(false) {}

// Constructeur avec initialisation des attributs
Block::Block(int spriteSheetX, int spriteSheetY, int id, std::string name,
             bool isSolid)
    : m_spriteSheet(Point(spriteSheetX, spriteSheetY)), m_isSolid(isSolid),
      Item(name, id) {}

// Getters
Point Block::getSpriteSheet() const { return m_spriteSheet; }

// int Block::getId() const { return m_id; }

// std::string Block::getName() const { return m_name; }

bool Block::isSolid() const { return m_isSolid; }

// Setters
void Block::setSpriteSheetX(int spriteSheetX) {
  m_spriteSheet.setX(spriteSheetX);
}

void Block::setSpriteSheetY(int spriteSheetY) {
  m_spriteSheet.setY(spriteSheetY);
}

// void Block::setId(int number) { m_id = number; }

// void Block::setName(std::string name) { m_name = name; }

void Block::setSolid(bool isSolid) { m_isSolid = isSolid; }

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