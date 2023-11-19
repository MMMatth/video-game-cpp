#ifndef MONSTERRENDER_HPP
#define MONSTERRENDER_HPP

#include "../include/monster.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace sf;

class  MonsterRender{
public:
    MonsterRender(Monster &monster);
    void draw(RenderWindow& window, Monster& monster);
    
private:
    Clock m_clock;
    Monster &m_monster;
};

#endif /*MONSTERRENDER_HPP*/