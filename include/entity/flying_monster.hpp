#ifndef FLYING_MONSTER_HPP
#define FLYING_MONSTER_HPP

#include "monster.hpp"

using namespace std;
using namespace sf;

/**
 * @class FlyingMonster
 * @brief Represents a flying monster entity in the game.
 *
 * This class inherits from the Monster class and implements the 'update'
 * function to define the specific behavior of a flying monster.
*/
class FlyingMonster : public Monster {

public:
  /**
   * @brief Default constructor for FlyingMonster.
   * @details Initializes the FlyingMonster with default values.
  */
  FlyingMonster() : Monster(0, 0, 0, 0, 0, 0) {}

  /**
   * @brief Parameterized constructor for FlyingMonster.
   * @param x The initial x-coordinate of the flying monster.
   * @param y The initial y-coordinate of the flying monster.
   * @param width The width of the flying monster.
   * @param height The height of the flying monster.
   * @param speed The movement speed of the flying monster.
   * @param life The initial life points of the flying monster.
  */
  FlyingMonster(int x, int y, int width, int height, int speed, int life)
      : Monster(x, y, width, height, speed, life) {}
      
  /**
   * @brief Function to update the state and behavior of the flying monster.
   * @details This function is called to update the flying monster's position,
   * animation, or any other specific behavior.
  */
  void update() override;

private:
  /* data */
};

#endif /* FLYING_MONSTER_HPP */