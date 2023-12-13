#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "../entity/entity.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "item.hpp"
#include <iostream>
#include <string>

using namespace std;

class Block : public Item {
public:
  /** @brief default constructor */
  Block();

  /** @brief constructor with param
   * @param id the id of the block (used for the map)
   * @param name the name of the block
   * @param isSolid whether the block is solid
   * @param time_to_break the time it takes to break the block
   * @param is_stackable whether the block is stackable
   * @param amount the amount of the block
   */
  Block(string id, string name, bool isSolid, int time_to_break = 2000,
        bool is_stackable = true, int amount = 1);

  /** @brief return if the block is Solid */
  bool isSolid() const { return m_isSolid; }

  /** @brief return the id of the block */
  string getId() const { return m_id; }

  /** @brief return the time it takes to break the block */
  int getTimeToBreak() const { return m_time_to_break; }

  /** @brief set the time it takes to break the block */
  void setTimeToBreak(int hardness) { m_time_to_break = hardness; }

  /** @brief set the isSolid flag of the block */
  void setSolid(bool isSolid) { m_isSolid = isSolid; }

private:
  bool m_isSolid;      /** Whether the block is solid. */
  string m_id;         /** The ID of the block. */
  int m_time_to_break; /** The time it takes to break the block. */
};

/** @brief Map of predefined blocks in the game. */
static map<string, Block> blockMap = {
    {"AIR", Block("0", "AIR", false, false)},
    {"GRASS", Block("1", "GRASS", true, 100)},
    {"DIRT", Block("2", "DIRT", true, 100)},
    {"STONE", Block("3", "STONE", true, 1000)},
    {"LEAF", Block("4", "LEAF", true, 10)},
    {"WOOD", Block("5", "WOOD", true, 1000)},
    {"WOOD_PLANK", Block("6", "WOOD_PLANK", true, 1000)},
    {"COBBLESTONE", Block("7", "COBBLESTONE", true, 1000)},
    {"BRICK", Block("8", "BRICK", true, 1000)},
    {"LIBRARY", Block("9", "LIBRARY", true, 1000)},
    {"RED_FLOWER", Block("10", "RED_FLOWER", false, 10, true)},
    {"YELLOW_FLOWER", Block("11", "YELLOW_FLOWER", false, 10, true)},
    {"TORCH", Block("12", "TORCH", false, 10, true)}};

#endif /* BLOCK_HPP */