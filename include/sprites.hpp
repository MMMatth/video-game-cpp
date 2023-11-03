#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "const.hpp"
#include "point.hpp"

class Sprites {
private:
  Point coord;
  int width;
  int height;

public:
  /* constructor*/
  Sprites(Point coord, int width, int height)
      : coord(coord), width(width), height(height) {}
  Sprites(int x, int y, int width, int height)
      : coord(x, y), width(width), height(height) {}
  Sprites() : coord(0, 0), width(0), height(0){};
  /* destructor */
  //   ~Sprites();
  /* getters */
  int getX() const { return coord.getX(); }
  int getY() const { return coord.getY(); }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  Point getCoord() const { return coord; }
  /* setters */
  void setX(int x) { coord.setX(x); }
  void setY(int y) { coord.setY(y); }
  void setWidth(int width) { this->width = width; }
  void setHeight(int height) { this->height = height; }
  void setCoord(Point coord) { this->coord = coord; }
  /* others */
  std::string toString() const {
    std::string s = "";
    s += "x : " + std::to_string(coord.getX());
    s += " y : " + std::to_string(coord.getY());
    s += " width : " + std::to_string(width);
    s += " height : " + std::to_string(height);
    return s;
  }
};

#endif /* SPRITES_HPP */