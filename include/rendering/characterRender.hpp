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
  /** @brief constructor for the character render */
  CharacterRender(Character &character);

  /** @brief render the life in heart */
  void renderLifeBar(RenderWindow &window,
                     unordered_map<string, Sprite> &sprites, int camX,
                     int camY);
};

#endif // CHARACTER_RENDER_HPP