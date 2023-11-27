#ifndef SPRITES_HPP
#define SPRITES_HPP

#include "const.hpp"
#include "coord.hpp"

/**
 * @brief Classe représentant les coordonnées et les dimensions d'un sprite.
 */
class Sprites {
private:
  Coord m_coord; ///< Les coordonnées du coin supérieur gauche du sprite.
  int m_width;   ///< La largeur du sprite.
  int m_height;  ///< La hauteur du sprite.

public:
  /**
   * @brief Constructeur avec paramètres.
   *
   * @param coord Les coordonnées du coin supérieur gauche du sprite.
   * @param width La largeur du sprite.
   * @param height La hauteur du sprite.
   */
  Sprites(Coord coord, int width, int height)
      : m_coord(coord), m_width(width), m_height(height) {}

  /**
   * @brief Constructeur avec paramètres.
   *
   * @param x La coordonnée horizontale du coin supérieur gauche du sprite.
   * @param y La coordonnée verticale du coin supérieur gauche du sprite.
   * @param width La largeur du sprite.
   * @param height La hauteur du sprite.
   */
  Sprites(int x, int y, int width, int height)
      : m_coord(x, y), m_width(width), m_height(height) {}

  /**
   * @brief Constructeur par défaut.
   */
  Sprites() : m_coord(0, 0), m_width(0), m_height(0){};

  /**
   * @brief Getter pour la coordonnée horizontale du coin supérieur gauche du sprite.
   *
   * @return La coordonnée horizontale du coin supérieur gauche du sprite.
   */
  int getX() const { return m_coord.getX(); }

  /**
   * @brief Getter pour la coordonnée verticale du coin supérieur gauche du sprite.
   *
   * @return La coordonnée verticale du coin supérieur gauche du sprite.
   */
  int getY() const { return m_coord.getY(); }

  /**
   * @brief Getter pour la largeur du sprite.
   *
   * @return La largeur du sprite.
   */
  int getWidth() const { return m_width; }

  /**
   * @brief Getter pour la hauteur du sprite.
   *
   * @return La hauteur du sprite.
   */
  int getHeight() const { return m_height; }

  /**
   * @brief Getter pour les coordonnées du coin supérieur gauche du sprite.
   *
   * @return Les coordonnées du coin supérieur gauche du sprite.
   */
  Coord getCoord() const { return m_coord; }

  /**
   * @brief Setter pour la coordonnée horizontale du coin supérieur gauche du sprite.
   *
   * @param x La nouvelle coordonnée horizontale du coin supérieur gauche du sprite.
   */
  void setX(int x) { m_coord.setX(x); }

  /**
   * @brief Setter pour la coordonnée verticale du coin supérieur gauche du sprite.
   *
   * @param y La nouvelle coordonnée verticale du coin supérieur gauche du sprite.
   */
  void setY(int y) { m_coord.setY(y); }

  /**
   * @brief Setter pour la largeur du sprite.
   *
   * @param width La nouvelle largeur du sprite.
   */
  void setWidth(int width) { this->m_width = width; }

  /**
   * @brief Setter pour la hauteur du sprite.
   *
   * @param height La nouvelle hauteur du sprite.
   */
  void setHeight(int height) { this->m_height = height; }

  /**
   * @brief Setter pour les coordonnées du coin supérieur gauche du sprite.
   *
   * @param coord Les nouvelles coordonnées du coin supérieur gauche du sprite.
   */
  void setCoord(Coord coord) { this->m_coord = coord; }

  /**
   * @brief Fonction pour obtenir une représentation textuelle des propriétés du sprite.
   *
   * @return Une chaîne de caractères représentant les propriétés du sprite.
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