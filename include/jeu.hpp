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
 * \namespace std
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
  /*!
   * Constructeur par défaut de la classe Jeu.
   * \param texture La texture à utiliser pour le personnage.
   */
  Jeu(Texture &texture);

  void initSprites();

  /*!
   * Fonction principale pour exécuter le jeu.
   */
  void run();

  /*!
   * Met à jour l'état du jeu.
   */
  void update();

  /*!
   * Met à jour la caméra.
   */
  void updateCam();

  /*!
   * Met à jour les collisions.
   */
  void updateCollide();

  void updateMousePos();
  /*!
   * Affiche les éléments du jeu.
   */
  void render();

  /*!
   * Nettoie les ressources du jeu.
   */
  void clean();

  /*!
   * Gère les événements du jeu.
   */
  void event();

  /*!
   * Vérifie s'il y a une collision avec la carte à une position donnée.
   * \param x La position horizontale.
   * \param y La position verticale.
   * \return true s'il y a une collision, false sinon.
   */
  bool collisionAvecCarte(int x, int y);
};

#endif /* JEU_HPP */
