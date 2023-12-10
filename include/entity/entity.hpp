#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

using namespace std;

class Entity {
public:
  /* Constructeur */
  Entity()
      : m_coord(0, 0), m_width(0), m_height(0), m_speed(0), m_life(0),
        m_maxLife(0) {}
  Entity(int x, int y, int width, int height, int speed, int life, int maxLife)
      : m_coord(x, y), m_width(width), m_height(height), m_speed(speed),
        m_life(life), m_maxLife(maxLife) {

    m_direction = {{"right", true},
                   {"left", false},
                   {"jump", false},
                   {"up", false},
                   {"fall", true}};
    m_collision = {
        {"up", false}, {"down", false}, {"left", false}, {"right", false}};
  }

  /* Getters */
  int getHeight() const { return m_height; }
  int getWidth() const { return m_width; }
  int getX() const { return m_coord.getX(); }
  int getY() const { return m_coord.getY(); }
  int getSpeed() const { return m_speed; }
  int getLife() const { return m_life; }
  int getMaxLife() const { return m_maxLife; }
  map<string, bool> getDirection() const { return m_direction; }
  map<string, bool> getCollision() const { return m_collision; }

  /* Setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setLife(int life) { m_life = life; }
  void reduceLife(int life) { m_life = m_life - life; }
  void setDirection(string key, bool value) { m_direction[key] = value; }
  void setCollision(string key, bool value) { m_collision[key] = value; }

  /* Other */
  void moveX(int x) { m_coord.setX(m_coord.getX() + x); }
  void moveY(int y) { m_coord.setY(m_coord.getY() + y); }
  bool isColliding(int x, int y, int width, int height) {
    return (m_coord.getX() <= x + width && m_coord.getX() + m_width >= x &&
            m_coord.getY() <= y + height && m_coord.getY() + m_height >= y);
  }
  void heal(int heal) {
    if (m_life + heal > m_maxLife) {
      m_life = m_maxLife;
    } else {
      m_life += heal;
    }
  }
  void hit(int damage) {
    if (m_life - damage < 0) {
      m_life = 0;
    } else {
      m_life -= damage;
    }
  }

protected:
  Coord m_coord;
  map<string, bool> m_direction;
  map<string, bool> m_collision;
  int m_height;
  int m_width;
  int m_speed;
  int m_life;
  int m_maxLife;
};

#endif /* ENTITY_HPP */
