#include "../include/character.hpp"
#include "../include/draw.hpp"

using namespace std;

Character::Character(string path) {
  ifstream file(path);
  if (file.is_open()) {
    string line;
    getline(file, line); // skip the header
    getline(file, line); // read the position
    stringstream ss(line);
    string x_str, y_str;
    getline(ss, x_str, ';');
    getline(ss, y_str, ';');
    m_coord = Coord(stoi(x_str), stoi(y_str));
  } else {
    // we create the file
    ofstream file(path);
    if (file.is_open()) {
      file << "x;y\n";
      file << MAP_WIDTH * TILE_SIZE / 2 << ";" << 0 << "\n";
      m_coord = Coord(MAP_WIDTH * TILE_SIZE / 2, 0);
    } else {
      cerr << "Character unable to open file " << path << "\n";
    }
  }
  init();
}

Character::Character(int x, int y) : m_coord(x, y) { init(); }

void Character::init() {
  m_width = 28;
  m_height = 58;

  m_direction = {{"jump", false},
                 {"up", false},
                 {"fall", true},
                 {"right", false},
                 {"left", false}};

  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  m_jumpHeight = 15;
  m_timeJump = 0;
  m_speed = 3;
}

void Character::update() {
  /* if the player can and want jump */
  if (m_direction["jump"] && m_collision["down"]) {
    m_timeJump = 0;
    m_direction["up"] = true;
    m_collision["down"] = false;
  } else if (m_collision["down"]) { // if the player touch the ground
    m_direction["fall"] = false;
  } else { // if the player is in the air
    m_direction["fall"] = true;
  }

  /* if the player stop jumping or the player touch the roof and is going up*/
  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  if (m_direction["up"] && !m_collision["up"] && m_timeJump < m_jumpHeight) {
    m_timeJump++;
    mooveY(-m_speed);
  } else if (m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }
  /* we moove the player */
  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    mooveY(m_speed);
  }
  if (m_direction["right"] && !m_collision["right"]) {
    mooveX(m_speed);
  }
  if (m_direction["left"] && !m_collision["left"]) {
    mooveX(-m_speed);
  }
  if (m_direction["up"] && !m_collision["up"]) {
    mooveY(-m_speed);
  }
  if (m_collision["up"] && !m_collision["down"]) {
    m_direction["fall"] = true;
    mooveY(m_speed);
  }

  /* We reset collision because it's going to be refreshed */
  m_collision["up"] = false;
  m_collision["down"] = false;
  m_collision["left"] = false;
  m_collision["right"] = false;
}

void Character::setCollisionFalseExcept(string key) {
  for (auto &x : m_collision) {
    if (x.first != key) {
      x.second = false;
    }
  }
}

// other methods
void Character::mooveX(int x) { m_coord.setX(m_coord.getX() + x); }

void Character::mooveY(int y) { m_coord.setY(m_coord.getY() + y); }

void Character::save(string path) {
  ofstream file;
  file.open(path);
  if (file.is_open()) {
    file << "x;y\n";                         // write the header
    file << getX() << ";" << getY() << "\n"; // write the position
  } else {
    cerr << "Save Character unable to open file " << path << "\n";
  }
  file.close();
}