#ifndef MONSTER_HPP
#define MONSTER_HPP

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

class Monster {
public:
    Monster(int x, int y, Texture& textureMonster);
    void init(Texture& textureMonster);
    void update();

    /* Getters */
    int getHeight() { return m_height; }
    int getWidth() { return m_width; }
    int getX() { return m_coord.getX(); }
    int getY() { return m_coord.getY(); }
    map<string, bool> getDirection() { return m_direction; }
    map<string, bool> getCollision() { return m_collision; }
    int getSpeed() { return m_speed; }
    unordered_map<string, Sprite> getSprites() { return sprites; }

    /* Setters */
    void setCollision(string key, bool value) { this->m_collision[key] = value; }
    void setMonsterX(int x) { m_coord.setX(x); }
    void setMonsterY(int y) { m_coord.setY(y); }
    void setCollisionFalse(string key);

    /*Move Monster along*/ 
    void moveX(int x);
    void moveY(int y);

private:
    Coord m_coord;  /*Monster's position*/

    map<string, bool> m_direction;           /*Monster's movement direction*/
    map<string, bool> m_collision;           /*Monster's collision status*/
    unordered_map<string, Sprite> sprites;  /*Monster's sprites for animations*/

    int m_life;     /*Monster's life points (if applicable)*/
    int m_height;   /*Monster's height*/
    int m_width;    /*Monster's width*/
    int m_speed;    /*Monster's movement speed*/
    Texture& m_textureMonster;  /*Reference to the texture used for Monster*/

};

#endif /* MONSTER_HPP */
