#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;

using namespace std;

class Character {
public:
  /* constructor */
  Character(string path);
  Character(int x, int y);
  void init();
  /* destructor */
  // ~Personnage();
  /* update */
  void update();

  /* getters */
  map<string, bool> getDirection() { return m_direction; }
  map<string, bool> getCollision() { return m_collision; }
  int getHeight() { return m_height; }
  int getWidth() { return m_width; }
  int getX() { return m_coord.getX(); }
  int getY() { return m_coord.getY(); }
  int getTimeJump() { return m_timeJump; }
  int getJumpHeight() { return m_jumpHeight; }
  int getVitesse() { return m_speed; }
  /* setters */
  /* m_direction */
  void setFalling(bool falling) { m_direction["fall"] = falling; }
  void setJumping(bool jumping) { m_direction["jump"] = jumping; }
  void setGoingUp(bool inUp) { m_direction["up"] = inUp; }
  void setGoingRight(bool inRight) { m_direction["right"] = inRight; }
  void setGoingLeft(bool inLeft) { m_direction["left"] = inLeft; }
  /* m_collision */
  void setCollision(string key, bool value) { this->m_collision[key] = value; }
  void setCollisionFalseExcept(string key);
  /* other setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setTimeJump(int time) { m_timeJump = time; }
  void setWidth(int width) { this->m_width = width; }
  void setHeight(int height) { this->m_height = height; }
  /* other */
  void deplacerX(int x);
  void deplacerY(int y);
  void save(string path);

private:
  Coord m_coord;
  bool m_isFalling;
  map<string, bool> m_direction;
  map<string, bool> m_collision;
  int m_timeJump;
  int m_jumpHeight;
  int m_width;
  int m_height;
  int m_speed;
};

#endif /* PERSONNAGE_HPP */
