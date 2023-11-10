#include "../include/const.hpp"
#include "./include/FastNoiseLite.h"
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
  Createmap(int width) : m_width(width) {
    srand(time(NULL)); // we reset the random
    m_seed = rand();   // we set the seed
    m_map = vector<vector<int>>();
    m_underground_size = m_altitude.size * UNDERGROUND_COEF;
  }
  int abs(int a) { return a < 0 ? -a : a; }

  /**
   * \brief Set the Curve Altitude object
   *The objective of this function is to define the m_curve_altitude array which
   * will give the height of the map based on the x position.
   */
  void setCurveAltitude() {
    FastNoiseLite m_perlin_noise;   // we create a perlin noise
    m_perlin_noise.SetSeed(m_seed); // we set the seed
    m_perlin_noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_perlin_noise.SetFrequency(0.01);
    /* we search the min and the max */
    m_altitude.max =
        abs(m_perlin_noise.GetNoise((float)0, (float)0) * MOUNTAIN_COEF);
    m_altitude.min =
        abs(m_perlin_noise.GetNoise((float)0, (float)0) * MOUNTAIN_COEF);
    for (int i = 0; i < m_width; i++) {
      m_curve_altitude.push_back(
          abs(m_perlin_noise.GetNoise((float)i, (float)0) *
              MOUNTAIN_COEF)); // we add the altitude in the array
      if (m_curve_altitude[i] > m_altitude.max) {
        m_altitude.max = m_curve_altitude[i];
      }
      if (m_curve_altitude[i] < m_altitude.min) {
        m_altitude.min = m_curve_altitude[i];
      }
    }
    m_altitude.size = m_altitude.max - m_altitude.min + 1;
    m_underground_size = m_altitude.size * UNDERGROUND_COEF;
  }
  void addStone() {
    /* we add the underground part */
    for (int y = 0; y < m_underground_size; y++) {
      m_map.push_back(vector<int>());
      for (int x = 0; x < m_width; x++) {
        m_map[y].push_back(3);
      }
    }
    /* we add the moutain part */
    for (int y = m_underground_size; y < m_altitude.size + m_underground_size;
         y = y + 1) {
      m_map.insert(m_map.begin(), vector<int>()); // we add a line on the top
      for (int x = 0; x < m_width; x++) {
        if (y < m_curve_altitude[x] + m_underground_size) {
          m_map[0].push_back(3);
        } else {
          m_map[0].push_back(0);
        }
      }
    }
  }

  void addCave() {
    FastNoiseLite cave_noise;
    cave_noise.SetSeed(m_seed);
    cave_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    cave_noise.SetFrequency(0.09);
    for (int y = 0; y < m_map.size(); y++) {
      for (int x = 0; x < m_map[y].size(); x++) {
        if (cave_noise.GetNoise((float)x, (float)y) > 0.3) {
          if (m_map[y][x] == 3) {
            m_map[y][x] = 0;
          }
        }
      }
    }
  }

  void addGrass() {
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
        if (y == abs(m_curve_altitude[x] - m_altitude.size) &&
            m_map[y][x] == 3) {
          m_map[y][x] = 1;
          break; // we break the loop because we have found the grass block
        }
      }
    }
  }

  void addDirt() {
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
        if (m_map[y][x] == 1) {
          for (int i = 0; i < DIRT_HEIGHT; i++) {
            if (m_map[y + i][x] == 3) { // we remplace the stone by the dirt
              m_map[y + i][x] = 2;
            }
          }
          break;
        }
      }
    }
  }

  void addSky() {
    /* we add the sky for after add tree */
    for (int y = 0; y < SKY_HEIGHT_OVER_MOUTAIN; y++) {
      m_map.insert(m_map.begin(), vector<int>());
      for (int x = 0; x < m_width; x++) {
        m_map[0].push_back(0);
      }
    }
  }

  void addTree() {
    srand(time(NULL));
    int ecarts = 0;
    int ecarts_max = rand() % ECART_TREE + 10;
    for (int x = 0; x < m_width; x++) {
      ecarts++;
      if (ecarts == ecarts_max) {
        ecarts = 0;
        for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
          if (m_map[y][x] == 1) { // we only place tree on grass
            for (int i = 1; i <= TREE_SIZE; i++) { // we add the tree
              if (y - i >= 0) {
                m_map[y - i][x] = 5; // wood
              }
            }
            m_map[y][x] = 2; // we remplace the grass by the dirt
            break;           // when we place the tree we break the loop
          }
        }
        ecarts_max = rand() % ECART_TREE + 10;
      }
    }
  }
  void addLeaf() {
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
        if (m_map[y][x] == 5) { // if we find a tree
          for (int j = 0; j < LEAF_HEIGHT; j++) {
            for (int i = 0; i < LEAF_WIDTH; i++) { // we add the leaf
              m_map[y - j][x - LEAF_WIDTH / 2 + i] = 4;
            }
            if (j == LEAF_HEIGHT - 1) { // we remove the corners
              m_map[y - j][x - LEAF_WIDTH / 2] = 0;
              m_map[y - j][x + LEAF_WIDTH / 2] = 0;
            }
          }
          break; // when we place the leaf we break the loop
        }
      }
    }
  }

  void addFlower() {
    srand(time(NULL));
    int ecarts = 0;
    int ecarts_max = rand() % (FLOWER_ECART);
    for (int x = 0; x < m_width; x++) {
      ecarts++;
      if (ecarts == ecarts_max) {
        ecarts = 0;
        for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
          if (m_map[y][x] == 1) {
            if (rand() % 2 == 0) {
              m_map[y - 1][x] = 10; // red flower
            } else {
              m_map[y - 1][x] = 11; // yellow flower
            }
            break; // when we place the flower we break the loop
          }
        }
        ecarts_max = rand() % FLOWER_ECART;
      }
    }
  }

  void setMap() {
    addStone();
    addCave();
    addGrass();
    addDirt();
    addSky();
    addTree();
    addLeaf();
    addFlower();
  }

  void saveinfile(string filename) {
    ofstream file;
    file.open(filename, ofstream::out | ofstream::trunc);
    for (int x = 0; x < m_map.size(); x++) {
      for (int y = 0; y < m_map[x].size(); y++) {
        file << m_map[x][y]
             << ";"; // we write the map in the file like a csv file
      }
      file << endl;
    }
    file.close();
  }
};

int main(int argc, char const *argv[]) {
  Createmap map = Createmap(MAP_WIDTH);
  map.setCurveAltitude();
  map.setMap();
  map.saveinfile(MAP_PATH);
  return 0;
}