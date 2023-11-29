#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "../entity/entity.hpp"
#include "../map/map.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;
using namespace std;

class Map;
/**
 * @class Character
 * @brief Represents a character in the game.
 *
 * This class encapsulates the properties and behaviors of a character in the
 * game, such as position, movement, collisions, and life.
 */
class Character : public Entity {
public:
  Character();
  /* constructor */

  Character(string fileName, bool save);
  /**
   * @brief Parameterized constructor for the Character class.
   * @param x The initial x-coordinate of the character.
   * @param y The initial y-coordinate of the character.
   * @param life The initial life of the character.
   */
  Character(int x, int y, int life, int speed, int width, int height,
            int jumpHeight, int timeJump, bool save);
  /**
   * @brief Loads character information from a CSV file.
   * @param csvPath The path to the CSV file containing character information.
   * @return True if loading is successful, false otherwise.
   */
  bool loadFromCSV(string csvPath);

  /** @brief Initializes the character's properties. */
  void init();
  /* update */
  /** @brief Updates the character's state and behavior. */
  void update();
  void collide(Map *map, int camX, int camY);

  /* getters */
  int getTimeJump() const { return m_timeJump; }
  int getJumpHeight() const { return m_jumpHeight; }

  /* other setters */
  void setTimeJump(int time) { m_timeJump = time; }
  void hit(int damage) { this->m_life -= damage; }
  void heal(int heal) { this->m_life += heal; }

  /* other */
  void reset(bool save, int x, int y,
             string path = string(SAVE_PATH) + string(CHARACTER_SAVE_PATH));
  void save(string path);

private:
  bool m_save;      /** if true the charcater is save in csv */
  int m_timeJump;   /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
};

#endif /* PERSONNAGE_HPP */
