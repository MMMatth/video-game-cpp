#ifndef MAP_HPP
#define MAP_HPP

#include "../entity/character.hpp"
#include "../entity/entity.hpp"
#include "../item/block.hpp"
#include "../utils/const.hpp"
#include "mapGenerator.hpp"
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Map {
public:
  /** @brief map constructor depending on the save condition
   * @param path the path to the map file
   * @param save the save condition
   */
  Map(string path, bool save);

  /** @brief map constructor (void map)*/
  Map(int height, int width, bool save);

  /** @brief  default constructor*/
  Map();

  /** @brief Initializes the map data from a CSV file.
   * @param pathFile The path to the CSV file containing map information.
   * @return True if initialization is successful, false otherwise.
   */
  bool loadFromCSV(string pathFile);

  /** @brief function to get the coord of the working area*/
  Coord getCoordWorkingArea() const { return m_workingAreaCoord; }

  /** @brief function to get the width of the working area*/
  int getWorkingAreaWidth() const { return m_workingAreaWidth; }

  /** @brief function to get the height of the working area*/
  int getWorkingAreaHeight() const { return m_workingAreaHeight; }

  /** @brief function to get the width of the map*/
  int getHeight() const { return m_height - 1; }

  /** @brief function to get the height of the map*/
  int getWidth() const { return m_width - 1; }

  /** @brief function to get a tile in the map
   * @param y_tile the y coord of the tile (in tile)
   * @param x_tile the x coord of the tile (in tile)
   */
  Tile get_tile(int y_tile, int x_tile) const { return m_map[y_tile][x_tile]; }

  /** @brief function to get a tile in the map
   * @param x the x coord in the game (in pixel)
   * @param y the y coord in the game (in pixel)
   */
  Tile *find_tile(int x, int y);

  /** @brief function to know if a block is in a breaking phase
   * @param mouseX the x coord of the mouse (in pixel)
   * @param mouseY the y coord of the mouse (in pixel)
   */
  bool isBreaking(int mouseX, int mouseY);

  /** @brief function to get the clock of a breaking block
   * @param mouseX the x coord of the mouse (in pixel)
   * @param mouseY the y coord of the mouse (in pixel)
   */
  Clock getBreakingClock(int mouseX, int mouseY);

  /** @brief function tu reset a breaking clock
   * @param mouseX the x coord of the mouse (in pixel)
   * @param mouseY the y coord of the mouse (in pixel)
   */
  void resetBreakingClock(int mouseX, int mouseY);

  /** @brief function to set the breaking condition of a block
   * @param isBreaking the breaking condition
   * @param mouseX the x coord of the mouse (in pixel)
   * @param mouseY the y coord of the mouse (in pixel)
   */
  void setIsBreaking(bool isBreaking, int mouseX, int mouseY);

  /** @brief to reset the map (generate a new one)
   * @param path the path to the map file (void map
   */
  void reset(string path);

  /** @brief Saves the map to a file.
   * @param path The path to the file where the map will be saved.
   */
  void save(string path);

  /** @brief Handles collision with an entity in the working area.
   * @param entity The entity for collision detection.
   */
  void collide(Entity *entity);

  /** @brief function who return if whe have a collision*/
  bool isCollide(Entity *entity);

  /** @brief to get the title depending the block id*/
  Tile chooseTile(string blockId, int x, int y, bool isBackground);

  /** @brief function to add a tile
   * @param block the block to add
   * @param x the x coord of the tile  (in pixel)
   * @param y the y coord of the tile (in pixel)
   * @param isBackground the condition of the tile
   */
  void add_tile(Block block, int x, int y, bool isBackground);

  /** @brief function to remove a tile
   * @param x the x coord of the tile (in pixel)
   * @param y the y coord of the tile (in pixel)
   */
  void remove_tile(int x, int y);

  /** @brief function to update the working area
   * @param camX The x-coordinate of the camera.
   * @param camY The y-coordinate of the camera.
   */
  void update(int camX, int camY);

private:
  bool m_save;                /** condition for the save*/
  vector<vector<Tile>> m_map; /**  2D vector contain tile */
  Coord m_workingAreaCoord;   /** coord x,y of the tile in top left */
  int m_workingAreaWidth;     /** amout of tile in the cam in x*/
  int m_workingAreaHeight;    /** amout of tile in the cam in y*/
  int m_width;                /** map width in block */
  int m_height;               /** map height in block */
};

#endif /* MAP_HPP */
