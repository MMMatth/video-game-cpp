#ifndef TILE_HPP
#define TILE_HPP

#include "block.hpp"
#include "const.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <iostream>
#include <string>
using namespace std;

class Tile {
private:
  Block m_block;
  Point m_position;

public:
  Tile(Block block, int x, int y);
  Tile(int x, int y);
  void setPosition(Point position) { m_position = position; }
  int getX() const { return m_position.getX(); }
  int getY() const { return m_position.getY(); }
  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);
  void collide(Personnage *perso);
  Block getBlock() const { return m_block; }
  string toString() { return m_block.toString(); }
};

#endif // TILE_HPP