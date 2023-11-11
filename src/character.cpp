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
  this->m_width = 28;
  this->m_height = 58;

  this->m_direction = {{"isJumping", false},
                       {"isGoingUp", false},
                       {"isFalling", true},
                       {"isGoingRight", false},
                       {"isGoingLeft", false}};

  this->m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  this->m_jumpHeight = 15;
  this->m_timeJump = 0;
  this->m_speed = 3;
}

void Character::update() {

  if (m_direction["isJumping"] && m_collision["down"]) {
    this->m_direction["isGoingUp"] = true;
    this->m_timeJump = 0;
    this->m_collision["down"] = false;
  }
  if (!m_direction["isJumping"]) {
    this->m_direction["isGoingUp"] = false;
    this->m_direction["isFalling"] = true;
  }
  if (m_direction["isGoingUp"] && !m_collision["up"]) {
    this->m_timeJump++;
    if (m_timeJump < m_jumpHeight) {
      this->deplacerY(-m_speed);
    } else {
      this->m_direction["isGoingUp"] = false;
      this->m_direction["isFalling"] = true;
    }
  }
  if (m_direction["isFalling"] && !m_collision["down"] &&
      !m_direction["isGoingUp"]) {
    this->deplacerY(m_speed);
  }

  if (m_direction["isGoingRight"] && !m_collision["right"]) {

    this->setCollisionFalseExcept("right");
    this->deplacerX(m_speed);
  }

  if (m_direction["isGoingLeft"] && !m_collision["left"]) {
    this->setCollisionFalseExcept("left");

    this->deplacerX(-m_speed);
  }

  if (m_direction["isGoingUp"] && !m_collision["up"]) {
    this->setCollisionFalseExcept("up");

    this->deplacerY(-m_speed);
  }
  if (m_collision["up"] && !m_collision["down"] && m_collision["right"] &&
      m_collision["left"]) {

    this->setCollisionFalseExcept("down");

    this->deplacerY(m_speed);
  }
}

void Character::setCollisionFalseExcept(string key) {
  for (auto &x : this->m_collision) {
    if (x.first != key) {
      x.second = false;
    }
  }
}

// other methods
void Character::deplacerX(int x) {
  this->m_coord.setX(this->m_coord.getX() + x);
}

void Character::deplacerY(int y) {
  this->m_coord.setY(this->m_coord.getY() + y);
}

void Character::save(string path) {
  ofstream file;
  file.open(path);
  if (file.is_open()) {
    file << "x;y\n";                                     // write the header
    file << this->getX() << ";" << this->getY() << "\n"; // write the position
  } else {
    cerr << "Save Character unable to open file " << path << "\n";
  }
  file.close();
}