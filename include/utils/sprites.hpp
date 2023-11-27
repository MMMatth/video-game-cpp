#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "const.hpp"
#include "coord.hpp"

/**
 * @brief Class representing the coordinates and dimensions of a sprite.
 */
class Sprites {
private:
  Coord m_coord; ///< The coordinates of the top-left corner of the sprite.
  int m_width;   ///< The width of the sprite.
  int m_height;  ///< The height of the sprite.

public:
  /**
   * @brief Parameterized constructor.
   *
   * @param coord The coordinates of the top-left corner of the sprite.
   * @param width The width of the sprite.
   * @param height The height of the sprite.
   */
  Sprites(Coord coord, int width, int height)
      : m_coord(coord), m_width(width), m_height(height) {}

  /**
   * @brief Parameterized constructor.
   *
   * @param x The horizontal coordinate of the top-left corner of the sprite.
   * @param y The vertical coordinate of the top-left corner of the sprite.
   * @param width The width of the sprite.
   * @param height The height of the sprite.
   */
  Sprites(int x, int y, int width, int height)
      : m_coord(x, y), m_width(width), m_height(height) {}

  /**
   * @brief Default constructor.
   */
  Sprites() : m_coord(0, 0), m_width(0), m_height(0){};

  /**
   * @brief Destructor.
   */
  //   ~Sprites();

  /**
   * @brief Getter for the horizontal coordinate of the top-left corner of the sprite.
   *
   * @return The horizontal coordinate of the top-left corner of the sprite.
   */
  int getX() const { return m_coord.getX(); }

  /**
   * @brief Getter for the vertical coordinate of the top-left corner of the sprite.
   *
   * @return The vertical coordinate of the top-left corner of the sprite.
   */
  int getY() const { return m_coord.getY(); }

  /**
   * @brief Getter for the width of the sprite.
   *
   * @return The width of the sprite.
   */
  int getWidth() const { return m_width; }

  /**
   * @brief Getter for the height of the sprite.
   *
   * @return The height of the sprite.
   */
  int getHeight() const { return m_height; }

  /**
   * @brief Getter for the coordinates of the top-left corner of the sprite.
   *
   * @return The coordinates of the top-left corner of the sprite.
   */
  Coord getCoord() const { return m_coord; }

  /**
   * @brief Setter for the horizontal coordinate of the top-left corner of the sprite.
   *
   * @param x The new horizontal coordinate of the top-left corner of the sprite.
   */
  void setX(int x) { m_coord.setX(x); }

  /**
   * @brief Setter for the vertical coordinate of the top-left corner of the sprite.
   *
   * @param y The new vertical coordinate of the top-left corner of the sprite.
   */
  void setY(int y) { m_coord.setY(y); }

  /**
   * @brief Setter for the width of the sprite.
   *
   * @param width The new width of the sprite.
   */
  void setWidth(int width) { this->m_width = width; }

  /**
   * @brief Setter for the height of the sprite.
   *
   * @param height The new height of the sprite.
   */
  void setHeight(int height) { this->m_height = height; }

  /**
   * @brief Setter for the coordinates of the top-left corner of the sprite.
   *
   * @param coord The new coordinates of the top-left corner of the sprite.
   */
  void setCoord(Coord coord) { this->m_coord = coord; }

  /**
   * @brief Function to get a textual representation of the sprite's properties.
   *
   * @return A string representing the properties of the sprite.
   */
  std::string toString() const {
    std::string s = "";
    s += "x : " + std::to_string(m_coord.getX());
    s += " y : " + std::to_string(m_coord.getY());
    s += " width : " + std::to_string(m_width);
    s += " height : " + std::to_string(m_height);
    return s;
  }
};

#endif /* SPRITES_HPP */