#include "../include/mapGenerator.hpp"

int abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

Createmap::Createmap(int width) {
  m_width = width;
  m_seed = time(NULL);
}

void Createmap::setCurveAltitude() {
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

void Createmap::addStone() {
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

void Createmap::addCave() {
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

void Createmap::addGrass() {
  for (int x = 0; x < m_width; x++) {
    for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
      if (y == abs(m_curve_altitude[x] - m_altitude.size) && m_map[y][x] == 3) {
        m_map[y][x] = 1;
        break; // we break the loop because we have found the grass block
      }
    }
  }
}

void Createmap::addDirt() {
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

void Createmap::addSky() {
  /* we add the sky for after add tree */
  for (int y = 0; y < SKY_HEIGHT_OVER_MOUTAIN; y++) {
    m_map.insert(m_map.begin(), vector<int>());
    for (int x = 0; x < m_width; x++) {
      m_map[0].push_back(0);
    }
  }
}

void Createmap::addTree() {
  srand(time(NULL));
  int ecarts = 0;
  int ecarts_max = rand() % ECART_TREE + 10;
  for (int x = 0; x < m_width; x++) {
    ecarts++;
    if (ecarts == ecarts_max) {
      ecarts = 0;
      for (int y = 0; y < m_altitude.size + m_underground_size; y++) {
        if (m_map[y][x] == 1) {                  // we only place tree on grass
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
void Createmap::addLeaf() {
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

void Createmap::addFlower() {
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

void Createmap::setMap() {
  addStone();
  addCave();
  addGrass();
  addDirt();
  addSky();
  addTree();
  addLeaf();
  addFlower();
}

void Createmap::saveinfile(string filename) {
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

void Createmap::generate() {
  setCurveAltitude();
  setMap();
  saveinfile(MAP_PATH);
}