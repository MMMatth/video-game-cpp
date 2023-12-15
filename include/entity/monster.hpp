#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "../entity/entity.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "../utils/list.hpp"
#include "character.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace sf;

class Monster : public Entity {
public:
  Monster(int x, int y, int width, int height, int speed, int life, int maxLife,
          string type)
      : Entity(x, y, width, height, speed, life, maxLife), m_type(type) {}

  virtual void update(const Character &m_char) = 0;

  string getType() { return m_type; }

  void setType(string type) { m_type = type; }

private:
  string m_type;
};

#endif /* MONSTER_HPP */
