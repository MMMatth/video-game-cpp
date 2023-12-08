#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "../entity/entity.hpp"
#include "../map/map.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <SFML/Audio.hpp>
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

class Map;

class Character : public Entity {
public:
  Character();
  /* constructor */

  Character(string fileName, bool save, int maxLife);

  Character(int x, int y, int life, int maxLife, int speed, int width,
            int height, int jumpHeight, int timeJump, bool save);

  bool loadFromCSV(string csvPath);

  void init();
  /* update */
  void update();
  void collide(Map *map, int camX, int camY);

  /* getters */
  int getTimeJump() const { return m_timeJump; }
  int getJumpHeight() const { return m_jumpHeight; }

  /* other setters */
  void setTimeJump(int time) { m_timeJump = time; }

  /* other */
  void reset(bool save, int x, int y,
             string path = string(SAVE_PATH) + string(CHARACTER_SAVE_PATH));
  void save(string path);

private:
  bool m_save;      /** if true the charcater is save in csv */
  int m_timeJump;   /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
};

#endif /* PERSONNAGE_HPP */
