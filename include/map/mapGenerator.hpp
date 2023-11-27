#ifndef CREATEMAP_HPP
#define CREATEMAP_HPP

#include "../lib/fastnoise/FastNoiseLite.h"
#include "../utils/const.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @struct altitude
 * @brief Represents the altitude range with maximum, minimum, and size.
*/
struct altitude {
  int max;  /**< The maximum altitude. */
  int min;  /**< The minimum altitude. */
  int size; /**< The size of the altitude range (max - min + 1). */
};

/**
 * @class Createmap
 * @brief Represents a map generator.
 *
 * This class is responsible for generating game maps with various features such
 * as terrain, caves, trees, and more.
*/
class Createmap {
private:
  int m_seed;                   // seed for the random
  int m_width;                  // width of the map
  vector<int> m_curve_altitude; // curve of the altitude
  vector<vector<int>> m_map;    // map
  altitude m_altitude;          // altitude
  int m_underground_size;       // size of the underground

public:
  /**
   * Parameterized constructor for Createmap.
   * @param width The width of the map.
  */
  Createmap(int width);

  /**
   * \brief Set the Curve Altitude object
   *The objective of this function is to define the m_curve_altitude array which
   * will give the height of the map based on the x position.
   */
  void setCurveAltitude();

   /**
   * Add stone blocks to the map based on the altitude curve.
   */
  void addStone();

  /**
   * Add cave-like structures to the map.
   */
  void addCave();

  /**
   * Add grass blocks to the map based on the altitude curve.
   */
  void addGrass();

  /**
   * Add dirt blocks to the map based on the altitude curve.
   */
  void addDirt();

  /**
   * Add sky blocks to the top layer of the map.
   */
  void addSky();

  /**
   * Add tree structures to the map.
   */
  void addTree();

  /**
   * Add leaf blocks to the map for trees.
   */
  void addLeaf();

  /**
   * Add flower blocks to the map.
   */
  void addFlower();

  /**
   * Set the entire map based on the generated features.
   */
  void setMap();

  /**
   * Save the generated map to a file.
   * @param filename The name of the file where the map will be saved.
   */
  void saveinfile(string filename);

  /**
   * Generate the map with various features.
   */
  void generate();
};

#endif // CREATEMAP_HPP