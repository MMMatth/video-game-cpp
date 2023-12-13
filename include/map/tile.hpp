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
  Color m_color;         /**< predominant color of the tile */

public:
  /* constructor */
  Tile()
      : m_isBackground(false), m_block(), m_coord(0, 0), m_isBreaking(false) {}
  Tile(Block block, int x, int y, bool isBackground = false);

  Tile(int x, int y, bool isBackground = false);

  /* getters */
  int getX() const { return m_coord.getX(); }
  int getY() const { return m_coord.getY(); }
  bool isBackground() const { return m_isBackground; }
  Block *getBlock() { return &m_block; }
  bool isBreaking() { return m_isBreaking; }
  Clock getBreakingClock() { return m_breakingClock; }

  /* setters */
  void setBackground(bool isBackground) { m_isBackground = isBackground; }
  void setPosition(Coord position) { m_coord = position; }
  void setBlock(Block block) { m_block = block; }
  void setHardness(int hardness) { m_block.setTimeToBreak(hardness); }
  void setBreaking(bool isBreaking) { m_isBreaking = isBreaking; }

  /* other */
  void resetBreakingClock() { m_breakingClock.restart(); }

  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);

  void collide(Entity *entity);
  bool isCollidingEntity(Entity *entity);
};

#endif // TILE_HPP