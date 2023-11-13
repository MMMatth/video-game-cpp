#ifndef CREATEMAP_HPP
#define CREATEMAP_HPP

#include "const.hpp"
#include "lib/fastnoise/FastNoiseLite.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
/* plus le coeff est grand plus les montagnes sont grande*/
#define MOUNTAIN_COEF 15
/* nombre de fois qu'il y'a l'altitude en dessous du niveau zero */
#define UNDERGROUND_COEF 10
/* sky */
#define SKY_HEIGHT_OVER_MOUTAIN 15
/* dirt*/
#define DIRT_HEIGHT 3
/* arbre */
#define TREE_SIZE 4
#define ECART_TREE 10
#define LEAF_WIDTH 5
#define LEAF_HEIGHT 3
/* flower */
#define FLOWER_ECART 10

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