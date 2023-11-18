#ifndef CAM_HPP
#define CAM_HPP

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

public:
  Cam();
  Cam(int x, int y);
  Cam(string csvPath);
  bool loadFromCSV(string csvPath);
  /* getters */
  int getX() { return m_pos.getX(); }
  int getY() { return m_pos.getY(); }
  Coord getPos() { return m_pos; }

  /* setters */
  void setX(int x) { m_pos.setX(x); }
  void setY(int y) { m_pos.setY(y); }
  void setPos(Coord pos) { m_pos = pos; }

  /* other */
  void reset(int x, int y);
  void save(string csvPath);
};

#endif