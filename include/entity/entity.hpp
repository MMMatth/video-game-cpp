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

  /**
   * @brief Constructor for the Entity class.
   * @param x The initial x-coordinate of the entity.
   * @param y The initial y-coordinate of the entity.
   * @param width The width of the entity.
   * @param height The height of the entity.
   * @param speed The movement speed of the entity.
   * @param life The initial life points of the entity.
  */
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
  int getHeight() const { return m_height; } /*< Get the height of the entity. */
  int getWidth() const { return m_width; } /*< Get the width of the entity. */
  int getX() const { return m_coord.getX(); } /*< Get the x-coordinate of the entity. */
  int getY() const { return m_coord.getY(); }  /*< Get the y-coordinate of the entity. */
  int getSpeed() const { return m_speed; }  /*< Get the movement speed of the entity. */
  int getLife() const { return m_life; }  /*< Get the current life points of the entity. */
  map<string, bool> getDirection() const { return m_direction; } /*< Get the entity's movement direction. */
  map<string, bool> getCollision() const { return m_collision; } /*< Get the entity's collision status. */

  /* Setters */
  void setX(int x) { m_coord.setX(x); } /*< Set the x-coordinate of the entity. */
  void setY(int y) { m_coord.setY(y); }  /*< Set the y-coordinate of the entity. */
  void setLife(int life) { m_life = life; }  /*< Set the current life points of the entity. */
  void setDirection(string key, bool value) { m_direction[key] = value; } /*< Set the entity's movement direction. */
  void setCollision(string key, bool value) { m_collision[key] = value; } /*< Set the entity's collision status. */

  /* Other */
  void moveX(int x) { m_coord.setX(m_coord.getX() + x); } /*< Move the entity horizontally by a specified amount. */
  void moveY(int y) { m_coord.setY(m_coord.getY() + y); } /*< Move the entity vertically by a specified amount. */

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
