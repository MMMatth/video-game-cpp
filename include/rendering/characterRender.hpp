#ifndef CHARACTER_RENDER_HPP
#define CHARACTER_RENDER_HPP

#include "../entity/character.hpp"
#include "entityRender.hpp"

using namespace std;

class CharacterRender : public EntityRender

{
private:
  /* data */
public:
  CharacterRender(Character &character) : EntityRender(character) {}
  void renderLifeBar(RenderWindow &window,
                     unordered_map<string, Sprite> &sprites, int camX,
                     int camY) {
    int life = 10;
    int entire_heart = life / 2;
    int half_heart = life % 2;
    int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
    int y = camY + CAM_HEIGHT / 2 - INVENTORY_TILE_SIZE * 2 - 20;

    for (int i = 0; i < 10; i++) {
      drawSprites(x + i * 15, y, sprites["BLACK_HEART"], &window, 15, 15);
    }
    for (int i = 0; i < entire_heart; i++) {
      drawSprites(x + i * 15, y, sprites["HEART"], &window, 15, 15);
    }
    for (int i = half_heart; i < entire_heart + half_heart; i++) {
      drawSprites(x + i * 15, y, sprites["HALF_HEART"], &window, 15, 15);
    }
  }
};

#endif // CHARACTER_RENDER_HPP