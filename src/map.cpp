#include "../include/map.hpp"

using namespace std;

Map::Map() { initMap("../assets/map.txt"); }

Tile Map::chooseTile(char c, int x, int y) {
  Block block;
  switch (c) {
  case '1':
    block = blockMap["GRASS"];
    break;
  case '2':
    block = blockMap["DIRT"];
    break;
  case '3':
    block = blockMap["STONE"];
    break;
  default:
    block = blockMap["AIR"];
    break;
  }
  return Tile(block, x, y);
}

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
      for (int x = 0; x < ligne.size(); x++) {
        m_map.push_back(chooseTile(ligne[x], x, y));
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