#ifndef WALKING_MONSTER_HPP
#define WALKING_MONSTER_HPP

#include "monster.hpp"

using namespace std;
using namespace sf;

class WalkingMonster : public Monster {
private:
  int m_timeJump;
  int m_jumpHeight;

public:
  WalkingMonster(int x, int y, int width, int height, int speed, int life,
                 int jumpHeight)
      : Monster(x, y, width, height, speed, life), m_jumpHeight(jumpHeight) {}
  void update() override;
  //   ~WalkingMonster();
};

#endif /* WALKING_MONSTER_HPP */