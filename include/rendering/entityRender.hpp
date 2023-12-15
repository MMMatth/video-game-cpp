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

/** @brief Renders an entity. */
class EntityRender {
protected:
  Clock m_clock;    /**< Clock used for controlling animations. */
  Entity &m_entity; /**< Reference to the entity being rendered. */

public:
  /** @brief constructor for entity render */
  EntityRender(Entity &entity);

  /** @brief draw the entity with an animation */
  void drawEnityAnimation(RenderWindow &window,
                          unordered_map<string, Sprite> &sprites,
                          const string &spriteKey, int frame, int x, int y);

  /** @brief draw the entity without animation */
  void drawEntityStatic(RenderWindow &window,
                        unordered_map<string, Sprite> &sprites,
                        const string &spriteKey, int x, int y);

  /** @brief render the character depend the entity direction */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame);

  /** @brief get the entity */
  Entity &getEntity() { return m_entity; }
};

#endif /* ENTITYRENDER_HPP */