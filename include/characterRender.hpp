#ifndef CHARACTERRENDER_HPP
#define CHARACTERRENDER_HPP

#include "const.hpp"
#include "coord.hpp"
#include "character.hpp"
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
    CharacterRender(Character& character);
    void draw(RenderWindow &window);

private:
    Clock m_clock;
    Character& character;
};



#endif /* CHARACTERRENDER_HPP */
