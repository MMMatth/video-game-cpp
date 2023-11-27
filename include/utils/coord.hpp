#ifndef COORD_HPP
#define COORD_HPP

#include <string>

/**
 * @brief The Coord class represents coordinates (x, y).
 *
 * This class is used to store and manipulate coordinates
 * in a two-dimensional space.
 */
class Coord {
public:
  /**
   * @brief Default constructor of the Coord class.
   *
   * Initializes coordinates to (0, 0).
   */
  Coord() : m_x(0), m_y(0) {}

  /**
   * @brief Constructor of the Coord class with specified coordinates.
   *
   * @param x Value of the horizontal coordinate (x).
   * @param y Value of the vertical coordinate (y).
   */
  Coord(int x, int y) : m_x(x), m_y(y) {}

  /**
   * @brief Destructor of the Coord class.
   */
  ~Coord() {}

  /**
   * @brief Gets the value of the horizontal coordinate (x).
   *
   * @return Value of the horizontal coordinate (x).
   */
  int getX() const { return m_x; }

  /**
   * @brief Gets the value of the vertical coordinate (y).
   *
   * @return Value of the vertical coordinate (y).
   */
  int getY() const { return m_y; }

  /**
   * @brief Sets the value of the horizontal coordinate (x).
   *
   * @param x New value of the horizontal coordinate (x).
   */
  void setX(int x) { m_x = x; }

  /**
   * @brief Sets the value of the vertical coordinate (y).
   *
   * @param y New value of the vertical coordinate (y).
   */
  void setY(int y) { m_y = y; }

  /**
   * @brief Sets the coordinates with new values for (x, y).
   *
   * @param x New value of the horizontal coordinate (x).
   * @param y New value of the vertical coordinate (y).
   */
  void setCoord(int x, int y) {
    m_x = x;
    m_y = y;
  }

  /**
   * @brief Checks if the coordinates are equal to other coordinates.
   *
   * @param other Other coordinates to compare.
   * @return true if the coordinates are equal, false otherwise.
   */
  bool isEqual(Coord other) {
    return (m_x == other.getX() && m_y == other.getY());
  }

  /**
   * @brief Converts the coordinates to a string.
   *
   * @return String representing the coordinates (x, y).
   */
  std::string toString() {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
  };

private:
  int m_x; /**< Value of the horizontal coordinate (x). */
  int m_y; /**< Value of the vertical coordinate (y). */
};

#endif // COORD_HPP