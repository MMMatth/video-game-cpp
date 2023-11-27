#ifndef COORD_HPP
#define COORD_HPP

#include <string>

/**
 * @brief La classe Coord représente des coordonnées (x, y).
 *
 * Cette classe est utilisée pour stocker et manipuler des coordonnées
 * dans un espace bidimensionnel.
 */
class Coord {
public:
  /**
   * @brief Constructeur par défaut de la classe Coord.
   *
   * Initialise les coordonnées à (0, 0).
   */
  Coord() : m_x(0), m_y(0) {}

  /**
   * @brief Constructeur de la classe Coord avec des coordonnées spécifiées.
   *
   * @param x Valeur de la coordonnée horizontale (x).
   * @param y Valeur de la coordonnée verticale (y).
   */
  Coord(int x, int y) : m_x(x), m_y(y) {}

  /**
   * @brief Destructeur de la classe Coord.
   */
  ~Coord() {}

  /**
   * @brief Obtient la valeur de la coordonnée horizontale (x).
   *
   * @return Valeur de la coordonnée horizontale (x).
   */
  int getX() const { return m_x; }

  /**
   * @brief Obtient la valeur de la coordonnée verticale (y).
   *
   * @return Valeur de la coordonnée verticale (y).
   */
  int getY() const { return m_y; }

  /**
   * @brief Définit la valeur de la coordonnée horizontale (x).
   *
   * @param x Nouvelle valeur de la coordonnée horizontale (x).
   */
  void setX(int x) { m_x = x; }

  /**
   * @brief Définit la valeur de la coordonnée verticale (y).
   *
   * @param y Nouvelle valeur de la coordonnée verticale (y).
   */
  void setY(int y) { m_y = y; }

  /**
   * @brief Définit les coordonnées avec de nouvelles valeurs pour (x, y).
   *
   * @param x Nouvelle valeur de la coordonnée horizontale (x).
   * @param y Nouvelle valeur de la coordonnée verticale (y).
   */
  void setCoord(int x, int y) {
    m_x = x;
    m_y = y;
  }

  /**
   * @brief Vérifie si les coordonnées sont égales à d'autres coordonnées.
   *
   * @param other Autres coordonnées à comparer.
   * @return true si les coordonnées sont égales, false sinon.
   */
  bool isEqual(Coord other) {
    return (m_x == other.getX() && m_y == other.getY());
  }

  /**
   * @brief Convertit les coordonnées en une chaîne de caractères.
   *
   * @return Chaîne de caractères représentant les coordonnées (x, y).
   */
  std::string toString() {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
  };

private:
  int m_x; /**< Valeur de la coordonnée horizontale (x). */
  int m_y; /**< Valeur de la coordonnée verticale (y). */
};

#endif // COORD_HPP