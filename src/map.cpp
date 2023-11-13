#include "../include/map.hpp"

using namespace std;

Block getBlock(string id) {
  for (auto it = blockMap.begin(); it != blockMap.end(); ++it) {
    if (it->second.getId() == id) {
      return it->second;
    }
  }
  return blockMap["AIR"];
}

Map::Map(string path) { initMap(path); }

Map::Map(int height, int width) {
  for (int y = 0; y < height; y++) {
    m_map.push_back(std::vector<Tile>());
    for (int x = 0; x < width; x++) {
      m_map[y].push_back(Tile(getBlock("AIR"), x, y));
    }
  }
}

Tile Map::chooseTile(string c, int x, int y) { return Tile(getBlock(c), x, y); }

void Map::collide(Character *perso, int camX, int camY) {
  for (int y = m_cam.getY(); y < m_cam_height; y++) {
    for (int x = m_cam.getX(); x < m_cam_width; x++) {
      if (m_map[y][x].getBlock().isSolid()) {
        m_map[y][x].collide(perso);
      }
    }
  }
}

void Map::update(int camX, int camY) {
  int newCamX = (camX - CAM_WIDTH) / TILE_SIZE;
  int newCamY = (camY - CAM_HEIGHT) / TILE_SIZE;
  int newCamWidth = (camX + CAM_WIDTH) / TILE_SIZE;
  int newCamHeight = (camY + CAM_HEIGHT) / TILE_SIZE;
  if (newCamX < 0)
    newCamX = 0;
  if (newCamY < 0)
    newCamY = 0;
  if (newCamWidth >= get_width())
    newCamWidth = get_width();
  if (newCamHeight >= get_height())
    newCamHeight = get_height();

  m_cam.setCoord(newCamX, newCamY);
  m_cam_width = newCamWidth;
  m_cam_height = newCamHeight;
}

void Map::initMap(string nomFichier) {
  ifstream fichier(nomFichier);
  if (fichier) {
    string ligne;
    int y = 0;
    while (getline(fichier, ligne)) {
      stringstream ss(ligne);
      string c;
      int x = 0;
      m_map.push_back(std::vector<Tile>());
      while (getline(ss, c, ';')) {
        m_map[y].push_back(chooseTile(c, x, y));
        x++;
      }
      y++;
    }
  } else {
    cout << "We cant open the map file" << endl;
  }
}

void Map::save(string path) {
  ofstream fichier(path);
  if (fichier) {
    for (int y = 0; y < m_map.size(); y++) {
      for (int x = 0; x < m_map[y].size(); x++) {
        fichier << m_map[y][x].getBlock().getId();
        if (x != m_map[y].size() - 1) {
          fichier << ";";
        }
      }
      fichier << endl;
    }
  }
}

void Map::add_tile(Block block, int mouseX, int mouseY) {
  for (int y = 0; y < m_map.size(); y++) {
    for (int x = 0; x < m_map[y].size(); x++) {
      if (mouseX > m_map[y][x].getX() &&
          mouseX < m_map[y][x].getX() + TILE_SIZE &&
          mouseY > m_map[y][x].getY() &&
          mouseY < m_map[y][x].getY() + TILE_SIZE) {
        m_map[y][x].setBlock(block);
        return;
      }
    }
  }
}

void Map::supr_tile(int mouseX, int mouseY) {
  for (int y = 0; y < m_map.size(); y++) {
    for (int x = 0; x < m_map[y].size(); x++) {
      if (mouseX > m_map[y][x].getX() &&
          mouseX < m_map[y][x].getX() + TILE_SIZE &&
          mouseY > m_map[y][x].getY() &&
          mouseY < m_map[y][x].getY() + TILE_SIZE) {
        m_map[y][x].setBlock(blockMap["AIR"]);
        return;
      }
    }
  }
}

void Map::clean() {
  for (int y = 0; y < m_map.size(); y++) {
    m_map[y].clear();
  }
  m_map.clear();
}

string Map::toString() {
  string res;
  for (int y = 0; y < m_map.size(); y++) {
    for (int x = 0; x < m_map[y].size(); x++) {
      res += m_map[y][x].toString();
    }
  }
  return res;
}