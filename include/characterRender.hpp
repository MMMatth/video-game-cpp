#ifndef CHARACTERRENDER_HPP
#define CHARACTERRENDER_HPP

#include "character.hpp"
#include "const.hpp"
#include "coord.hpp"
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
                  const string &spriteKey, int frame);
  void draw(RenderWindow &window, unordered_map<string, Sprite> sprites);

private:
  Clock m_clock;
  Character &character;
};

#endif /* CHARACTERRENDER_HPP */
