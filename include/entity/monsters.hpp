#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../item/block.hpp"
#include "../map/map.hpp"
#include "../rendering/entityRender.hpp"
#include "../utils/list.hpp"
#include "flying_monster.hpp"
#include "character.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>

/**
 * @class Monsters
 * @brief Represents a collection of monsters in the game.
 *
 * This class manages a collection of different types of monsters and provides
 * functionality to add, update, and render them.
 */
class Monsters {
private:
  LinkedList<Monster *> *m_flyingMonsters = cons_empty<Monster *>();               // Collection of flying monsters
  LinkedList<Monster *> *m_walkingMonsters = cons_empty<Monster *>();               // Collection of walking monsters
  LinkedList<EntityRender *> *m_flyingMonsterRenderers = cons_empty<EntityRender *>();// Renderers for the monsters
  LinkedList<EntityRender *> *m_walkingMonsterRenderers = cons_empty<EntityRender *>(); // Renderers for the monsters
  const Map m_map;                           // Reference to the game map
 const Character& m_char; // Character

public:
  /**
   * @brief Constructor for Monsters.
   * @param map Reference to the game map.
   * @details Initializes the Monsters collection and adds random flying and
   * walking monsters to it.
   */
  Monsters(const Map &map, const Character& m_char);

  /**
   * @brief Getter for the collection of monsters.
   * @return Linked list containing pointers to monsters.
   */
  LinkedList<Monster *> *getFlyingMonsters() const { return m_flyingMonsters; }

  LinkedList<Monster *> *getWalkingMonsters() const { return m_walkingMonsters; }

  /**
   * @brief Adds a random monster to the collection at a valid position on the
   * map.
   * @param monster Pointer to the monster to be added.
   * @param map Reference to the game map.
   */
  void addRandomMonster(Monster *monster, Map map);

  /**
   * @brief Handles collisions between monsters and the map.
   * @param map Pointer to the game map.
   * @param camX Camera X position.
   * @param camY Camera Y position.
   */
  void collide(Map *map, int camX, int camY);
  /**
   * @brief Renders all monsters on the screen.
   * @param window Reference to the game window.
   * @param sprites Map of sprites for rendering.
   * @param key Key to select the appropriate sprite.
   * @param nbFrame Number of frames for animation.
   */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame);

  /**
   * @brief Updates the state of all monsters.
   */
  void update();

  /**
 * @brief Renders health bars for the monsters.
 * @param window Reference to the game window.
 * @param monsters Linked list of monsters.
 */
  void renderMonstersHealthBars(RenderWindow &window, LinkedList<Monster *> *monsters);

  /**
 * @brief Checks for collision between two rectangles.
 * @param x1 X position of the first rectangle.
 * @param y1 Y position of the first rectangle.
 * @param width1 Width of the first rectangle.
 * @param height1 Height of the first rectangle.
 * @param x2 X position of the second rectangle.
 * @param y2 Y position of the second rectangle.
 * @param width2 Width of the second rectangle.
 * @param height2 Height of the second rectangle.
 * @return True if there is a collision, false otherwise.
 */
 bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) const;

 /**
 * @brief Checks for collisions between the player and monsters.
 * @param m_char Reference to the player character.
 * @param m_monster Pointer to the monster.
 * @return True if there is a collision, false otherwise.
 */
bool checkPlayerMonsterCollision(const Character& m_char, Monster *m_monster) const;


};

#endif