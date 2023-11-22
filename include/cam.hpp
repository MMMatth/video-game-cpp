#ifndef CAM_HPP
#define CAM_HPP

#include "const.hpp"
#include "coord.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

/**
 * @class Cam
 * @brief Represents the camera in the game world.
 * The camera is responsible for controlling the view and position within the game.
 */
class Cam {
private:
  bool m_save; /*Indicates whether the camera state should be saved.*/
  Coord m_pos; /*The position of the camera.*/
  int m_width = CAM_WIDTH; /*The width of the camera view.*/
  int m_height = CAM_HEIGHT; /*The height of the camera view.*/

public:
  /**
   * @brief Default constructor for the Cam class.
  */
  Cam();

  /**
   * @brief Parameterized constructor for the Cam class.
   * @param x The initial x-coordinate of the camera.
   * @param y The initial y-coordinate of the camera.
  */
  Cam(int x, int y);

  /**
   * @brief Constructor for the Cam class that loads camera state from a CSV file.
   * @param csvPath The path to the CSV file containing camera state information.
  */
  Cam(string csvPath);

  /**
   * @brief Loads camera state from a CSV file.
   * @param csvPath The path to the CSV file containing camera state information.
   * @return True if the loading is successful, false otherwise.
  */
  bool loadFromCSV(string csvPath);

  /**
   * @brief Updates the camera position based on the character's position and the window dimensions.
   * @param charX The x-coordinate of the character.
   * @param charY The y-coordinate of the character.
   * @param charW The width of the character.
   * @param charH The height of the character.
   * @param mapWidth The width of the game map.
   * @param mapHeight The height of the game map.
   * @param window The RenderWindow object representing the game window.
  */
  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);
  
  /**
   * @brief Getter function for retrieving the x-coordinate of the camera.
   * @return The x-coordinate of the camera.
  */
  int getX() { return m_pos.getX(); }

  /**
   * @brief Getter function for retrieving the y-coordinate of the camera.
   * @return The y-coordinate of the camera.
  */
  int getY() { return m_pos.getY(); }

  /**
   * @brief Getter function for retrieving the position of the camera.
   * @return The position of the camera as a Coord object.
  */
  Coord getPos() { return m_pos; }

  /**
   * @brief Getter function for retrieving the width of the camera view.
   * @return The width of the camera view.
   */
  int getWidth() { return m_width; }

  /**
   * @brief Getter function for retrieving the height of the camera view.
   * @return The height of the camera view.
  */
  int getHeight() { return m_height; }

  /**
   * @brief Setter function for setting the x-coordinate of the camera.
   * @param x The x-coordinate of the camera.
  */
  void setX(int x) { m_pos.setX(x); }

  /**
   * @brief Setter function for setting the y-coordinate of the camera.
   * @param y The y-coordinate of the camera.
  */
  void setY(int y) { m_pos.setY(y); }

  /**
   * @brief Setter function for setting the position of the camera.
   * @param pos The position of the camera as a Coord object.
  */
  void setPos(Coord pos) { m_pos = pos; }

  /**
   * @brief Resets the camera to a specified position.
   * @param x The x-coordinate of the new camera position.
   * @param y The y-coordinate of the new camera position.
   */
  void reset(int x, int y);

  /**
   * @brief Saves the camera state to a CSV file.
   * @param csvPath The path to the CSV file where the camera state will be saved.
  */
  void save(string csvPath);
};

#endif