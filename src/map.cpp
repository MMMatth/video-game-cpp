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

Tile Map::chooseTile(string c, int x, int y) { return Tile(getBlock(c), x, y); }

void Map::collide(Character *perso) {
  for (int i = 0; i < m_map.size(); i++) {
    m_map[i].collide(perso);
  }
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
      while (getline(ss, c, ';')) {
        m_map.push_back(chooseTile(c, x, y));
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
    for (int i = 0; i < m_map.size(); i++) {
      fichier << m_map[i].getBlock().getId();
      if (i % MAP_WIDTH == MAP_WIDTH - 1) {
        fichier << endl;
      } else {
        fichier << ";";
      }
    }
  } else {
    cout << "We cant open the map file" << endl;
  }
}

void Map::addTile(Block block, int mouseX, int mouseY) {
  cout << mouseX << " " << mouseY << endl;
  cout << m_map[0].getX() << " " << m_map[0].getY() << endl;
  for (int i = 0; i < m_map.size(); i++) {
    if (mouseX > m_map[i].getX() && mouseX < m_map[i].getX() + TILE_SIZE &&
        mouseY > m_map[i].getY() && mouseY < m_map[i].getY() + TILE_SIZE) {
      m_map[i].setBlock(block);
      return;
    }
  }
}

void Map::suprTile(int mouseX, int mouseY) {
  for (auto it = m_map.begin(); it != m_map.end(); ++it) {
    if (mouseX > it->getX() && mouseX < it->getX() + TILE_SIZE &&
        mouseY > it->getY() && mouseY < it->getY() + TILE_SIZE) {
      it->setBlock(blockMap["AIR"]);
      break;
    }
  }
}

void Map::clean() { m_map.clear(); }

string Map::toString() {
  string res;
  for (int i = 0; i < m_map.size(); i++) {
    res += m_map[i].toString();
  }
  return res;
}