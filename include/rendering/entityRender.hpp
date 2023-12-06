#ifndef ENTITYRENDER_HPP
#define ENTITYRENDER_HPP

#include "../entity/entity.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

using namespace std;
using namespace sf;

/**
 * @class EntityRender
 * @brief Responsible for rendering an entity in the game.
 *
 * This class handles the rendering of an entity, including animation and static
 * rendering.
 */
class EntityRender {
private:
  Clock m_clock;    /**< Clock used for controlling animations. */
  Entity &m_entity; /**< Reference to the entity being rendered. */

public:
  /**
   * Parameterized constructor for EntityRender.
   * @param entity The entity to be rendered.
   */
  EntityRender(Entity &entity);

  /**
   * Draw the animated entity on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the animations.
   * @param spriteKey Key to identify the sprite in the sprites map.
   * @param frame Current frame of the animation.
   * @param x X-coordinate of the entity.
   * @param y Y-coordinate of the entity.
   */
  void drawEnityAnimation(RenderWindow &window,
                          unordered_map<string, Sprite> &sprites,
                          const string &spriteKey, int frame, int x, int y);

  /**
   * Draw the animated flying monster entity on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the animations.
   * @param spriteKey Key to identify the sprite in the sprites map.
   * @param frame Current frame of the animation.
   * @param x X-coordinate of the entity.
   * @param y Y-coordinate of the entity.
   */
  void drawEnityAnimationMonster(RenderWindow &window,
                                 unordered_map<string, Sprite> &sprites,
                                 const string &spriteKey, int frame, int x,
                                 int y);

  /**
   * Draw the static entity on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the static images.
   * @param spriteKey Key to identify the sprite in the sprites map.
   * @param x X-coordinate of the entity.
   * @param y Y-coordinate of the entity.
   */
  void drawEntityStatic(RenderWindow &window,
                        unordered_map<string, Sprite> &sprites,
                        const string &spriteKey, int x, int y);

  /**
   * Render the entity on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the animations or static images.
   * @param key Key to identify the sprite in the sprites map.
   * @param nbFrame Current frame of the animation (for animated entities).
   */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame);
  
   /**
   * Get a reference to the underlying entity.
   * @return Reference to the entity being rendered.
   */
  Entity& getEntity() { return m_entity; }
};

#endif /* ENTITYRENDER_HPP */