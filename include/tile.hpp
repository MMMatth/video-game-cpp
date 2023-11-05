#ifndef TILE_HPP
#define TILE_HPP

#include "block.hpp"
#include "character.hpp"
#include "const.hpp"
#include "coord.hpp"
#include <iostream>
#include <string>
using namespace std;

class Tile {
private:
  Block m_block;
  Coord m_position;

public:
  /* constructor */
  Tile(Block block, int x, int y);
  Tile(int x, int y);
  /* destructor */
  // ~Tile();
  /* getters */
  int getX() const { return m_position.getX(); }
  int getY() const { return m_position.getY(); }
  Block getBlock() const { return m_block; }
  /* setters */
  void setPosition(Coord position) { m_position = position; }
  /* other */
  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);
  void collide(Character *perso);
  string toString() { return m_block.toString(); }
};

#endif // TILE_HPP