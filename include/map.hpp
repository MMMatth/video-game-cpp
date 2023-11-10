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
  Map(string filePath = "../assets/map.csv");
  void initMap(string nomFichier);

  /* getters */
  vector<Tile> getMap() { return m_map; }
  int getSize() { return m_map.size(); }
  Tile getTile(int i) { return m_map[i]; }
  /* setters */

  /* other*/
  void save();
  void collide(Character *perso);
  Tile chooseTile(string c, int x, int y);
  void clean();
  void addTile(Block block, int mouseX, int mouseY);
  void suprTile(int x, int y);
  string toString();

private:
  vector<Tile> m_map;
};

#endif /* CARTE_HPP */
