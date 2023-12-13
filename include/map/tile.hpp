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

/** @brief Represents a tile on the game map. */
class Tile {
private:
  bool m_isBackground; /**< true = the tile is shaded*/
  Block m_block;       /**< The block contained in the tile. */
  Coord m_coord;       /**< The position of the tile (in tile) */
  bool m_isBreaking;   /**< Indicates whether the tile is currently breaking. */
  Clock m_breakingClock; /**< Clock used for tracking breaking progress. */

public:
  /** @brief default constructor */
  Tile()
      : m_isBackground(false), m_block(), m_coord(0, 0), m_isBreaking(false) {}

  /** @brief constructor
   * @param block the block contained in the tile
   * @param x the x coord of the tile (in tile)
   * @param y the y coord of the tile (in tile)
   * @param isBackground indicates whether the tile is a background tile
   */
  Tile(Block block, int x, int y, bool isBackground = false);

  /** @brief constructor
   * @param x the x coord of the tile (in tile)
   * @param y the y coord of the tile (in tile)
   * @param isBackground indicates whether the tile is a background tile
   */
  Tile(int x, int y, bool isBackground = false);

  /** @brief Get the X coordinate of the tile. */
  int getX() const { return m_coord.getX(); }

  /** @brief Get the Y coordinate of the tile. */
  int getY() const { return m_coord.getY(); }

  /** @brief Check if the tile is a background tile. */
  bool isBackground() const { return m_isBackground; }

  /** @brief Get the block associated with the tile. */
  Block *getBlock() { return &m_block; }

  /** @brief Check if the tile is breaking. */
  bool isBreaking() { return m_isBreaking; }

  /** @brief Get the breaking clock of the tile. */
  Clock getBreakingClock() { return m_breakingClock; }

  /** @brief Set if the tile is a background tile. */
  void setBackground(bool isBackground) { m_isBackground = isBackground; }

  /** @brief Set the position of the tile. */
  void setPosition(Coord position) { m_coord = position; }

  /** @brief Set the block associated with the tile. */
  void setBlock(Block block) { m_block = block; }

  /** @brief Set the hardness of the tile. */
  void setHardness(int hardness) { m_block.setTimeToBreak(hardness); }

  /** @brief Set if the tile is breaking. */
  void setBreaking(bool isBreaking) { m_isBreaking = isBreaking; }

  /** @brief restart the clock */
  void resetBreakingClock() { m_breakingClock.restart(); }

  /** @brief function who check if a rect is colliding with the tile */
  bool isColliding(int entity_x, int entity_y, int entity_width,
                   int entity_height, int entity_speed, int tile_x, int tile_y);

  /** @brief function who update the collide of the entity*/
  void collide(Entity *entity);

  /** @brief true if the enity touch a block */
  bool isCollidingEntity(Entity *entity);
};

#endif // TILE_HPP