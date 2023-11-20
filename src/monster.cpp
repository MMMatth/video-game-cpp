#include "../include/monster.hpp"
#include "../include/const.hpp"
#include "../include/draw.hpp"
#include "../include/map.hpp"
#include "../include/tile.hpp"
#include <iostream>

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