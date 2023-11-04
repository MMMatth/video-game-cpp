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

using namespace sf;

using namespace std;

class Personnage {
public:
  /* constructor */
  Personnage(int x, int y, int taille);
  Personnage(float x, float y, Texture &texture);
  /* destructor */
  // ~Personnage();

  void initSprites(Texture &spritesheet);

  void update();
  /* getters */
  int getHauteur() { return hauteur; }
  int getLargeur() { return largeur; }
  int getX() { return coord.getX(); }
  int getY() { return coord.getY(); }
  int getTimeJump() { return timeJump; }
  int getJumpHeight() { return jumpHeight; }
  int getVitesse() { return vitesse; }
  bool isInFall() { return direction["isFalling"]; }
  bool isInJump() { return direction["isGoingUp"]; }
  /* setters */
  void setX(int x) { coord.setX(x); }
  void setY(int y) { coord.setY(y); }
  void setFalling(bool falling) { this->direction["isFalling"] = falling; }
  void setJumping(bool jumping) { this->direction["isJumping"] = jumping; }
  void setGoingUp(bool inUp) { this->direction["isGoingUp"] = inUp; }
  void setTimeJump(int time) { this->timeJump = time; }
  void setGoingRight(bool inRight) {
    this->direction["isGoingRight"] = inRight;
  }
  void setGoingLeft(bool inLeft) { this->direction["isGoingLeft"] = inLeft; }
  void setCollision(string key, bool value) { this->collision[key] = value; }
  void setCollisionFalseExcept(string key);
  /* other */
  void deplacerX(int x);
  void deplacerY(int y);

  string toString();

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
