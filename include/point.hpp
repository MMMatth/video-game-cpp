/*!
 * \file point.hpp
 * \brief Définition de la classe Point.
 * \author Matthieu Gaudel and Papa El Hadji G Cissé
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <string>

/*!
 * \class Point
 * \brief class représentant un point dans un espace 2D.
 */
class Point {
public:
  Point() : m_x(0), m_y(0) {}
  Point(int x, int y) : m_x(x), m_y(y) {}
  int getX() const { return m_x; }
  int getY() const { return m_y; }
  void setX(int x) { m_x = x; }
  void setY(int y) { m_y = y; }
  bool isEqual(Point other) {
    return (m_x == other.getX() && m_y == other.getY());
  }
  std::string toString() {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
  };

private:
  int m_x; /*!< Coordonnée horizontale du point. */
  int m_y; /*!< Coordonnée verticale du point. */
};

#endif