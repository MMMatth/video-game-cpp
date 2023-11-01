#ifndef POINT_HPP
#define POINT_HPP

/*!
 * \file point.hpp
 * \brief Définition de la classe Point.
 * \author Mathieu Gaudel and Papa El Hadji G Cissé
 * \version 2023
 */

/*!
 * \class Point
 * \brief Classe représentant un point dans un espace 2D.
 */
class Point {
public:
  Point(int x, int y) : m_x(x), m_y(y) {}
  int getX() const { return m_x; }
  int getY() const { return m_y; }
  void setX(int x) { m_x = x; }
  void setY(int y) { m_y = y; }
  // std::string toString();

private:
  int m_x; /*!< Coordonnée horizontale du point. */
  int m_y; /*!< Coordonnée verticale du point. */
};

#endif