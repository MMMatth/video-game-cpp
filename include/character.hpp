#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;

using namespace std;

class Character : public Entity {
public:
  /* constructor */
  Character(string path);
  Character(int x, int y, int life, int speed, int width, int height,
            int jumpHeight, int timeJump, bool save);
  // ~Character();
  bool loadFromCSV(string csvPath);
  void init();
  /* update */
  void update();

  /* getters */
  int getTimeJump() const { return m_timeJump; }
  int getJumpHeight() const { return m_jumpHeight; }

  /* other setters */
  void setTimeJump(int time) { m_timeJump = time; }
  void hit(int damage) { this->m_life -= damage; }
  void heal(int heal) { this->m_life += heal; }

  /* other */
  void save(string path);

private:
  bool m_save;      /** if true the charcater is save in csv */
  int m_timeJump;   /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
};

#endif /* PERSONNAGE_HPP */
