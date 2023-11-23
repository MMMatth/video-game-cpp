#ifndef CREATEMAP_HPP
#define CREATEMAP_HPP

#include "../lib/fastnoise/FastNoiseLite.h"
#include "../utils/const.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct altitude {
  int max;
  int min;  // position la plus basse
  int size; // altitude max - altitude min + 1
};

class Createmap {
private:
  int m_seed;                   // seed for the random
  int m_width;                  // width of the map
  vector<int> m_curve_altitude; // curve of the altitude
  vector<vector<int>> m_map;    // map
  altitude m_altitude;          // altitude
  int m_underground_size;       // size of the underground

public:
  Createmap(int width);

  /**
   * \brief Set the Curve Altitude object
   *The objective of this function is to define the m_curve_altitude array which
   * will give the height of the map based on the x position.
   */
  void setCurveAltitude();

  void addStone();

  void addCave();

  void addGrass();

  void addDirt();

  void addSky();

  void addTree();

  void addLeaf();

  void addFlower();

  void setMap();

  void saveinfile(string filename);

  void generate();
};

#endif // CREATEMAP_HPP