#ifndef CARTE_HPP
#define CARTE_HPP

#include "block.hpp"
#include "character.hpp"
#include "const.hpp"
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Map {
public:
  Map();

  void initMap(const char *nomFichier);

  vector<Tile> getMap();

  int getSize();

  Tile getTile(int i);

  void collide(Character *perso);

  Tile chooseTile(string c, int x, int y);

  void clean();

  string toString();

private:
  vector<Tile> m_map;
};

#endif /* CARTE_HPP */
