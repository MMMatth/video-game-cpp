/*!
 * \file personnage.hpp
 * \brief Définition de la classe Personnage.
 * \author Matthieu Gaudel and Papa El Hadji G Cissé
 * \version 2023
 */
#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "const.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

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
 * \class Personnage
 * \brief Classe représentant un personnage.
 */
class Personnage {
public:
  /*!
   * Constructeur de la classe Personnage.
   * \param x La position horizontale initiale.
   * \param y La position verticale initiale.
   * \param taille La taille du personnage.
   */
  Personnage(int x, int y, int taille);

  /*!
   * Constructeur de la classe Personnage avec texture.
   * \param x La position horizontale initiale.
   * \param y La position verticale initiale.
   * \param taille La taille du personnage.
   * \param texture La texture à utiliser pour le personnage.
   */
  Personnage(float x, float y, Texture &texture);

  /*!
   * Initialise les sprites du personnage à partir d'une texture.
   * \param spritesheet La texture contenant les sprites du personnage.
   */
  void initSprites(Texture &spritesheet);

  /*!
   * Met à jour l'état du personnage.
   */
  void update();

  /* getters */
  /*!
   * Récupère la hauteur du personnage.
   * \return int La hauteur du personnage.
   */
  int getHauteur();

  /*!
   * Récupère la largeur du personnage.
   * \return int La largeur du personnage.
   */
  int getLargeur();

  /*!
   * Récupère la position horizontale du personnage.
   * \return int La position horizontale du personnage.
   */
  int getX();

  /*!
   * Récupère la position verticale du personnage.
   * \return int La position verticale du personnage.
   */
  int getY();

  /*!
   * Récupère le temps du saut du personnage.
   * \return int Le temps du saut du personnage.
   */
  int getTimeJump();

  /*!
   * Récupère la hauteur du saut du personnage.
   * \return int La hauteur du saut du personnage.
   */
  int getJumpHeight();

  /*!
   * Récupère la vitesse du personnage.
   * \return int La vitesse du personnage.
   */
  int getVitesse();

  // Setters
  /*!
   * Définit la position horizontale du personnage.
   * \param x La nouvelle position horizontale du personnage.
   */
  void setX(int x);

  /*!
   * Définit la position verticale du personnage.
   * \param y La nouvelle position verticale du personnage.
   */
  void setY(int y);

  /*!
   * Définit si le personnage est en chute (falling).
   * \param falling true si le personnage est en chute, false sinon.
   */
  void setFalling(bool falling);

  /*!
   * Définit si le personnage est en train de sauter (jumping).
   * \param jumping true si le personnage est en train de sauter, false sinon.
   */
  void setJumping(bool jumping);

  /*!
   * Définit si le personnage monte (going up).
   * \param inUp true si le personnage monte, false sinon.
   */
  void setGoingUp(bool inUp);

  /*!
   * Définit le temps du saut du personnage.
   * \param time Le temps du saut du personnage.
   */
  void setTimeJump(int time);

  /*!
   * Définit si le personnage va vers la droite (going right).
   * \param inRight true si le personnage va vers la droite, false sinon.
   */
  void setGoingRight(bool inRight);

  /*!
   * Définit si le personnage va vers la gauche (going left).
   * \param inLeft true si le personnage va vers la gauche, false sinon.
   */
  void setGoingLeft(bool inLeft);

  /*!
   * Définit les collisions du personnage.
   * \param key La clé associée à la collision.
   * \param value true si collision, false sinon.
   */
  void setCollision(string key, bool value);

  /*!
   * Définit toutes les collisions à false sauf une spécifiée par la clé.
   * \param key La clé de la collision à laisser à true.
   */
  void setCollisionFalseExcept(string key);

  /*!
   * Déplace le personnage horizontalement.
   * \param x La distance de déplacement horizontale.
   */
  void deplacerX(int x);

  /*!
   * Déplace le personnage verticalement.
   * \param y La distance de déplacement verticale.
   */
  void deplacerY(int y);

  /*!
   * Renvoie une représentation textuelle du personnage.
   * \return std::string Une chaîne de caractères représentant le personnage.
   */
  std::string toString();

  /*!
   * Vérifie si le personnage est en chute (falling).
   * \return true si le personnage est en chute, false sinon.
   */
  bool isInFall();

  /*!
   * Vérifie si le personnage est en train de sauter (jumping).
   * \return true si le personnage est en train de sauter, false sinon.
   */
  bool isInJump();

  /*!
   * Nettoie les ressources du personnage.
   */
  void clean();

  /*!
   * Dessine le personnage sur la fenêtre spécifiée.
   * \param window La fenêtre sur laquelle dessiner le personnage.
   */
  void draw(RenderWindow &window);

private:
  Point coord;                 /*!< Coordonnées du personnage. */
  bool isFalling;              /*!< Indique si le personnage est en chute. */
  map<string, bool> direction; /*!< Direction du personnage. */
  map<string, bool> collision; /*!< Collisions du personnage. */
  int timeJump;                /*!< Temps du saut du personnage. */
  int jumpHeight;              /*!< Hauteur du saut du personnage. */
  int largeur;                 /*!< Largeur du personnage. */
  int hauteur;                 /*!< Hauteur du personnage. */
  int tempSaut;                /*!< Temps du saut actuel. */
  int vitesse;                 /*!< Vitesse du personnage. */

  unordered_map<string, Sprite>
      sprites; /*! Dictionnaire de sprites du personnage */
  Clock clock; /*! La durée */
};

#endif /* PERSONNAGE_HPP */
