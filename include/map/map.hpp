#ifndef MAP_HPP
#define MAP_HPP

#include "../entity/character.hpp"
#include "../entity/entity.hpp"
#include "../item/block.hpp"
#include "../utils/const.hpp"
#include "mapGenerator.hpp"
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
  bool loadFromCSV(string pathFile);
  bool initLegthFromCSV(string pathFile);

  /* getters */
  vector<vector<Tile>> getMap() const { return m_map; }
  Coord get_working_area() const { return m_workingAreaCoord; }
  int get_height() const { return m_height - 1; }
  int get_width() const { return m_width - 1; }
  Tile get_tile(int y_tile, int x_tile) const { return m_map[y_tile][x_tile]; }
  Tile *find_tile(int x, int y);
  int get_cam_width() const { return m_workingAreaWidth; }
  int get_cam_height() const { return m_workingAreaHeight; }
  bool isBreaking(int mouseX, int mouseY);
  Clock getBreakingClock(int mouseX, int mouseY);
  /* setters */
  void resetBreakingClock(int mouseX, int mouseY);
  void setIsBreaking(bool isBreaking, int mouseX, int mouseY);

  /* other*/
  void save(string path);
  void collide(Entity *entity, int camX, int camY);
  void collide(Entity *entity);

  Tile chooseTile(string c, int x, int y, bool isBackground);
  void add_tile(Block block, int mouseX, int mouseY);
  void supr_tile(int x, int y);
  void update(int camX, int camY);
  string toString();

private:
  bool m_save;                /** condition for the save*/
  vector<vector<Tile>> m_map; /**  2D vector contain tile */
  Coord m_workingAreaCoord;   /** coord x,y of the tile in top left */
  int m_workingAreaWidth;     /** amout of tile in the cam in x*/
  int m_workingAreaHeight;    /** amout of tile in the cam in y*/
  int m_width;                /** map width in block */
  int m_height;               /** map height in block */
};

#endif /* CARTE_HPP */
