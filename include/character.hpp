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
  Character(int x, int y, int life);
  bool loadFromCSV(string csvPath);
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
  int getLife() { return m_life; }
  /* setters */
  /* m_direction */
  void setFalling(bool falling) { m_direction["fall"] = falling; }
  void setJumping(bool jumping) { m_direction["jump"] = jumping; }
  void setGoingUp(bool inUp) { m_direction["up"] = inUp; }
  void setGoingRight(bool inRight) { m_direction["right"] = inRight; }
  void setGoingLeft(bool inLeft) { m_direction["left"] = inLeft; }

  /* m_collision */
  void setCollision(string key, bool value) { this->m_collision[key] = value; }
  /* other setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setTimeJump(int time) { m_timeJump = time; }
  void setWidth(int width) { this->m_width = width; }
  void setHeight(int height) { this->m_height = height; }
  void setLife(int life) { this->m_life = life; }
  void hit(int damage) { this->m_life -= damage; }
  void heal(int heal) { this->m_life += heal; }

  /* other */
  void moveX(int x);
  void moveY(int y);
  void save(string path);

private:
  bool m_save;                   /** if true the charcater is save in csv */
  Coord m_coord;                 /** coord in x y of the character*/
  map<string, bool> m_direction; /** Contains booleans for states: fall, jump,
                                    up, right, left. */
  map<string, bool>
      m_collision; /** Contains booleans for collision : up, down, right, left*/
  int m_timeJump;  /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
  int m_width;      /** width of the character */
  int m_height;     /** height of the character */
  int m_speed;      /** speed */
  int m_life;       /** life of the character */
};

#endif /* PERSONNAGE_HPP */
