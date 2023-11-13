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
  Map(string path);
  Map(int height, int width);
  void initMap(string nomFichier);

  /* getters */
  vector<vector<Tile>> getMap() { return m_map; }
  int get_height() { return m_map.size(); }
  int get_width() { return m_map[0].size(); }
  Tile get_tile(int x, int y) { return m_map[x][y]; }
  Coord get_cam() { return m_cam; }
  int get_cam_width() { return m_cam_width; }
  int get_cam_height() { return m_cam_height; }
  /* setters */

  /* other*/
  void save(string path);
  void collide(Character *perso, int camX, int camY);
  Tile chooseTile(string c, int x, int y);
  void clean();
  void add_tile(Block block, int mouseX, int mouseY);
  void supr_tile(int x, int y);
  void update(int camX, int camY);
  string toString();

private:
  vector<vector<Tile>> m_map;
  Coord m_cam;      /* position x,y of the tile in top left */
  int m_cam_width;  /* amout of tile in the cam in x*/
  int m_cam_height; /* amout of tile in the cam in y*/
};

#endif /* CARTE_HPP */
