#ifndef WALKING_MONSTER_HPP
#define WALKING_MONSTER_HPP

#include "monster.hpp"

using namespace std;
using namespace sf;

/**
 * @class WalkingMonster
 * @brief Represents a walking type of monster in the game.
 *
 * This class inherits from the Monster class and provides specific
 * implementation for a walking type of monster, including walking behavior.
*/
class WalkingMonster : public Monster {
private:
  int m_timeJump; // Elapsed time during the jump
  int m_jumpHeight; // The limit of time jump

public:
  /**
   * @brief Parameterized constructor for WalkingMonster.
   * @param x The initial x-coordinate of the monster.
   * @param y The initial y-coordinate of the monster.
   * @param width The width of the monster.
   * @param height The height of the monster.
   * @param speed The movement speed of the monster.
   * @param life The life points of the monster.
   * @param jumpHeight The limit of time for jumping.
  */
  WalkingMonster(int x, int y, int width, int height, int speed, int life,
                 int jumpHeight)
      : Monster(x, y, width, height, speed, life), m_jumpHeight(jumpHeight) {}
  
  /**
   * @brief Updates the state and behavior of the walking monster.
   * @details This function is called during each game update to handle the
   * walking monster's behavior.
  */
  void update() override;
  
  // Destructor (if needed)
  //   ~WalkingMonster();
};

#endif /* WALKING_MONSTER_HPP */