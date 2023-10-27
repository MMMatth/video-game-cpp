
#ifndef BLOCK_HPP
#define BLOCK_HPP
/*!
* \file block.hpp
* \brief les prototypes de la classe block.
* \author Mathieu Gaudel and Papa El Hadji G Cissé
* \version 2023
*/
#include "const.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

 /*! \class block
   * \brief classe block
   */
class Block {
public:
  /*!
  * Constructeur par défaut de la classe Block
  */
  Block();
  /*!
   * Constructeur avec initialisation des attributs.
   * \param spriteSheetX La position X de la sprite 
   * \param spriteSheetY La position Y de la sprite 
   * \param number Le numéro du block.
   * \param name Le nom du block.
   * \param blockX La position X du block.
   * \param blockY La position Y du block.
   * \param isSolid Un booléen indiquant si le block est solide.
  */ 
  Block(int spriteSheetX, int spriteSheetY, int number, std::string name,
        int blockX, int blockY, bool isSolid);

  /*!
   * Une fonction qui vérifie si un objet est actuellement visible dans la caméra du jeu.
   * \param posCamX La position horizontale de la caméra.
   * \param posCamY La position verticale de la caméra.
   * \param largeur La largeur de la zone visible à l'écran.
   * \param hauteur La hauteur de la zone visible à l'écran.
   * \return True si l'objet est actuellement visible dans la caméra, sinon False.
  */
  bool estDansCam(int posCamX, int posCamY, int largeur, int hauteur);

  /*!
    * Une fonction qui vérifie si le personnage est en collision avec un block.
    * \param perso Un pointeur vers l'objet Personnage avec lequel vérifier la collision.
  */
  void collide(Personnage *perso);

  //getters

  /*!
    * Une fonction qui retourne les coordonnées de la sprite.
    * \return Point Un objet représentant les coordonnées de la sprite.
 */
  Point getSpriteSheet() const;

  /*!
    * Une fonction qui retourne le numéro du block.
    * \return int Le numéro du block.
 */
  int getNumber() const;

  /*!
    * Une fonction qui retourne le nom du block.
    * \return String Le nom du block.
  */
  std::string getName() const;

  /*!
    * Une fonction qui retourne l'abscisse du block.
    * \return int l'abscisse du block.
  */
  int getX() const;

  /*!
    * Une fonction qui retourne l'ordonnée du block.
    * \return int l'ordonnée du block.
  */
  int getY() const;

  /*!
    * Une fonction qui verifie si le block est solide ou pas.
    * \return Un booléen indiquant si le block est solide.
  */
  bool isSolid() const;

  // Setters

  /*!
    * Une fonction qui définit la position X de la sprite dans la feuille de sprite.
    * \param spriteSheetX La nouvelle position X de la sprite.
  */
  void setSpriteSheetX(int spriteSheetX);

  /*!
    * Une fonction qui définit la position Y de la sprite dans la feuille de sprite.
    * \param spriteSheetY La nouvelle position Y de la sprite.
  */
  void setSpriteSheetY(int spriteSheetY);

  /*!
   * Une fonction qui définit le numéro du bloc.
   * \param number Le nouveau numéro du bloc.
  */
  void setNumber(int number);

  /*!
   * Une fonction qui définit le nom du bloc.
   * \param name Le nouveau nom du bloc en tant que chaîne de caractères.
  */
  void setName(std::string name);

  /*!
   * Une fonction qui définit la position du bloc.
   * \param position Un objet Point représentant la nouvelle position du bloc.
  */
  void setPosition(Point position);

  /*!
   * Une fonction qui définit si le bloc est solide ou non.
   * \param isSolid Un booléen indiquant si le bloc est solide (true) ou non (false).
  */
  void setSolid(bool isSolid);


  // to string

  /*!
    * Une fonction qui renvoie une représentation sous forme de chaîne de caractères de l'objet Block.
     * \return std::string Une chaîne de caractères représentant l'objet Block.
 */
std::string toString() const;

private:
  /*!
    * Coordonnées de la sprite dans la feuille de sprite.
  */
  Point m_spriteSheet;

  /*!
   * Numéro du bloc.
  */
  int m_number;

  /*!
  * Nom du bloc.
  */
  std::string m_name;

  /*!
    * Position du bloc.
  */
  Point m_position;

  /*!
   * Indique si le bloc est solide (true) ou non (false).
  */
  bool m_isSolid;

};

#endif