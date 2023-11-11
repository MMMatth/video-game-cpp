#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "const.hpp"
#include "coord.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;

using namespace std;

class Character {
public:
  /* constructor */
  Character(int x, int y);
  /* destructor */
  // ~Personnage();

  void initSprites(Texture &spritesheet);

  void update();
  /* getters */
  unordered_map<string, Sprite> getSprites() { return sprites; }
  map<string, bool> getDirection() { return m_direction; }
  map<string, bool> getCollision() { return m_collision; }
  int getHeight() { return m_height; }
  int getWidth() { return m_width; }
  int getX() { return m_coord.getX(); }
  int getY() { return m_coord.getY(); }
  int getTimeJump() { return m_timeJump; }
  int getJumpHeight() { return m_jumpHeight; }
  int getVitesse() { return m_speed; }
  bool isInFall() { return m_direction["isFalling"]; }
  bool isInJump() { return m_direction["isGoingUp"]; }
  /* setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setFalling(bool falling) { this->m_direction["isFalling"] = falling; }
  void setJumping(bool jumping) { this->m_direction["isJumping"] = jumping; }
  void setGoingUp(bool inUp) { this->m_direction["isGoingUp"] = inUp; }
  void setTimeJump(int time) { this->m_timeJump = time; }
  void setGoingRight(bool inRight) {
    this->m_direction["isGoingRight"] = inRight;
  }
  void setGoingLeft(bool inLeft) { this->m_direction["isGoingLeft"] = inLeft; }
  void setCollision(string key, bool value) { this->m_collision[key] = value; }
  void setCollisionFalseExcept(string key);
  void setWidth(int width) { this->m_width = width; }
  void setHeight(int height) { this->m_height = height; }
  /* other */
  void deplacerX(int x);
  void deplacerY(int y);

  string toString();

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

  unordered_map<string, Sprite> sprites;
  Texture texture;
};

#endif /* PERSONNAGE_HPP */
