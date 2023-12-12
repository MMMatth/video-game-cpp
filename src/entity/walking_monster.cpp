#include "../../include/entity/walking_monster.hpp"

void WalkingMonster::update(const Character &m_char) {
  int deltaX = m_char.getX() - getX() - DISTANCEMONSTERPLAYER;
  int deltaY = m_char.getY() - getY() - DISTANCEMONSTERPLAYER;

  float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

  float directionX = deltaX / distance;
  float directionY = deltaY / distance;

  bool isRight = m_char.getX() > getX();
  m_direction["right"] = isRight;
  m_direction["left"] = !isRight;

  if (distance <= ATTACKDISTANCE && !m_collision[isRight ? "right" : "left"]) {
    if (m_char.getX() - DISTANCEMONSTERPLAYER > getX()) {
      m_direction["right"] = true;
      m_direction["left"] = false;
      moveX(static_cast<int>(directionX * m_speed));
      moveY(static_cast<int>(directionY * m_speed));
    }
    if(m_char.getX()< getX() - DISTANCEMONSTERPLAYER) {
      m_direction["right"] = false;
      m_direction["left"] = true;
      moveX(static_cast<int>(directionX * m_speed));
      moveY(static_cast<int>(directionY * m_speed));
    }
  } else {
    if (m_direction["right"] && !m_collision["right"]) {
      m_direction["jump"] = false;
      moveX(m_speed);
    } else if (m_direction["left"] && m_collision["left"] && getX() > 0) {
      m_direction["jump"] = true;
    }
    if (m_direction["left"] && !m_collision["left"]) {
      m_direction["jump"] = false;
      moveX(-m_speed);
    } else if (m_direction["right"] && m_collision["right"] &&
               getX() < MAP_WIDTH * (TILE_SIZE - 1)) {
      m_direction["jump"] = true;
    }
    if (m_collision["up"] && !m_collision["down"]) {
      m_direction["fall"] = true;
      moveY(m_speed);
    }
  }

  if (m_direction["up"] && !m_collision["up"] && m_timeJump < m_jumpHeight) {
    m_timeJump++;
    moveY(-m_speed);
  } else if (m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  if (m_direction["fall"] && !m_collision["down"] && !m_direction["up"]) {
    moveY(m_speed);
  }

  if (m_direction["jump"] && m_collision["down"]) {
    m_timeJump = 0;
    m_direction["up"] = true;
    m_collision["down"] = false;
  } else if (m_collision["down"]) {
    m_direction["fall"] = false;
  } else {
    m_direction["fall"] = true;
  }

  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  m_collision["up"] = m_collision["down"] = m_collision["left"] =
      m_collision["right"] = false;
}