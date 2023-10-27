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
  /*!
   * Constructeur de la classe Point.
   * \param x La coordonnée horizontale du point.
   * \param y La coordonnée verticale du point.
   */
  Point(int x, int y);

  /*!
   * Récupère la coordonnée horizontale du point.
   * \return int La coordonnée horizontale du point.
   */
  int getX() const;

  /*!
   * Récupère la coordonnée verticale du point.
   * \return int La coordonnée verticale du point.
   */
  int getY() const;

  /*!
   * Définit la coordonnée horizontale du point.
   * \param x La nouvelle coordonnée horizontale du point.
   */
  void setX(int x);

  /*!
   * Définit la coordonnée verticale du point.
   * \param y La nouvelle coordonnée verticale du point.
   */
  void setY(int y);

  
  // /*!
  //  * Renvoie une représentation textuelle du point.
  //  * \return std::string Une chaîne de caractères représentant le point.
  //  */
  // std::string toString();

private:
  int m_x; /*!< Coordonnée horizontale du point. */
  int m_y; /*!< Coordonnée verticale du point. */
};

#endif /* POINT_HPP */
