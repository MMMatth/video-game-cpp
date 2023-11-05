#include "../include/character.hpp"
#include "../include/draw.hpp"

using namespace std;

Character::Character(int x, int y, int taille) : coord(x, y) {
  this->largeur = taille;
  this->hauteur = taille;

  this->direction = {{"isJumping", false},
                     {"isGoingUp", false},
                     {"isFalling", true},
                     {"isGoingRight", false},
                     {"isGoingLeft", false}};

  this->collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  this->jumpHeight = 15;
  this->timeJump = 0;
  this->vitesse = 3;
}

void Character::initSprites(Texture &spritesheet) {

  vector<string> spriteNames = {"stop", "jump", "fall"};
  for (string &name : spriteNames) {
    sprites[name].setTexture(spritesheet);
    if (name == "stop") {
      sprites[name].setTextureRect(IntRect(128, 1152, 64, 64));
    } else if (name == "jump") {
      sprites[name].setTextureRect(IntRect(256, 128, 64, 64));
    } else if (name == "fall") {
      sprites[name].setTextureRect(IntRect(320, 128, 64, 64));
    }
    sprites[name].setPosition(coord.getX(), coord.getY());
  }

  vector<string> moveNames = {"moveLeft", "moveRight"};
  for (string &moveName : moveNames) {
    int x = 0;
    if (moveName == "moveLeft") {
      for (int i = 1; i <= 9; i++) {
        string spriteName = moveName + to_string(i);
        sprites[spriteName].setTexture(spritesheet);
        sprites[spriteName].setTextureRect(IntRect(x, 576, 64, 64));
        sprites[spriteName].setPosition(coord.getX(), coord.getY());
        x += 64;
      }
    } else {
      for (int i = 1; i <= 9; i++) {
        string spriteName = moveName + to_string(i);
        sprites[spriteName].setTexture(spritesheet);
        sprites[spriteName].setTextureRect(IntRect(x, 704, 64, 64));
        sprites[spriteName].setPosition(coord.getX(), coord.getY());
        x += 64;
      }
    }
  }
}

Character::Character(float x, float y, Texture &texture) : coord(x, y) {
  this->largeur = 64;
  this->hauteur = 64;
  this->direction = {{"isJumping", false},
                     {"isGoingUp", false},
                     {"isFalling", true},
                     {"isGoingRight", false},
                     {"isGoingLeft", false}};

  this->collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  this->jumpHeight = 15;
  this->timeJump = 0;
  this->vitesse = 3;

  initSprites(texture);
}       

void Character::draw(RenderWindow &window) {
  if (direction["isGoingLeft"]) {

    int frame = (clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) %
                NUM_FRAMES;
    window.draw(sprites["moveLeft" + to_string(frame + 1)]);

  } else if (direction["isGoingRight"]) {

    int frame = (clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) %
                NUM_FRAMES;
    window.draw(sprites["moveRight" + to_string(frame + 1)]);

  } else if (direction["isJumping"] && !collision["right"]) {

    window.draw(sprites["jump"]);

  } else if (direction["isFalling"] && !collision["down"]) {
    window.draw(sprites["fall"]);
  } else {
    window.draw(sprites["stop"]);
  }
}

void Character::update() {
  // update position of the sprite
  vector<string> spriteNames = {"stop", "jump", "fall"};
  for (string &name : spriteNames) {
    sprites[name].setPosition(coord.getX(), coord.getY());
  }

  vector<string> moveNames = {"moveLeft", "moveRight"};
  for (string &moveName : moveNames) {
    int x = 0;
    if (moveName == "moveLeft") {
      for (int i = 1; i <= 9; i++) {
        string spriteName = moveName + to_string(i);
        sprites[spriteName].setPosition(coord.getX(), coord.getY());
        x += 64;
      }
    } else {
      for (int i = 1; i <= 9; i++) {
        string spriteName = moveName + to_string(i);
        sprites[spriteName].setPosition(coord.getX(), coord.getY());
        x += 64;
      }
    }
  }

  if (direction["isJumping"] && collision["down"]) {
    this->direction["isGoingUp"] = true;
    this->timeJump = 0;
    this->collision["down"] = false;
  }
  if (!direction["isJumping"]) {
    this->direction["isGoingUp"] = false;
    this->direction["isFalling"] = true;
  }
  if (direction["isGoingUp"] && !collision["up"]) {
    this->timeJump++;
    if (timeJump < jumpHeight) {
      this->deplacerY(-vitesse);
    } else {
      this->direction["isGoingUp"] = false;
      this->direction["isFalling"] = true;
    }
  }
  if (direction["isFalling"] && !collision["down"] && !direction["isGoingUp"]) {
    // this->setCollisionFalseExcept("down");
    this->deplacerY(vitesse);
  }

  if (direction["isGoingRight"] && !collision["right"]) {

    this->setCollisionFalseExcept("right");
    this->deplacerX(vitesse);
  }

  if (direction["isGoingLeft"] && !collision["left"]) {
    this->setCollisionFalseExcept("left");

    this->deplacerX(-vitesse);
  }

  if (direction["isGoingUp"] && !collision["up"]) {
    this->setCollisionFalseExcept("up");

    this->deplacerY(-vitesse);
  }
  if (collision["up"] && !collision["down"] && collision["right"] &&
      collision["left"]) {

    this->setCollisionFalseExcept("down");

    this->deplacerY(vitesse);
  }
}

void Character::setCollisionFalseExcept(string key) {
  for (auto &x : this->collision) {
    if (x.first != key) {
      x.second = false;
    }
  }
}

// other methods
void Character::deplacerX(int x) { this->coord.setX(this->coord.getX() + x); }

void Character::deplacerY(int y) { this->coord.setY(this->coord.getY() + y); }