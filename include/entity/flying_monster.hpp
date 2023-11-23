#ifndef FLYING_MONSTER_HPP
#define FLYING_MONSTER_HPP

#include "monster.hpp"

using namespace std;
using namespace sf;

class FlyingMonster : public Monster {
private:
  /* data */
public:
  FlyingMonster() : Monster(0, 0, 0, 0, 0, 0) {}
  FlyingMonster(int x, int y, int width, int height, int speed, int life)
      : Monster(x, y, width, height, speed, life) {}
  void update() override;
};

#endif /* FLYING_MONSTER_HPP */