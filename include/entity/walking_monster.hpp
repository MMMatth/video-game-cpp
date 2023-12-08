#ifndef WALKING_MONSTER_HPP
#define WALKING_MONSTER_HPP

#include "../map/map.hpp"
#include "monster.hpp"

using namespace std;
using namespace sf;

class WalkingMonster : public Monster {
private:
  int m_timeJump;   // Elapsed time during the jump
  int m_jumpHeight; // The limit of time jump
<<<<<<< HEAD
  // const Map &m_map;

public:
  WalkingMonster() : Monster(0, 0, 0, 0, 0, 0, 0) {}
  WalkingMonster(int x, int y, int width, int height, int speed, int life,
                 int maxLife, int jumpHeight)
      : Monster(x, y, width, height, speed, life, maxLife),
        m_jumpHeight(jumpHeight) {}
  ~WalkingMonster() {}
=======
  const Map &m_map;

public:
  WalkingMonster(int x, int y, int width, int height, int speed, int life,
                 int maxLife, int jumpHeight, const Map &map)
      : Monster(x, y, width, height, speed, life, maxLife),
        m_jumpHeight(jumpHeight), m_map(map) {}
>>>>>>> b5b03dc (i modified monster a bit)

  /**
   * @brief Updates the state and behavior of the walking monster.
   * @details This function is called during each game update to handle the
   * walking monster's behavior.
   */
  void update(const Character &m_char) override;
<<<<<<< HEAD
=======

  // Destructor (if needed)
  //   ~WalkingMonster();
>>>>>>> b5b03dc (i modified monster a bit)
};

#endif /* WALKING_MONSTER_HPP */