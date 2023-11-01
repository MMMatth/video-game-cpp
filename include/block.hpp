/*!
 * \file block.hpp
 * \brief Définition de la classe Block.
 * \author Matthieu Gaudel and Papa El Hadji G Cissé
 * \version 2023
 */

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "const.hpp"
#include "item.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

/*!
 * \namespace std
 * Espace de nommage standard de C++.
 */
using namespace std;

/*!
 * \class Block
 * \brief Classe représentant un bloc du jeu.
 */
class Block : public Item {
public:
  /*!
   * Constructeur par défaut de la classe Block.
   */
  Block();

  /*!
   * Constructeur avec initialisation des attributs.
   * \param spriteSheetX La position X de la sprite.
   * \param spriteSheetY La position Y de la sprite.
   * \param id Le numéro du block.
   * \param name Le nom du block.a position Y du block.
   * \param isSolid Un booléen indiquant si le block est solide.
   */
  Block(int spriteSheetX, int spriteSheetY, int id, std::string name,
        bool isSolid, bool is_stackable = true);

  // Getters

  Point getSpriteSheet() const;
  bool isSolid() const;

  // Setters

  /*!
   * Une fonction qui définit la position X de la sprite dans la feuille de
   * sprite. \param spriteSheetX La nouvelle position X de la sprite.
   */
  void setSpriteSheetX(int spriteSheetX);

  /*!
   * Une fonction qui définit la position Y de la sprite dans la feuille de
   * sprite. \param spriteSheetY La nouvelle position Y de la sprite.
   */
  void setSpriteSheetY(int spriteSheetY);

  /*!
   * Une fonction qui définit si le bloc est solide ou non.
   * \param isSolid Un booléen indiquant si le bloc est solide (true) ou non
   * (false).
   */
  void setSolid(bool isSolid);

  // To string

  /*!
   * Une fonction qui renvoie une représentation sous forme de chaîne de
   * caractères de l'objet Block. \return std::string Une chaîne de caractères
   * représentant l'objet Block.
   */
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
    {DIRT, Block(16, 0, 2, "dirt", true)},
    {STONE, Block(32, 0, 3, "stone", true)}
    // ... et ainsi de suite pour les autres types de blocs
};
#endif