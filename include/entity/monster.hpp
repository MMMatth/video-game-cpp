#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "../entity/entity.hpp"
#include "../utils/const.hpp"
#include "../utils/list.hpp"
#include "character.hpp"
#include "../utils/coord.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace sf;

/**
 * @class Monster
 * @brief Represents a generic monster entity in the game.
 *
 * This class is an abstract base class for all monster entities in the game.
 * It inherits common properties and behaviors from the Entity class and defines
 * a pure virtual function 'update' for updating the monster's state and behavior.
*/
class Monster : public Entity {
public:
  /**
   * @brief Constructor for the Monster class.
   * @param x The initial x-coordinate of the monster.
   * @param y The initial y-coordinate of the monster.
   * @param width The width of the monster.
   * @param height The height of the monster.
   * @param speed The movement speed of the monster.
   * @param life The initial life points of the monster.
  */
  Monster(int x, int y, int width, int height, int speed, int life)
      : Entity(x, y, width, height, speed, life) {}
  
  /**
   * @brief Pure virtual function to update the monster's state and behavior.
   * @details This function must be implemented by derived classes to define
   * specific behavior for each type of monster.
  */
  virtual void update(const Character &m_char) = 0;

private:
  /* data */
};

#endif /* MONSTER_HPP */
