#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Entity {
public:
  // Entity() : m_coord(0, 0), m_width(0), m_height(0), m_speed(0), m_life(0) {
  //   m_direction = {{"right", false},
  //                  {"left", false},
  //                  {"jump", false},
  //                  {"up", false},
  //                  {"fall", true}};
  //   m_collision = {
  //       {"up", false}, {"down", false}, {"left", false}, {"right", false}};
  // }
  Entity(int x, int y, int width, int height, int speed, int life)
      : m_coord(x, y), m_width(width), m_height(height), m_speed(speed),
        m_life(life) {
    m_direction = {{"right", false},
                   {"left", false},
                   {"jump", false},
                   {"up", false},
                   {"fall", true}};
    m_collision = {
        {"up", false}, {"down", false}, {"left", false}, {"right", false}};
  }

  virtual void update() = 0;

  /* Getters */
  int getHeight() const { return m_height; }
  int getWidth() const { return m_width; }
  int getX() const { return m_coord.getX(); }
  int getY() const { return m_coord.getY(); }
  int getSpeed() const { return m_speed; }
  int getLife() const { return m_life; }
  map<string, bool> getDirection() const { return m_direction; }
  map<string, bool> getCollision() const { return m_collision; }

  /* Setters */
  void setX(int x) { m_coord.setX(x); }
  void setY(int y) { m_coord.setY(y); }
  void setLife(int life) { m_life = life; }
  void setDirection(string key, bool value) { m_direction[key] = value; }
  void setCollision(string key, bool value) { m_collision[key] = value; }

  /* Other */
  void moveX(int x) { m_coord.setX(m_coord.getX() + x); }
  void moveY(int y) { m_coord.setY(m_coord.getY() + y); }

protected:
  Coord m_coord;                 // Entity's position
  map<string, bool> m_direction; // Entity's movement direction
  map<string, bool> m_collision; // Entity's collision
  int m_height;                  // Entity's height
  int m_width;                   // Entity's width
  int m_speed;                   // Entity's movement speed
  int m_life;                    // Entity's life points

private:
  Entity(); // Private default constructor to prevent instantiation without
            // parameters
};

#endif /* ENTITY_HPP */
