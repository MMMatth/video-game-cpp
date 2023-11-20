#include "../include/monster.hpp"
#include "../include/const.hpp"
#include "../include/draw.hpp"
#include "../include/map.hpp"
#include "../include/tile.hpp"
#include <iostream>

Monster::Monster(int x, int y) : m_coord(x, y) { init(); }

void Monster::init() {
  m_width = 16;
  m_height = 30;

  /*Initialize direction, collision, speed, and sprites */
  m_direction = {{"right", false},
                 {"left", false},
                 {"jump", false},
                 {"up", false},
                 {"fall", true}};
  m_collision = {
      {"up", false}, {"down", false}, {"left", false}, {"right", false}};
  m_jumpHeight = 15;
  m_timeJump = 0;
  m_speed = 1;
}

void Monster::update() {
  if (m_direction["jump"] && m_collision["down"]) {
    m_timeJump = 0;
    m_direction["up"] = true;
    m_collision["down"] = false;
  } else if (m_collision["down"]) { // if the player touch the ground
    m_direction["fall"] = false;
  } else { // if the player is in the air
    m_direction["fall"] = true;
  }

  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  if (m_direction["up"] && !m_collision["up"] && m_timeJump < m_jumpHeight) {
    m_timeJump++;
    moveY(-m_speed);
  } else if (m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }
  /* we moove the player */
  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    moveY(m_speed);
  }
  if (m_direction["right"] && !m_collision["right"]) {
    moveX(m_speed);
  }
  if (m_direction["left"] && !m_collision["left"]) {
    moveX(-m_speed);
  }
  if (m_direction["up"] && !m_collision["up"]) {
    moveY(-m_speed);
  }
  if (m_collision["up"] && !m_collision["down"]) {
    m_direction["fall"] = true;
    moveY(m_speed);
  }

  m_collision["up"] = false;
  m_collision["down"] = false;
  m_collision["left"] = false;
  m_collision["right"] = false;
}

void Monster::setCollisionFalse(string key) { m_collision[key] = false; }

void Monster::moveX(int x) { setMonsterX(x + getX()); }

void Monster::moveY(int y) { setMonsterY(y + getY()); }