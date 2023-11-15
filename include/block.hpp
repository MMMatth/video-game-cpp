

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

  Block(string id, string name, bool isSolid, int millisecond_to_break = 2000,
        bool is_stackable = true, int amount = 1);

  /* getters */
  bool isSolid() const { return m_isSolid; }
  string getId() { return m_id; }
  int getHardness() { return m_time_to_break; }
  bool isBeingBroken() { return m_being_broken; }

  /* setters */
  void setHardness(int hardness) { m_time_to_break = hardness; }
  void setSolid(bool isSolid) { m_isSolid = isSolid; }
  void setBeingBroken(bool being_broken) { m_being_broken = being_broken; }

  /* other */
  string toString() const;

private:
  bool m_isSolid;
  string m_id;
  bool m_being_broken;
  int m_time_to_break;
};
static map<string, Block> blockMap = {
    {"AIR", Block("0", "AIR", false, false)},
    {"GRASS", Block("1", "GRASS", true)},
    {"DIRT", Block("2", "DIRT", true)},
    {"STONE", Block("3", "STONE", true)},
    {"LEAF", Block("4", "LEAF", false)},
    {"WOOD", Block("5", "WOOD", false)},
    {"WOOD_PLANK", Block("6", "WOOD_PLANK", true)},
    {"COBBLESTONE", Block("7", "COBBLESTONE", true)},
    {"BRICK", Block("8", "BRICK", true)},
    {"LIBRARY", Block("9", "LIBRARY", true)},
    {"RED_FLOWER", Block("10", "RED_FLOWER", false, true)},
    {"YELLOW_FLOWER", Block("11", "YELLOW_FLOWER", false, true)},
    {"TORCH", Block("12", "TORCH", false, true)}};

#endif