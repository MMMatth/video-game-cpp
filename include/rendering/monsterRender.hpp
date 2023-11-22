#ifndef MONSTERRENDER_HPP
#define MONSTERRENDER_HPP

#include "../entity/monster.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace sf;

class MonsterRender {
public:
  MonsterRender(Monster &monster);
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites);
  void drawSprite(RenderWindow &window, unordered_map<string, Sprite> &sprites,
                  const string &spriteKey, int frame, int x, int y);

  Monster &m_monster;
  Clock m_clock;
};

#endif /*MONSTERRENDER_HPP*/