#ifndef CAM_HPP
#define CAM_HPP

#include "const.hpp"
#include "coord.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

class Cam {
private:
  bool m_save;
  Coord m_pos;
  int m_width = CAM_WIDTH;
  int m_height = CAM_HEIGHT;

public:
  Cam();
  Cam(int x, int y);
  Cam(string csvPath);
  // ~Cam();
  bool loadFromCSV(string csvPath);
  /* update */
  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);
  /* getters */
  int getX() const { return m_pos.getX(); }
  int getY() const { return m_pos.getY(); }
  Coord getPos() const { return m_pos; }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

  /* setters */
  void setX(int x) { m_pos.setX(x); }
  void setY(int y) { m_pos.setY(y); }
  void setPos(Coord pos) { m_pos = pos; }

  /* other */
  void reset(int x, int y);
  void save(string csvPath);
};

#endif