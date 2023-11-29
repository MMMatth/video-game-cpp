#include "../../include/entity/character.hpp"

using namespace std;

const int characterWidth = 28;
const int characterHeight = 58;

const int characterJumpHeight = 15;
const int characterTimeJump = 0;

const int characterSpeed = 3;
const int characterLife = 20;

Character::Character() : Entity(0, 0, 0, 0, 0, 0) {
  m_jumpHeight = 0;
  m_timeJump = 0;
}

Character::Character(string fileName, bool save)
    : Entity(0, 0, 0, 0, 0, 0), m_save(save) {
  // string csvPath = path + fileName;
  if (!loadFromCSV(fileName)) {
    m_coord = Coord(MAP_WIDTH * TILE_SIZE / 2, 64);
    m_life = 20;
  }
  init();
}

Character::Character(int x, int y, int life, int speed, int width, int height,
                     int jumpHeight, int timeJump, bool save)
    : Entity(x, y, width, height, speed, life), m_save(save) {
  m_direction = {{"jump", false},
                 {"up", false},
                 {"fall", true},
                 {"right", false},
                 {"left", false}};
  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};
}

bool Character::loadFromCSV(string csvPath) {
  ifstream file(csvPath);
  if (file.is_open()) {
    string line;
    getline(file, line); // skip the header
    getline(file, line); // read the position
    stringstream ss(line);
    string x_str, y_str, life_str;
    getline(ss, x_str, ';');
    getline(ss, y_str, ';');
    getline(ss, life_str, ';');
    int x = stoi(x_str);
    int y = stoi(y_str);
    if (y % TILE_SIZE == 0)
      m_coord = Coord(x, y);
    else
      m_coord = Coord(x, y - y % TILE_SIZE);
    m_life = stoi(life_str);
    return true;
  } else {
    cerr << "Load Character unable to open file " << csvPath << "\n";
    return false;
  }
}

void Character::init() {
  m_width = characterWidth;
  m_height = characterHeight;
  m_direction = {{"jump", false},
                 {"up", false},
                 {"fall", true},
                 {"right", false},
                 {"left", false}};

  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  m_jumpHeight = characterJumpHeight;
  m_timeJump = characterTimeJump;
  m_speed = characterSpeed;
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

  /* if the player stop jumping or the player touch the roof and is going
   * up*/
  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  if (m_direction["up"] && !m_collision["up"] && m_timeJump < m_jumpHeight) {
    m_timeJump++;
    moveY(-m_speed);
  } else if (m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }
  /* we moove the player */
  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    moveY(m_speed);
  }
  if (m_direction["right"] && !m_collision["right"]) {
    moveX(m_speed);
  }
  if (m_direction["left"] && !m_collision["left"]) {
    moveX(-m_speed);
  }
  if (m_direction["up"] && !m_collision["up"]) {
    moveY(-m_speed);
  }
  if (m_collision["up"] && !m_collision["down"]) {
    m_direction["fall"] = true;
    moveY(m_speed);
  }

  /* We reset collision because it's going to be refreshed */
  m_collision["up"] = false;
  m_collision["down"] = false;
  m_collision["left"] = false;
  m_collision["right"] = false;
}

void Character::collide(Map *map, int camX, int camY) {
  map->collide(this, camX, camY);
  map->collide(this);
}

void Character::save(string path) {
  if (m_save) {
    ofstream file;
    file.open(path);
    if (file.is_open()) {
      file << "x;y;life\n"; /* header */
      file << getX() << ";" << getY() << ";" << getLife()
           << "\n"; /* position */
    } else {
      cerr << "Save Character unable to open file " << path << "\n";
    }
    file.close();
  }
}