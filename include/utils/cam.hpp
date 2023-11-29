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
 * @brief The Cam class represents a camera in the game world.
 *
 * The camera is used to define the player's view in the game by setting
 * a position and dimensions. It can be updated to follow a character
 * or adapt to a certain area of the map.
 */
class Cam {
private:
  bool m_save;               /**< Condition for saving */
  Coord m_pos;               /**< Camera position */
  int m_width = CAM_WIDTH;   /**< Camera width */
  int m_height = CAM_HEIGHT; /**< Camera height */

public:
  Cam();

  Cam(int x, int y, bool save);

  Cam(string csvPath, bool save);

  bool loadFromCSV(string csvPath);

  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);

  int getX() { return m_pos.getX(); }

  /**
   * @brief Gets the vertical position of the camera.
   *
   * @return Vertical position of the camera.
   */
  int getY() { return m_pos.getY(); }
  int getTopLeftX() { return m_pos.getX() - m_width / 2; }
  int getTopLeftY() { return m_pos.getY() - m_height / 2; }

  /**
   * @brief Gets the camera position as coordinates.
   *
   * @return Coord representing the camera position.
   */
  Coord getPos() { return m_pos; }

  /**
   * @brief Gets the width of the camera.
   *
   * @return Width of the camera.
   */
  int getWidth() { return m_width; }

  /**
   * @brief Gets the height of the camera.
   *
   * @return Height of the camera.
   */
  int getHeight() { return m_height; }

  /**
   * @brief Sets the horizontal position of the camera.
   *
   * @param x New horizontal position of the camera.
   */
  void setX(int x) { m_pos.setX(x); }

  /**
   * @brief Sets the vertical position of the camera.
   *
   * @param y New vertical position of the camera.
   */
  void setY(int y) { m_pos.setY(y); }

  /**
   * @brief Sets the camera position using coordinates.
   *
   * @param pos New camera position.
   */
  void setPos(Coord pos) { m_pos = pos; }

  /**
   * @brief Resets the camera position.
   *
   * @param x New horizontal position.
   * @param y New vertical position.
   */
  void reset(int x, int y);

  /**
   * @brief Saves camera data to a CSV file.
   *
   * @param csvPath Path to the CSV file.
   */
  void save(string csvPath);
};

#endif // CAM_HPP