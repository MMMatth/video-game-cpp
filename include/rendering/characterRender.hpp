#ifndef CHARACTERRENDER_HPP
#define CHARACTERRENDER_HPP

#include "../entity/character.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;
using namespace std;

class CharacterRender {
public:
  CharacterRender(Character &character);
  void drawSprite(RenderWindow &window, unordered_map<string, Sprite> &sprites,
                  const string &spriteKey, int frame, int x, int y);
  void renderCharacter(RenderWindow &window,
                       unordered_map<string, Sprite> sprites);
  void renderLife(RenderWindow &window, unordered_map<string, Sprite> sprites,
                  int camX, int camY);
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              int camX, int camY);

private:
  Clock m_clock;
  Character &character;
};

#endif /* CHARACTERRENDER_HPP */
