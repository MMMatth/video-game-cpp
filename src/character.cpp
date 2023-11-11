#include "../include/character.hpp"

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
  if (m_direction["jump"] && m_collision["down"] && !m_collision["up"]) {
    m_timeJump = 0;
    m_direction["up"] = true;
    m_collision["down"] = false;
  }
  /* if the player dont press jump key or the player collide the roof*/
  if (!m_direction["jump"] || m_collision["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }
  /* if the player is in the air */
  if (m_direction["up"] && !m_collision["up"]) {
    m_timeJump++;
    /* While the time jump is not equal to or greater than jump height */
    if (m_timeJump < m_jumpHeight) {
      deplacerY(-m_speed);
    } else { /* if the player reach the jump height */
      /* is fall */
      m_direction["up"] = false;
      m_direction["fall"] = true;
    }
  }
  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    deplacerY(m_speed);
  }
  if (m_direction["right"] && !m_collision["right"]) {
    deplacerX(m_speed);
  }
  if (m_direction["left"] && !m_collision["left"]) {
    deplacerX(-m_speed);
  }
  if (m_direction["up"] && !m_collision["up"]) {
    deplacerY(-m_speed);
  }
  if (m_collision["up"] && !m_collision["down"]) {
    m_direction["fall"] = true;
    deplacerY(m_speed);
  }
  cout << m_collision["up"] << " " << m_collision["down"] << " "
       << m_collision["left"] << " " << m_collision["right"] << "\n";
  cout << m_direction["up"] << " " << m_direction["fall"] << " "
       << m_direction["left"] << " " << m_direction["right"] << "\n";
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
void Character::deplacerX(int x) { m_coord.setX(m_coord.getX() + x); }

void Character::deplacerY(int y) { m_coord.setY(m_coord.getY() + y); }

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