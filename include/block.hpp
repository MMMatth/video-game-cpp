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

/**
 * @class Block
 * @brief Represents a block in the game world.
 *
 * This class inherits from the Item class and adds properties specific to blocks,
 * such as solidity and time to break.
*/
class Block : public Item {
public:

  /**
   * @brief Default constructor for Block class.
  */
  Block();

  /**
   * @brief Parameterized constructor for Block class.
   * @param id The unique identifier for the block.
   * @param name The name of the block.
   * @param isSolid Indicates whether the block is solid.
   * @param time_to_break The time it takes to break the block (default is 2000).
   * @param is_stackable Indicates whether the block is stackable (default is true).
   * @param amount The amount of the block (default is 1).
  */
  Block(string id, string name, bool isSolid, int time_to_break = 2000,
        bool is_stackable = true, int amount = 1);

  /**
   * @brief Getter function for checking if the block is solid.
   * @return True if the block is solid, false otherwise.
  */
  bool isSolid() const { return m_isSolid; }

  /**
   * @brief Getter function for retrieving the unique identifier of the block.
   * @return The unique identifier of the block.
  */
  string getId() { return m_id; }

  /**
   * @brief Getter function for retrieving the time it takes to break the block.
   * @return The time it takes to break the block.
  */
  int getTimeToBreak() { return m_time_to_break; }

  /**
   * @brief Setter function for setting the time it takes to break the block.
   * @param hardness The time it takes to break the block.
  */
  void setTimeToBreak(int hardness) { m_time_to_break = hardness; }

  /**
   * @brief Setter function for setting whether the block is solid.
   * @param isSolid True if the block is solid, false otherwise.
  */
  void setSolid(bool isSolid) { m_isSolid = isSolid; }

  /**
   * @brief Convert the block information to a string format.
   * @return A string representation of the block.
  */
  string toString() const;

private:
  bool m_isSolid;  /*Indicates whether the block is solid.*/
  string m_id;  /*The unique identifier of the block.*/
  int m_time_to_break; /*The time it takes to break the block.*/
};

/**
 * @brief Map of predefined blocks with their unique identifiers.
 * This map contains a set of predefined blocks with their unique identifiers
 * and corresponding Block objects.
 */
static map<string, Block> blockMap = {
    {"AIR", Block("0", "AIR", false, false)},
    {"GRASS", Block("1", "GRASS", true, 100)},
    {"DIRT", Block("2", "DIRT", true, 100)},
    {"STONE", Block("3", "STONE", true, 1000)},
    {"LEAF", Block("4", "LEAF", false, 10)},
    {"WOOD", Block("5", "WOOD", false, 1000)},
    {"WOOD_PLANK", Block("6", "WOOD_PLANK", true, 1000)},
    {"COBBLESTONE", Block("7", "COBBLESTONE", true, 1000)},
    {"BRICK", Block("8", "BRICK", true, 1000)},
    {"LIBRARY", Block("9", "LIBRARY", true, 1000)},
    {"RED_FLOWER", Block("10", "RED_FLOWER", false, 10, true)},
    {"YELLOW_FLOWER", Block("11", "YELLOW_FLOWER", false, 10, true)},
    {"TORCH", Block("12", "TORCH", false, 10, true)}};

#endif