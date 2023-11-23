#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "const.hpp"
#include "coord.hpp"

class Sprites {
private:
  Coord m_coord;
  int m_width;
  int m_height;

public:
  /* constructor*/
  Sprites(Coord coord, int width, int height)
      : m_coord(coord), m_width(width), m_height(height) {}
  Sprites(int x, int y, int width, int height)
      : m_coord(x, y), m_width(width), m_height(height) {}
  Sprites() : m_coord(0, 0), m_width(0), m_height(0){};
  /* destructor */
  //   ~Sprites();
  /* getters */
  int getX() const { return m_coord.getX(); }
  int getY() const { return m_coord.getY(); }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  Coord getCoord() const { return m_coord; }
  /* setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setWidth(int width) { this->m_width = width; }
  void setHeight(int height) { this->m_height = height; }
  void setCoord(Coord coord) { this->m_coord = coord; }
  /* others */
  std::string toString() const {
    std::string s = "";
    s += "x : " + std::to_string(m_coord.getX());
    s += " y : " + std::to_string(m_coord.getY());
    s += " width : " + std::to_string(m_width);
    s += " height : " + std::to_string(m_height);
    return s;
  }
};

#endif /* SPRITES_HPP */