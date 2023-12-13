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

/** @brief a class who represent the camera in the game */
class Cam {
private:
  bool m_save;               /**< Condition for saving */
  Coord m_pos;               /**< Camera position */
  int m_width = CAM_WIDTH;   /**< Camera width */
  int m_height = CAM_HEIGHT; /**< Camera height */

public:
  /** @brief default constructor */
  Cam();

  /** @brief constructor with param */
  Cam(int x, int y, bool save);

  /** @brief constructor with csv */
  Cam(string csvPath, bool save);

  /** @brief a function who load the camera from a csv file
   * @param csvPath the path of the csv file
   */
  bool loadFromCSV(string csvPath);

  /** @brief a function who update the camera with the char pos */
  void update(int charX, int charY, int charW, int charH, int mapWidth,
              int mapHeight, RenderWindow &window);

  /** @brief function who get the camera x position (centrer of the camera) */
  int getX() { return m_pos.getX(); }

  /** @brief function who get the camera y position (centrer of the camera) */
  int getY() { return m_pos.getY(); }

  /** @brief function who get the camera x position (top left of the camera)*/
  int getTopLeftX() { return m_pos.getX() - m_width / 2; }

  /** @brief function who get the camera y position (top left of the camera)*/
  int getTopLeftY() { return m_pos.getY() - m_height / 2; }

  /** @brief function who get the camera pos (center of the camera) */
  Coord getPos() { return m_pos; }

  /** @brief function who get the camera width */
  int getWidth() { return m_width; }

  /** @brief function who get the camera height */
  int getHeight() { return m_height; }

  /** @brief function who set the camera x */
  void setX(int x) { m_pos.setX(x); }

  /** @brief function who set the camera y */
  void setY(int y) { m_pos.setY(y); }

  /** @brief function who set the camera pos */
  void setPos(Coord pos) { m_pos = pos; }

  /** @brief function who reset camera
   * @param x the x coord (in pixel) of the camera
   * @param y the y coord (in pixel) of the camera
   */
  void reset(int x, int y);

  /** @brief function who save the camera in a csv file
   * @param csvPath the path of the csv file
   */
  void save(string csvPath);
};

#endif // CAM_HPP