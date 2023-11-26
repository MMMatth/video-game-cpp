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

class Tile {
private:
  Block m_block;
  Coord m_coord;
  bool m_isBreaking;
  Clock m_breakingClock;

public:
  /* constructor */
  Tile(Block block, int x, int y);
  Tile(int x, int y);
  /* destructor */
  // ~Tile();
  /* getters */
  int getX() const { return m_coord.getX(); }
  int getY() const { return m_coord.getY(); }
  Block *getBlock() { return &m_block; }
  bool isBreaking() { return m_isBreaking; }
  Clock getBreakingClock() { return m_breakingClock; }
  /* setters */
  void setPosition(Coord position) { m_coord = position; }
  void setBlock(Block block) { m_block = block; }
  void setHardness(int hardness) { m_block.setTimeToBreak(hardness); }
  void setBreaking(bool isBreaking) { m_isBreaking = isBreaking; }
  void resetBreakingClock() { m_breakingClock.restart(); }
  /* other */
  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);
  void collide(Entity *entity);
  string toString() { return m_block.toString(); }
};

#endif // TILE_HPP