#ifndef CARTE_HPP
#define CARTE_HPP

/*!
 * \file Carte.hpp
 * \brief Définition de la classe Carte.
 * \author Mathieu Gaudel and Papa El Hadji G Cissé
 * \version 2023
 */

#include "block.hpp"
#include "const.hpp"
#include "personnage.hpp"
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*!
 * \class Carte
 * \brief Classe représentant une carte du jeu.
 */
class Carte {
public:
  /*!
   * Constructeur par défaut de la classe Carte.
   */
  Carte();

  /*!
   * Initialise la carte à partir d'un fichier.
   * @param nomFichier Le nom du fichier contenant la définition de la carte.
   */
  void initCarte(const char *nomFichier);

  // Getters
  /*!
   * Récupère la carte sous forme d'un vecteur de blocks.
   * @return vector<Block> Un vecteur contenant les blocks de la carte.
   */
  vector<Tile> getCarte();

  /*!
   * Récupère le nombre de blocks dans la carte.
   * @return int Le nombre de blocks dans la carte.
   */
  int getSize();

  /*!
   * Récupère un bloc spécifique dans la carte.
   * @param i L'indice du block dans la carte.
   * @return Block Le bloc à l'indice spécifié.
   */
  Tile getTile(int i);

  /*!
   * Gère les collisions entre un personnage et les blocks de la carte.
   * @param perso Un pointeur vers l'objet Personnage avec lequel vérifier les
   * collisions.
   */
  void collide(Personnage *perso);

  /*!
   * Sélectionne un block en fonction d'un caractère du fichier de définition de
   * la carte.
   * @param c Le caractère spécifiant le type de block.
   * @param x La position horizontale du block.
   * @param y La position verticale du block.
   * @return Block Le block correspondant au caractère spécifié.
   */
  Tile chooseTile(char c, int x, int y);

  /*!
   * Nettoie la carte en libérant la mémoire allouée.
   */
  void clean();

  /*!
   * Renvoie une représentation textuelle de la carte.
   * @return string Une chaîne de caractères représentant la carte.
   */
  string toString();

private:
  vector<Tile> carte;
};

#endif /* CARTE_HPP */
