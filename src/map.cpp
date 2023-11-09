#include "../include/map.hpp"

Block getBlock(string id) {
  for (auto it = blockMap.begin(); it != blockMap.end(); ++it) {
    if (it->second.getId() == id) {
      return it->second;
    }
  }
  return blockMap["AIR"];
}

using namespace std;

Map::Map() { initMap("../assets/map.txt"); }

Tile Map::chooseTile(string c, int x, int y) { return Tile(getBlock(c), x, y); }

void Map::collide(Character *perso) {
  for (int i = 0; i < m_map.size(); i++) {
    m_map[i].collide(perso);
  }
}

void Map::initMap(const char *nomFichier) {
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
    cout << "Erreur lors de l'ouverture du fichier" << endl;
  }
}

vector<Tile> Map::getMap() { return m_map; }

int Map::getSize() { return m_map.size(); }

Tile Map::getTile(int i) { return m_map[i]; }

void Map::clean() { m_map.clear(); }

string Map::toString() {
  string res;
  for (int i = 0; i < m_map.size(); i++) {
    res += m_map[i].toString();
  }
  return res;
}