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
  /* constructor */
  Map(string path);
  Map(int height, int width);
  /* destructor */
  void clear();
  /* init function */
  void initMap(string nomFichier);
  void initLength(string nomFichier);

  /* getters */
  vector<vector<Tile>> getMap() { return m_map; }
  Coord get_cam() { return m_cam; }
  int get_height() { return m_height; }
  int get_width() { return m_width - 1; }
  Tile get_tile(int y_tile, int x_tile) { return m_map[y_tile][x_tile]; }
  Tile *find_tile(int x, int y);
  int get_cam_width() { return m_cam_width; }
  int get_cam_height() { return m_cam_height; }
  bool isBreaking(int mouseX, int mouseY);
  Clock getBreakingClock(int mouseX, int mouseY);
  /* setters */
  void resetBreakingClock(int mouseX, int mouseY);
  void setIsBreaking(bool isBreaking, int mouseX, int mouseY);

  /* other*/
  void save(string path);
  void collide(Character *perso, int camX, int camY);
  void collide(Character *perso);
  Tile chooseTile(string c, int x, int y);
  void add_tile(Block block, int mouseX, int mouseY);
  void supr_tile(int x, int y);
  void update(int camX, int camY);
  string toString();

private:
  vector<vector<Tile>> m_map;
  Coord m_cam;      /* position x,y of the tile in top left */
  int m_cam_width;  /* amout of tile in the cam in x*/
  int m_cam_height; /* amout of tile in the cam in y*/
  int m_width;
  int m_height;
};

#endif /* CARTE_HPP */
