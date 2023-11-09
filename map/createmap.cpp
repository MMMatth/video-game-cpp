#include "./include/FastNoiseLite.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
/* plus le coeff est grand plus les montagnes sont grande*/
#define MOUNTAIN_COEF 15
/* nombre de fois qu'il y'a l'altitude en dessous du niveau zero */
#define UNDERGROUND_COEF 20
/* arbre */
#define TREE_SIZE 4
#define ECART_TREE 10
#define LEAF_WIDTH 5
#define LEAF_HEIGHT 3
/* flower */
#define FLOWER_ECART 10

struct altitude {
  int max;
  int min;
  int size;
};

class Createmap {
private:
  int m_seed;
  int m_width;
  vector<int> m_curve_altitude;
  vector<vector<int>> m_map;
  altitude m_altitude;

public:
  Createmap(int width) : m_width(width) {
    srand(time(NULL));
    // m_seed = rand();
    m_seed = 1;
    m_map = vector<vector<int>>();
  }
  int abs(int a) { return a < 0 ? -a : a; }

  void setCurveAltitude() {
    FastNoiseLite m_perlin_noise;
    m_perlin_noise.SetSeed(m_seed);
    m_perlin_noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_perlin_noise.SetFrequency(0.01);
    m_altitude.max =
        abs(m_perlin_noise.GetNoise((float)0, (float)0) * MOUNTAIN_COEF);
    m_altitude.min =
        abs(m_perlin_noise.GetNoise((float)0, (float)0) * MOUNTAIN_COEF);
    for (int i = 0; i < m_width; i++) {
      m_curve_altitude.push_back(
          abs(m_perlin_noise.GetNoise((float)i, (float)0) * MOUNTAIN_COEF));
      if (m_curve_altitude[i] > m_altitude.max) {
        m_altitude.max = m_curve_altitude[i];
      }
      if (m_curve_altitude[i] < m_altitude.min) {
        m_altitude.min = m_curve_altitude[i];
      }
    }
    m_altitude.size = m_altitude.max - m_altitude.min + 1;
  }
  void setStone() {
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    for (int y = 0; y < underground_size; y++) {
      m_map.push_back(vector<int>());
      for (int x = 0; x < m_width; x++) {
        m_map[y].push_back(3);
      }
    }
    for (int y = underground_size; y < m_altitude.size + underground_size;
         y = y + 1) {
      m_map.insert(m_map.begin(), vector<int>());
      for (int x = 0; x < m_width; x++) {
        if (y < m_curve_altitude[x] + underground_size) {
          m_map[0].push_back(3);
        } else {
          m_map[0].push_back(0);
        }
      }
    }
  }

  void setCave() {
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

  void setGrass() {
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + underground_size; y++) {
        if (y == abs(m_curve_altitude[x] - m_altitude.size) &&
            m_map[y][x] == 3) {
          m_map[y][x] = 1;
        }
      }
    }
  }

  void setDirt() {
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + underground_size; y++) {
        if (m_map[y][x] == 1) {
          for (int i = 0; i < 3; i++) {
            if (m_map[y + i][x] == 3) {
              m_map[y + i][x] = 2;
            }
          }
          break;
        }
      }
    }
  }

  void addSky() {
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    for (int y = 0; y < 10; y++) {
      // on rajouter 50 ligne de ciel au debut du ta
      m_map.insert(m_map.begin(), vector<int>());
      for (int x = 0; x < m_width; x++) {
        m_map[0].push_back(0);
      }
    }
  }

  void addTree() {
    srand(time(NULL));
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    int ecarts = 0;
    // entre 10 et 20
    int ecarts_max = rand() % ECART_TREE + 10;
    for (int x = 0; x < m_width; x++) {
      ecarts++;
      if (ecarts == ecarts_max) {
        ecarts = 0;
        for (int y = 0; y < m_altitude.size + underground_size; y++) {
          if (m_map[y][x] == 1) {
            for (int i = 1; i <= TREE_SIZE; i++) { // we add the tree
              if (y - i >= 0) {
                m_map[y - i][x] = 5; // wood
              }
            }
          }
        }
        ecarts_max = rand() % ECART_TREE + 10;
      }
    }
  }
  void addLeaf() {
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_altitude.size + underground_size; y++) {
        if (m_map[y][x] == 5) { // if we find a tree
          for (int j = 0; j < LEAF_HEIGHT; j++) {
            for (int i = 0; i < LEAF_WIDTH; i++) {
              m_map[y - j][x - LEAF_WIDTH / 2 + i] = 4; // leaf
            }
            if (j == LEAF_HEIGHT - 1) { // we remove the corners
              m_map[y - j][x - LEAF_WIDTH / 2] = 0;
              m_map[y - j][x + LEAF_WIDTH / 2] = 0;
            }
          }
          break;
        }
      }
    }
  }

  void addFlower() {
    srand(time(NULL));
    int underground_size = m_altitude.size * UNDERGROUND_COEF;
    int ecarts = 0;
    int ecarts_max = rand() % (FLOWER_ECART);
    for (int x = 0; x < m_width; x++) {
      ecarts++;
      if (ecarts == ecarts_max) {
        ecarts = 0;
        for (int y = 0; y < m_altitude.size + underground_size; y++) {
          if (m_map[y][x] == 1) {
            if (rand() % 2 == 0) {
              m_map[y - 1][x] = 10; // red flower
            } else {
              m_map[y - 1][x] = 11; // yellow flower
            }
          }
        }
        ecarts_max = rand() % FLOWER_ECART;
      }
    }
  }

  void setMap() {
    setStone();
    setCave();
    setGrass();
    setDirt();
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
        file << m_map[x][y] << ";";
      }
      file << endl;
    }
    file.close();
  }

  void printCurveAltitude() {
    for (int i = 0; i < m_curve_altitude.size(); i++) {
      cout << m_curve_altitude[i];
    }
    cout << endl;
  }
};

int main(int argc, char const *argv[]) {
  Createmap map = Createmap(50);
  map.setCurveAltitude();
  map.setMap();
  map.saveinfile("../assets/map.txt");
  return 0;
}