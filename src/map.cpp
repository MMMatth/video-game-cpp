#include "../include/map.hpp"

using namespace std;

/* aux func */
Block getBlock(string id) {
  for (auto it = blockMap.begin(); it != blockMap.end(); ++it) {
    if (it->second.getId() == id) {
      return it->second;
    }
  }
  return blockMap["AIR"];
}

/* constructor */
Map::Map(string path) : m_cam(0, 0), m_cam_width(0), m_cam_height(0) {
  initLength(path);
  initMap(path);
}

Map::Map(int height, int width) {
  for (int y = 0; y < height; y++) {
    m_map.push_back(std::vector<Tile>());
    for (int x = 0; x < width; x++) {
      m_map[y].push_back(Tile(getBlock("AIR"), x, y));
    }
  }
}
/* destructor */
void Map::clear() {
  for (int y = 0; y < m_height; y++) {
    m_map[y].clear();
  }
  m_map.clear();
}

/* init function */

void Map::initLength(string nomFichier) {
  int width = 0;
  m_width = 0;
  m_height = 0;
  ifstream fichier(nomFichier);
  if (fichier) {
    string ligne;
    while (getline(fichier, ligne)) {
      stringstream ss(ligne);
      string c;
      while (getline(ss, c, ';')) {
        width++;
      }
      if (width > m_width) {
        m_width = width;
      }
      width = 0;
      m_height++;
    }
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
      m_map.push_back(std::vector<Tile>());
      while (getline(ss, c, ';')) {
        m_map[y].push_back(chooseTile(c, x, y));
        x++;
      }
      if (x < m_width) {
        for (int i = x; i < m_width; i++) {
          m_map[y].push_back(chooseTile("0", i, y));
        }
      }
      y++;
    }
  } else {
    cout << "We cant open the map file" << endl;
  }
  // save(nomFichier);
}

/* getters */

Tile Map::chooseTile(string c, int x, int y) { return Tile(getBlock(c), x, y); }

Tile *Map::find_tile(int mouseX, int mouseY) {
  for (int y = m_cam.getY(); y < m_cam_height; y++) {
    for (int x = m_cam.getX(); x < m_cam_width; x++) {
      if (mouseX > m_map[y][x].getX() &&
          mouseX < m_map[y][x].getX() + TILE_SIZE &&
          mouseY > m_map[y][x].getY() &&
          mouseY < m_map[y][x].getY() + TILE_SIZE) {
        cout << m_map[y][x].getBlock()->getName() << endl;
        return &m_map[y][x];
      }
    }
  }
  return nullptr;
}

Clock Map::getBreakingClock(int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    return target->getBreakingClock();
  } else {
    cerr << "getBreakingClock : target is nullptr" << endl;
    return Clock();
  }
}

bool Map::isBreaking(int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    return target->isBreaking();
  } else {
    // cerr << "isBreaking : target is nullptr" << endl;
    return false;
  }
}

/* setters */
void Map::setIsBreaking(bool isBreaking, int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    target->setBreaking(isBreaking);
  } else {
    cerr << "setIsBreaking : target is nullptr" << endl;
  }
}

void Map::resetBreakingClock(int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    target->resetBreakingClock();
  } else {
    cerr << "resetBreakingClock : target is nullptr" << endl;
  }
}

/* other */

void Map::save(string path) {
  ofstream fichier(path);
  if (fichier) {
    for (int y = 0; y < m_height; y++) {
      for (int x = 0; x < m_width; x++) {
        fichier << m_map[y][x].getBlock()->getId();
        fichier << ";";
      }
      fichier << endl;
    }
  }
}

void Map::collide(Character *perso, int camX, int camY) {
  for (int y = m_cam.getY(); y < m_cam_height; y++) {
    for (int x = m_cam.getX(); x < m_cam_width; x++) {
      if (m_map[y][x].getBlock()->isSolid()) {
        m_map[y][x].collide(perso);
      }
    }
  }
}

void Map::collide(Character *perso) {
  if (perso->getX() < 0)
    perso->setCollision("left", true);
  if (perso->getX() + perso->getWidth() > get_width() * TILE_SIZE)
    perso->setCollision("right", true);
  if (perso->getY() < 0)
    perso->setCollision("up", true);
  if (perso->getY() + perso->getHeight() > get_height() * TILE_SIZE)
    perso->setCollision("down", true);
}

void Map::add_tile(Block block, int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    target->setBlock(block);
  } else {
    cerr << "add_tile : target is nullptr" << endl;
  }
}

void Map::supr_tile(int mouseX, int mouseY) {
  Tile *target = find_tile(mouseX, mouseY);
  if (target) {
    target->setBlock(blockMap["AIR"]);
  } else {
    cerr << "supr_tile: target is nullptr" << endl;
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

string Map::toString() {
  string res;
  for (int y = 0; y < m_map.size(); y++) {
    for (int x = 0; x < m_map[y].size(); x++) {
      res += m_map[y][x].toString();
    }
  }
  return res;
}
