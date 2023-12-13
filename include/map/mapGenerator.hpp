#ifndef CREATEMAP_HPP
#define CREATEMAP_HPP

#include "../lib/fastnoise/FastNoiseLite.h"
#include "../utils/const.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/** @brief Struct for the altitude of the map. */
struct altitude {
  int max;
  int min;
  int size;
};

class Createmap {
private:
  int m_seed;                   /** seed for the perlin noise */
  int m_width;                  /** width of the map */
  vector<int> m_curve_altitude; /** vector of altitude for the perlin noise */
  vector<vector<int>> m_map;    /** 2D vector of the map */
  altitude m_altitude;          /** altitude of the map */
  int m_underground_size;       /** size of the underground */

public:
  /** @brief Constructor for Createmap. */
  Createmap(int width);

  /** @brief Set the Curve Altitude object. */
  void setCurveAltitude();

  /** @brief Add stone blocks to the map. */
  void addStone();

  /** @brief Add cave to the map. */
  void addCave();

  /** @brief Add grass blocks to the map. */
  void addGrass();

  /** @brief Add dirt blocks to the map. */
  void addDirt();

  /** @brief Add sky blocks to the top layer of the map. */
  void addSky();

  /** @brief Add tree structures to the map. */
  void addTrunk();

  /** @brief Add leaf blocks to the map for trees. */
  void addLeaf();

  /** @brief Add flower blocks to the map. */
  void addFlower();

  /** @brief Set the entire map based on the generated features. */
  void setMap();

  /** @brief Save the generated map to a file. */
  void saveinfile(string filename);

  /** @brief Generate the map with various features. */
  void generate();
};

#endif // CREATEMAP_HPP