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
protected:
  Clock m_clock;    /**< Clock used for controlling animations. */
  Entity &m_entity; /**< Reference to the entity being rendered. */

public:
  EntityRender(Entity &entity);

  void drawEnityAnimation(RenderWindow &window,
                          unordered_map<string, Sprite> &sprites,
                          const string &spriteKey, int frame, int x, int y);

  void drawEnityAnimationMonster(RenderWindow &window,
                                 unordered_map<string, Sprite> &sprites,
                                 const string &spriteKey, int frame, int x,
                                 int y);

  void drawEntityStatic(RenderWindow &window,
                        unordered_map<string, Sprite> &sprites,
                        const string &spriteKey, int x, int y);

  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame);

  Entity &getEntity() { return m_entity; }
};

#endif /* ENTITYRENDER_HPP */