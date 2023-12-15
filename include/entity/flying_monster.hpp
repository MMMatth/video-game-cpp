#ifndef FLYING_MONSTER_HPP
#define FLYING_MONSTER_HPP

#include "monster.hpp"

using namespace std;
using namespace sf;

class FlyingMonster : public Monster {

public:
  FlyingMonster() : Monster(0, 0, 0, 0, 0, 0, 0, (string) "FLYING_MONSTER") {}

  FlyingMonster(int x, int y, int width, int height, int speed, int life,
                int maxLife)
      : Monster(x, y, width, height, speed, life, maxLife,
                (string) "FLYING_MONSTER") {}

  void update(const Character &m_char) override;

private:
  /* data */
};

#endif /* FLYING_MONSTER_HPP */