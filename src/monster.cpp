#include "../include/monster.hpp"
#include "../include/draw.hpp"
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/map.hpp"
#include <iostream>


Monster::Monster(int x, int y, Texture& textureMonster) : m_coord(x, y), m_textureMonster(textureMonster) {
    init(m_textureMonster);
}

void Monster::init(Texture& textureMonster) {
    m_width = 16;
    m_height = 30;

    /*Initialize direction, collision, speed, and sprites */
    m_direction = {{"right", true}, {"left", true}};
    m_collision = {{"up", false}, {"down", false}, {"left", false}, {"right", false}};
    m_speed = 1;
    
    vector<string> moveNames = {"moveLeft", "moveRight"};
    for (string& moveName : moveNames) {
       int x = 0;
        if(moveName == "moveLeft"){
          for (int i = 1; i <= 3; i++) {
            string spriteName = moveName + to_string(i);
            sprites[spriteName].setTexture(textureMonster);
            sprites[spriteName].setTextureRect(IntRect(x, 32, 32, 32));
            sprites[spriteName].setPosition(m_coord.getX(), m_coord.getY());
            x += 32;
          }
        }else if(moveName == "moveRight"){
          for (int i = 1; i <= 3; i++) {
            string spriteName = moveName + to_string(i);
            sprites[spriteName].setTexture(textureMonster);
            sprites[spriteName].setTextureRect(IntRect(x, 64, 32, 32));
            sprites[spriteName].setPosition(m_coord.getX(), m_coord.getY());
            x += 32;
          }
        }
    }
    
}

void Monster::update() {
    vector<string> moveNames = {"moveLeft", "moveRight"};
    for (string& moveName : moveNames) {
        int x = 0;
        for (int i = 1; i <= 3; i++) {
            string spriteName = moveName + to_string(i);
            sprites[spriteName].setPosition(m_coord.getX(), m_coord.getY());
        }
    }
    /*Check movement direction and collision for updates*/
    if (m_direction["right"] && !m_collision["right"]) {
        m_direction["left"] = false;
        setCollisionFalse("left");
        moveX(m_speed); 
    }else{
        m_direction["left"] = true;
    }
    if (m_direction["left"] && !m_collision["left"]) {
        m_direction["right"] = false;
        setCollisionFalse("right");
        moveX(-m_speed); 
    }else{
        m_direction["right"] = true;
    }
    
}

void Monster::setCollisionFalse(string key) {
  m_collision[key] = false;
}

void Monster::moveX(int x) { setMonsterX(x + getX()); }

void Monster::moveY(int y) { setMonsterY(y + getY()); }