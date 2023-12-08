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
  Monster(int x, int y, int width, int height, int speed, int life, int maxLife)
      : Entity(x, y, width, height, speed, life, maxLife) {}

  virtual void update(const Character &m_char) = 0;

private:
  /* data */
};

#endif /* MONSTER_HPP */
