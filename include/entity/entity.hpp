#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

using namespace std;

/**
 * @class Entity
 * @brief Represents a generic entity in the game.
 *
 * This class serves as the base class for all entities in the game, providing
 * common properties and behaviors such as position, movement, collisions, and
 * life points.
 */

class Entity {
public:
  Entity(int x, int y, int width, int height, int speed, int life)
      : m_coord(x, y), m_width(width), m_height(height), m_speed(speed),
        m_life(life) {
    m_direction = {{"right", true},
                   {"left", false},
                   {"jump", false},
                   {"up", false},
                   {"fall", true}};
    m_collision = {
        {"up", false}, {"down", false}, {"left", false}, {"right", false}};
  }

  // virtual void update() = 0;

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
  void reduceLife(int life) { m_life = m_life - life; }
  void setDirection(string key, bool value) { m_direction[key] = value; }
  void setCollision(string key, bool value) { m_collision[key] = value; }

  /* Other */
  void moveX(int x) {
    m_coord.setX(m_coord.getX() + x);
  } /*< Move the entity horizontally by a specified amount. */
  void moveY(int y) {
    m_coord.setY(m_coord.getY() + y);
  } /*< Move the entity vertically by a specified amount. */

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
