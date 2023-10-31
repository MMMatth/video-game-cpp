#ifndef CARTE_HPP
#define CARTE_HPP

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

class Carte {

public:
  Carte();

  void initCarte(const char *nomFichier);

  // getters
  vector<Tile> getCarte();
  int getSize();
  Tile getTile(int i);
  void collide(Personnage *perso);
  Tile chooseTile(char c, int x, int y);

  void clean();

  string toString();

private:
  vector<Tile> carte;
};

#endif // CARTE_HPP