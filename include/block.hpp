

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "const.hpp"
#include "item.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Block : public Item {
public:
  Block();

  Block(string id, int spriteX, int spriteY, int spriteW, int spriteH,
        bool isSolid, bool is_stackable = true, int amount = 1);

  /* getters */
  bool isSolid() const { return m_isSolid; }

  /* setters */
  void setSolid(bool isSolid) { m_isSolid = isSolid; }

  /* other */
  std::string toString() const;

private:
  bool m_isSolid;
};

static std::map<string, Block> blockMap = {
    {"AIR", Block("AIR", 0, 0, 0, 0, false, false)},
    {"GRASS", Block("GRASS", 0, 0, 16, 16, true)},
    {"DIRT", Block("DIRT", 16, 0, 16, 16, true)},
    {"STONE", Block("STONE", 32, 0, 16, 16, true)}};
#endif