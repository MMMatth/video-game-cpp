

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

  Block(int spriteSheetX, int spriteSheetY, int id, string name, bool isSolid,
        bool is_stackable = true);

  /* getters */
  bool isSolid() const { return m_isSolid; }

  /* setters */
  void setSolid(bool isSolid) { m_isSolid = isSolid; }

  /* other */
  std::string toString() const;

private:
  Point m_spriteSheet;
  int m_id;
  std::string m_name;
  bool m_isSolid;
};

enum BlockType { AIR, GRASS, DIRT, STONE };

static std::map<BlockType, Block> blockMap = {
    {AIR, Block(0, 0, 0, "air", false)},
    {GRASS, Block(0, 0, 1, "grass", true)},
    {DIRT, Block(16, 0, 2, "dirt", true)},
    {STONE, Block(32, 0, 3, "stone", true)}};
#endif