#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
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

/**
 * @class Character
 * @brief Represents a character in the game.
 *
 * This class encapsulates the properties and behaviors of a character in the game,
 * such as position, movement, collisions, and life.
*/
class Character {
public:
  /**
   * @brief Constructor for the Character class.
   * @param path The path to a file containing character information (used for loading).
  */
  Character(string path);

  /**
   * @brief Parameterized constructor for the Character class.
   * @param x The initial x-coordinate of the character.
   * @param y The initial y-coordinate of the character.
   * @param life The initial life of the character.
  */
  Character(int x, int y, int life);

  /**
   * @brief Loads character information from a CSV file.
   * @param csvPath The path to the CSV file containing character information.
   * @return True if loading is successful, false otherwise.
  */
  bool loadFromCSV(string csvPath);

  /**
   * @brief Initializes the character's properties.
  */
  void init();

  /**
   * @brief Destructor for the Character class.
  */
  // ~Personnage();
  
  /**
   * @brief Updates the character's state and behavior.
  */
  void update();

  /**
   * @brief Getter function for retrieving the direction of the character.
   * @return A map containing booleans for different directions (fall, jump, up, right, left).
  */
  map<string, bool> getDirection() { return m_direction; }

  /**
   * @brief Getter function for retrieving collision information of the character.
   * @return A map containing booleans for collision in different directions (up, down, right, left).
  */
  map<string, bool> getCollision() { return m_collision; }

  /**
   * @brief Getter function for retrieving the height of the character.
   * @return The height of the character.
  */
  int getHeight() { return m_height; }

  /**
   * @brief Getter function for retrieving the width of the character.
   * @return The width of the character.
  */
  int getWidth() { return m_width; }

  /**
   * @brief Getter function for retrieving the x-coordinate of the character.
   * @return The x-coordinate of the character.
  */
  int getX() { return m_coord.getX(); }

  /**
   * @brief Getter function for retrieving the y-coordinate of the character.
   * @return The y-coordinate of the character.
  */
  int getY() { return m_coord.getY(); }

  /**
   * @brief Getter function for retrieving the time elapsed during a jump.
   * @return The time elapsed during the jump.
  */
  int getTimeJump() { return m_timeJump; }

  /**
   * @brief Getter function for retrieving the limit of time for a jump.
   * @return The limit of time for a jump.
  */
  int getJumpHeight() { return m_jumpHeight; }

  /**
   * @brief Getter function for retrieving the speed of the character.
   * @return The speed of the character.
  */
  int getVitesse() { return m_speed; }

  /**
   * @brief Getter function for retrieving the life of the character.
   * @return The life of the character.
  */
  int getLife() { return m_life; }

  /**
   * @brief Setter function for setting the falling state of the character.
   * @param falling True if the character is falling, false otherwise.
  */
  void setFalling(bool falling) { m_direction["fall"] = falling; }

  /**
   * @brief Setter function for setting the jumping state of the character.
   * @param jumping True if the character is jumping, false otherwise.
  */
  void setJumping(bool jumping) { m_direction["jump"] = jumping; }

  /**
   * @brief Setter function for setting the going-up state of the character.
   * @param inUp True if the character is going up, false otherwise.
  */
  void setGoingUp(bool inUp) { m_direction["up"] = inUp; }

  /**
   * @brief Setter function for setting the going-right state of the character.
   * @param inRight True if the character is going right, false otherwise.
  */
  void setGoingRight(bool inRight) { m_direction["right"] = inRight; }

  /**
   * @brief Setter function for setting the going-left state of the character.
   * @param inLeft True if the character is going left, false otherwise.
  */
  void setGoingLeft(bool inLeft) { m_direction["left"] = inLeft; }

  /**
   * @brief Setter function for setting collision state in a specific direction.
   * @param key The direction (up, down, right, left).
   * @param value True if there is collision, false otherwise.
  */
  void setCollision(string key, bool value) { this->m_collision[key] = value; }

  /**
   * @brief Setter function for setting collision state to false except for a specific direction.
   * @param key The direction for which collision state should be true.
  */
  void setCollisionFalseExcept(string key);
  
  /**
   * @brief Setter function for setting the x-coordinate of the character.
   * @param x The x-coordinate of the character.
  */
  void setX(int x) { m_coord.setX(x); }

  /**
   * @brief Setter function for setting the y-coordinate of the character.
   * @param y The y-coordinate of the character.
  */
  void setY(int y) { m_coord.setY(y); }

  /**
   * @brief Setter function for setting the time elapsed during a jump.
   * @param time The time elapsed during the jump.
  */
  void setTimeJump(int time) { m_timeJump = time; }

  /**
   * @brief Setter function for setting the width of the character.
   * @param width The width of the character.
  */
  void setWidth(int width) { this->m_width = width; }

  /**
   * @brief Setter function for setting the height of the character.
   * @param height The height of the character.
  */
  void setHeight(int height) { this->m_height = height; }

  /**
   * @brief Setter function for setting the life of the character.
   * @param life The life of the character.
  */
  void setLife(int life) { this->m_life = life; }

  /**
   * @brief Inflicts damage to the character.
   * @param damage The amount of damage to be inflicted.
  */
  void hit(int damage) { this->m_life -= damage; }

  /**
   * @brief Heals the character.
   * @param heal The amount of healing to be applied.
  */
  void heal(int heal) { this->m_life += heal; }

  /**
   * @brief Moves the character horizontally.
   * @param x The amount to move the character along the x-axis.
  */
  void mooveX(int x);

  /**
   * @brief Moves the character vertically.
   * @param y The amount to move the character along the y-axis.
  */
  void mooveY(int y);

  /**
   * @brief Saves the character state to a file.
   * @param path The path to the file where the character state will be saved.
  */
  void save(string path);

private:
  bool m_save;                   /** if true the charcater is save in csv */
  Coord m_coord;                 /** coord in x y of the character*/
  map<string, bool> m_direction; /** Contains booleans for states: fall, jump,
                                    up, right, left. */
  map<string, bool>
      m_collision; /** Contains booleans for collision : up, down, right, left*/
  int m_timeJump;  /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
  int m_width;      /** width of the character */
  int m_height;     /** height of the character */
  int m_speed;      /** speed */
  int m_life;       /** life of the character */
};

#endif /* PERSONNAGE_HPP */
