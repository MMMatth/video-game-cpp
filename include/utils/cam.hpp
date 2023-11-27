#ifndef CAM_HPP
#define CAM_HPP

#include "const.hpp"
#include "coord.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

/**
 * @brief La classe Cam représente une caméra dans le monde du jeu.
 *
 * La caméra est utilisée pour définir la vue du joueur dans le jeu en définissant
 * une position et des dimensions. Elle peut être mise à jour pour suivre un personnage
 * ou pour s'adapter à une certaine zone de la carte.
 */
class Cam {
private:
  bool m_save;  /**< Condition pour la sauvegarde */
  Coord m_pos;  /**< Position de la caméra */
  int m_width;  /**< Largeur de la caméra */
  int m_height; /**< Hauteur de la caméra */

public:
  /**
   * @brief Constructeur par défaut de la classe Cam.
   *
   * Initialise la caméra avec une position (0,0) et des dimensions par défaut.
   */
  Cam();

  /**
   * @brief Constructeur de la classe Cam avec des paramètres spécifiés.
   *
   * Initialise la caméra avec une position (x, y) et des dimensions par défaut.
   *
   * @param x Position horizontale de la caméra.
   * @param y Position verticale de la caméra.
   */
  Cam(int x, int y);

  /**
   * @brief Constructeur de la classe Cam à partir d'un fichier CSV.
   *
   * Initialise la caméra à partir d'un fichier CSV qui contient des informations
   * sur la position et les dimensions de la caméra.
   *
   * @param csvPath Chemin du fichier CSV.
   */
  Cam(string csvPath);

  /**
   * @brief Charge les données de la caméra à partir d'un fichier CSV.
   *
   * @param csvPath Chemin du fichier CSV.
   * @return true si le chargement est réussi, false sinon.
   */
  bool loadFromCSV(string csvPath);

  /**
   * @brief Met à jour la position de la caméra en fonction de la position d'un personnage
   * et des dimensions de la carte.
   *
   * @param charX Position horizontale du personnage.
   * @param charY Position verticale du personnage.
   * @param charW Largeur du personnage.
   * @param charH Hauteur du personnage.
   * @param mapWidth Largeur de la carte.
   * @param mapHeight Hauteur de la carte.
   * @param window Fenêtre SFML utilisée pour déterminer les dimensions de la vue.
   */
  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);

  /**
   * @brief Obtient la position horizontale de la caméra.
   *
   * @return Position horizontale de la caméra.
   */
  int getX() { return m_pos.getX(); }

  /**
   * @brief Obtient la position verticale de la caméra.
   *
   * @return Position verticale de la caméra.
   */
  int getY() { return m_pos.getY(); }

  /**
   * @brief Obtient la position de la caméra sous forme de coordonnées.
   *
   * @return Coord représentant la position de la caméra.
   */
  Coord getPos() { return m_pos; }

  /**
   * @brief Obtient la largeur de la caméra.
   *
   * @return Largeur de la caméra.
   */
  int getWidth() { return m_width; }

  /**
   * @brief Obtient la hauteur de la caméra.
   *
   * @return Hauteur de la caméra.
   */
  int getHeight() { return m_height; }

  /**
   * @brief Définit la position horizontale de la caméra.
   *
   * @param x Nouvelle position horizontale de la caméra.
   */
  void setX(int x) { m_pos.setX(x); }

  /**
   * @brief Définit la position verticale de la caméra.
   *
   * @param y Nouvelle position verticale de la caméra.
   */
  void setY(int y) { m_pos.setY(y); }

  /**
   * @brief Définit la position de la caméra en utilisant des coordonnées.
   *
   * @param pos Nouvelle position de la caméra.
   */
  void setPos(Coord pos) { m_pos = pos; }

  /**
   * @brief Réinitialise la position de la caméra.
   *
   * @param x Nouvelle position horizontale.
   * @param y Nouvelle position verticale.
   */
  void reset(int x, int y);

  /**
   * @brief Sauvegarde les données de la caméra dans un fichier CSV.
   *
   * @param csvPath Chemin du fichier CSV.
   */
  void save(string csvPath);
};

#endif // CAM_HPP