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

/**
 * @class Map
 * @brief Represents the game map.
 *
 * This class manages the game map, including loading, saving, collision
 * detection, and modification of tiles.
 */
class Map {
public:
  /* constructor */

  /**
   * Parameterized constructor for Map.
   * @param path The path to a file containing map information (used for
   * loading).
   */
  Map(string path);

  /**
   * Parameterized constructor for Map.
   * @param height The height of the map.
   * @param width The width of the map.
   */
  Map(int height, int width);

  /* destructor */
  void clear();

  /* init function */

  /**
   * Loads map information from a CSV file.
   * @param pathFile The path to the CSV file containing map information.
   * @return True if loading is successful, false otherwise.
   */
  bool loadFromCSV(string pathFile);

  /**
   * Initializes the map dimensions from a CSV file.
   * @param pathFile The path to the CSV file containing map information.
   * @return True if initialization is successful, false otherwise.
   */
  bool initLegthFromCSV(string pathFile);

  /* getters */
  vector<vector<Tile>> getMap() const { return m_map; }
  Coord get_working_area() const { return m_workingAreaCoord; }
  int get_height() const { return m_height - 1; }
  int get_width() const { return m_width - 1; }
  Tile get_tile(int y_tile, int x_tile) const { return m_map[y_tile][x_tile]; }
  Tile *find_tile(int x, int y);
  int get_cam_width() const { return m_workingAreaWidth; }
  int get_cam_height() const { return m_workingAreaHeight; }
  bool isBreaking(int mouseX, int mouseY);
  Clock getBreakingClock(int mouseX, int mouseY);
  /* setters */
  void resetBreakingClock(int mouseX, int mouseY);
  void setIsBreaking(bool isBreaking, int mouseX, int mouseY);

  /* other*/
  void reset(string path);

  /**
   * Saves the map to a file.
   * @param path The path to the file where the map will be saved.
   */
  void save(string path);

  /**
   * Handles collision with an entity in the specified camera position.
   * @param entity The entity for collision detection.
   * @param camX The x-coordinate of the camera position.
   * @param camY The y-coordinate of the camera position.
   */
  void collide(Entity *entity, int camX, int camY);

  /**
   * Handles collision with an entity.
   * @param entity The entity for collision detection.
   */
  void collide(Entity *entity);

  /**
   * Chooses a tile based on a character and coordinates.
   * @param c The character representing the type of the tile.
   * @param x The x-coordinate of the tile.
   * @param y The y-coordinate of the tile.
   * @return The chosen tile.
   */
  Tile chooseTile(string c, int x, int y, bool isBackground);

  /**
   * Adds a tile to the map at the specified coordinates.
   * @param block The block to be added as a tile.
   * @param mouseX The x-coordinate of the mouse position.
   * @param mouseY The y-coordinate of the mouse position.
   */
  void add_tile(Block block, int mouseX, int mouseY, bool isBackground);

  /**
   * Removes a tile from the map at the specified coordinates.
   * @param x The x-coordinate of the tile.
   * @param y The y-coordinate of the tile.
   */
  void supr_tile(int x, int y);

  /**
   * Updates the map based on camera coordinates.
   * @param camX The x-coordinate of the camera.
   * @param camY The y-coordinate of the camera.
   */
  void update(int camX, int camY);

  /**
   * Checks if an entity collides with a solid block on the map.
   * @param entity The entity for collision detection.
   * @return True if there is a collision with a solid block, false otherwise.
   */
  bool collidesWithSolidBlock(Entity *entity);

  /**
   * Converts the map to a string representation.
   * @return The string representation of the map.
   */
  string toString();

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
