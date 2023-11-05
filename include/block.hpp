

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "character.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "item.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Block : public Item {
public:
  Block();

  Block(string id, bool isSolid, bool is_stackable = true, int amount = 1);

  /* getters */
  bool isSolid() const { return m_isSolid; }

  /* setters */
  void setSolid(bool isSolid) { m_isSolid = isSolid; }

  /* other */
  std::string toString() const;

private:
  bool m_isSolid;
};

static std::map<string, Block> blockMap = {{"AIR", Block("AIR", false, false)},
                                           {"GRASS", Block("GRASS", true)},
                                           {"DIRT", Block("DIRT", true)},
                                           {"STONE", Block("STONE", true)}};
#endif