#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "const.hpp"
#include "coord.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;

using namespace std;

class Character {
public:
  /* constructor */
  Character(int x, int y, int taille);
  /* destructor */
  // ~Personnage();

  void initSprites(Texture &spritesheet);

  void update();
  /* getters */
  unordered_map<string, Sprite> getSprites() { return sprites; }
  map<string, bool> getDirection() { return direction; }
  map<string, bool> getCollision() { return collision; }
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



private:
  Coord coord;
  bool isFalling;
  map<string, bool> direction;
  map<string, bool> collision;
  int timeJump;
  int jumpHeight;
  int largeur;
  int hauteur;
  int tempSaut;
  int vitesse;

  unordered_map<string, Sprite> sprites;
  Texture texture;
};

#endif /* CHARACTER_HPP */
