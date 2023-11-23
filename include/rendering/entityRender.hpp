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

class EntityRender {
private:
  Clock m_clock;
  Entity &m_entity;

public:
  EntityRender(Entity &entity);
  void drawEnityAnimation(RenderWindow &window,
                          unordered_map<string, Sprite> &sprites,
                          const string &spriteKey, int frame, int x, int y);
  void drawEntityStatic(RenderWindow &window,
                        unordered_map<string, Sprite> &sprites,
                        const string &spriteKey, int x, int y);
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame);
};

#endif /* ENTITYRENDER_HPP */