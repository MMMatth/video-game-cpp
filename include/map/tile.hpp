#ifndef TILE_HPP
#define TILE_HPP

#include "../entity/entity.hpp"
#include "../item/block.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

/**
 * @class Tile
 * @brief Represents a tile on the game map.
 *
 * This class encapsulates the properties and behaviors of a tile, including its
 * position, the block it contains, and whether it is currently breaking.
 */
class Tile {
private:
  bool m_isBackground;
  Block m_block;     /**< The block contained in the tile. */
  Coord m_coord;     /**< The position of the tile. */
  bool m_isBreaking; /**< Indicates whether the tile is currently breaking. */
  Clock m_breakingClock; /**< Clock used for tracking breaking progress. */

public:
  /**
   * Parameterized constructor for Tile.
   * @param block The block to be contained in the tile.
   * @param x The x-coordinate of the tile.
   * @param y The y-coordinate of the tile.
   * @param isBackground Indicates whether the tile is a background tile.
   */
  Tile(Block block, int x, int y, bool isBackground = false);

  /**
   * Parameterized constructor for Tile without specifying a block.
   * @param x The x-coordinate of the tile.
   * @param y The y-coordinate of the tile.
   * @param isBackground Indicates whether the tile is a background tile.
   */
  Tile(int x, int y, bool isBackground = false);

  /**
   * Get the x-coordinate of the tile.
   * @return The x-coordinate of the tile.
   */
  int getX() const { return m_coord.getX(); }

  /**
   * Get the y-coordinate of the tile.
   * @return The y-coordinate of the tile.
   */
  int getY() const { return m_coord.getY(); }
  bool isBackground() const { return m_isBackground; }

  /**
   * Get the block contained in the tile.
   * @return A pointer to the block contained in the tile.
   */
  Block *getBlock() { return &m_block; }

  /**
   * Check if the tile is currently breaking.
   * @return True if the tile is breaking, false otherwise.
   */
  bool isBreaking() { return m_isBreaking; }

  /**
   * Get the breaking clock for tracking breaking progress.
   * @return The breaking clock.
   */
  Clock getBreakingClock() { return m_breakingClock; }
  /* setters */
  void setBackground(bool isBackground) { m_isBackground = isBackground; }

  /**
   * Set the position of the tile.
   * @param position The new position of the tile.
   */
  void setPosition(Coord position) { m_coord = position; }

  /**
   * Set the block contained in the tile.
   * @param block The new block to be contained in the tile.
   */
  void setBlock(Block block) { m_block = block; }

  /**
   * Set the hardness of the block contained in the tile.
   * @param hardness The new hardness value.
   */
  void setHardness(int hardness) { m_block.setTimeToBreak(hardness); }

  /**
   * Set the breaking status of the tile.
   * @param isBreaking True if the tile is breaking, false otherwise.
   */
  void setBreaking(bool isBreaking) { m_isBreaking = isBreaking; }

  /**
   * Reset the breaking clock, typically used when the breaking process starts
   * anew.
   */
  void resetBreakingClock() { m_breakingClock.restart(); }

  /**
   * Check if the tile is within the specified camera bounds.
   * @param posCamX The x-coordinate of the camera.
   * @param posCamY The y-coordinate of the camera.
   * @param largeur The width of the camera.
   * @param hauteur The height of the camera.
   * @return True if the tile is within the camera bounds, false otherwise.
   */
  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);

  /**
   * Handle collision with an entity.
   * @param entity The entity to check for collision.
   */
  void collide(Entity *entity);

  /**
   * Get a string representation of the tile.
   * @return A string representation of the block contained in the tile.
   */
  string toString() { return m_block.to_string(); }
};

#endif // TILE_HPP