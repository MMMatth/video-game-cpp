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
  // Constructeur par défaut
  Block();

  // Constructeur avec initialisation des attributs
  Block(int spriteSheetX, int spriteSheetY, int id, std::string name,
        bool isSolid);

  // Getters
  Point getSpriteSheet() const;
  int getId() const;
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
  int m_id;
  std::string m_name;
  bool m_isSolid;
};

enum BlockType {
  AIR,
  GRASS,
  DIRT,
  STONE
  // WOOD,
  // PLANK,
  // COAL,
  // COBBLESTONE,
  // BRICK,
  // DOOR,
  // LIBRARY,
  // BED,
  // RED_FLOWER,
  // YELLOW_FLOWER,
  // TORCH,
  // TOTAL_BLOCKS
};

static std::map<BlockType, Block> blockMap = {
    {AIR, Block(0, 0, 0, "air", false)},
    {GRASS, Block(0, 0, 1, "grass", true)},
    {DIRT, Block(32, 0, 2, "dirt", true)},
    {STONE, Block(64, 0, 3, "stone", true)}
    // ... et ainsi de suite pour les autres types de blocs
};
#endif