#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "../entity/entity.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
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
  Monster(int x, int y, int width, int height, int speed, int life)
      : Entity(x, y, width, height, speed, life) {
    m_timeJump = 0;
  }
  void update() override;

private:
  int m_timeJump;
  int m_jumpHeight;
};

#endif /* MONSTER_HPP */
