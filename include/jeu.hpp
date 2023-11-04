/*!
 * \file jeu.hpp
 * \brief Définition de la classe Jeu.
 * \author Matthieu Gaudel and Papa El Hadji G Cissé
 */
#ifndef JEU_HPP
#define JEU_HPP

#include "cartes.hpp"
#include "const.hpp"
#include "draw.hpp"
#include "inventory.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include "tool.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <unordered_map>

/*!
 * \namespace sf
 * \brief Espace de noms pour la bibliothèque SFML (Simple and Fast Multimedia
 * Library).
 */
using namespace sf;

/*!
 * \namespace stdz
 * \brief Espace de noms pour les éléments standard de la bibliothèque C++.
 */
using namespace std;

/*!
 * \class Jeu
 * \brief Classe représentant le jeu.
 */
class Jeu {
private:
  Carte carte;         /*!< Objet représentant la carte du jeu. */
  Personnage perso;    /*!< Objet représentant le personnage du joueur. */
  RenderWindow window; /*!< Fenêtre de rendu du jeu. */
  View miniWindow;     /*!< Vue pour la mini-carte. */
  bool collideDown;    /*!< Indique s'il y a une collision vers le bas. */
  bool collideSide;    /*!< Indique s'il y a une collision sur les côtés. */
  Point posCam;        /*!< Position de la caméra. */
  unordered_map<string, Sprite> sprites; /*!< Dictionnaire de sprites. */
  Inventory inv;
  Point mousePosInCam;
  Point mousePosInWorld;

public:
  Jeu(Texture &texture);

  void run();

  void update();

  void updateCam();

  void updateCollide();

  void updateMousePos();

  void render();

  void clean();

  void event();

  void quit();

  void save();

  bool collisionAvecCarte(int x, int y);
};

#endif /* JEU_HPP */
