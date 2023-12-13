#include "../../include/entity/character.hpp"

using namespace std;

Character::Character(string filePath, bool save)
    : Entity(0, 0, 0, 0, 0, 0, CHAR_MAX_LIFE), m_save(save) {
  if (!loadFromCSV(filePath)) {
    // if the file doesn't open we have to define the coord and life
    m_coord = Coord(CHAR_X, CHAR_Y); // we use default value
    m_life = CHAR_MAX_LIFE;          // we use default value
  }
  init();
}

Character::Character(int x, int y, int life, int maxLife, int speed, int width,
                     int height, int jumpHeight, int timeJump, bool save)
    : Entity(x, y, width, height, speed, life, maxLife), m_save(save) {
  m_direction = {{"jump", false},
                 {"up", false},
                 {"fall", true},
                 {"right", false},
                 {"left", false}};
  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};
}

bool Character::loadFromCSV(string csvPath) {
  ifstream file(csvPath); // open the file
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
  m_width = CHAR_WIDTH;
  m_height = CHAR_HEIGHT;
  m_direction = {{"jump", false},
                 {"up", false},
                 {"fall", true},
                 {"right", false},
                 {"left", false}};

  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};

  m_jumpHeight = CHAR_JUMP_HEIGHT;
  m_speed = CHAR_SPEED;
  m_timeJump = 0;
}

void Character::update() {
  /* jump part */
  if (m_direction["jump"] && m_collision["down"]) { // if the player jump
    m_timeJump = 0;
    m_direction["up"] = true;
    m_collision["down"] = false;
  } else if (m_collision["down"]) { // if the player touch the ground
    m_direction["fall"] = false;
  } else { // if the player is in the air
    m_direction["fall"] = true;
  }
  /* if the jump is interrupted */
  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }
  /* if the player is jumping */
  if (m_direction["up"] && !m_collision["up"] && m_timeJump < m_jumpHeight) {
    m_timeJump++;    // we increment the time of the jump
    moveY(-m_speed); // we move the player
  }
  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    moveY(m_speed);
  }

  /* movement part */
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

void Character::collide(Map *map) { map->collide(this); }

void Character::reset(bool save, string path) {
  init();
  m_coord = Coord(CHAR_X, CHAR_Y);
  m_life = CHAR_MAX_LIFE;
  m_save = save;
}

void Character::save(string path) {
  if (m_save) {
    ofstream file;
    file.open(path);
    if (file.is_open()) {
      file << "x;y;life\n"; /* header */
      file << getX() << ";" << getY() << ";" << getLife()
           << "\n"; /* position and life */
    } else {
      cerr << "Save Character unable to open file " << path << "\n";
    }
    file.close();
  }
}