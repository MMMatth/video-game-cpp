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
  bool m_save;               /**< Condition for saving */
  Coord m_pos;               /**< Camera position */
  int m_width = CAM_WIDTH;   /**< Camera width */
  int m_height = CAM_HEIGHT; /**< Camera height */

public:
  Cam();

  Cam(int x, int y, bool save);

  Cam(string csvPath, bool save);

  bool loadFromCSV(string csvPath);

  /* update */
  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);

  /* getters */
  int getX() { return m_pos.getX(); }
  int getY() { return m_pos.getY(); }
  int getTopLeftX() { return m_pos.getX() - m_width / 2; }
  int getTopLeftY() { return m_pos.getY() - m_height / 2; }
  Coord getPos() { return m_pos; }
  int getWidth() { return m_width; }
  int getHeight() { return m_height; }

  /* setters */
  void setX(int x) { m_pos.setX(x); }
  void setY(int y) { m_pos.setY(y); }
  void setPos(Coord pos) { m_pos = pos; }

  /* other */
  void reset(int x, int y);
  void save(string csvPath);
};

#endif // CAM_HPP