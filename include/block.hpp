#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "const.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Block {
public:
  // enum {
  //   grass = Block(0, 0, 1, "grass", 0, 0, false).getNumber(),
  //   dirt,
  //   stone,
  //   wood,
  //   plank,
  //   coal,
  //   coblestone,
  //   brick,
  //   door,
  //   librairie,
  //   bed,
  //   redFlower,
  //   yellowFlower,
  //   torch
  // };
  // Constructeur par défaut
  Block();

  // Constructeur avec initialisation des attributs
  Block(int spriteSheetX, int spriteSheetY, int number, std::string name,
        int blockX, int blockY, bool isSolid);

  // Getters
  Point getSpriteSheet() const;
  int getNumber() const;
  std::string getName() const;
  bool isSolid() const;

  // Setters
  void setSpriteSheetX(int spriteSheetX);
  void setSpriteSheetY(int spriteSheetY);
  void setNumber(int number);
  void setName(std::string name);
  void setSolid(bool isSolid);

  // to string
  std::string toString() const;

private:
  Point m_spriteSheet;
  int m_number;
  std::string m_name;
  int m_id;
  bool m_isSolid;
};

#endif