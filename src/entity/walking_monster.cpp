#include "../../include/entity/walking_monster.hpp"

void WalkingMonster::update(const Character &m_char) {
  // Calculate the direction towards which the monster should move to reach the player
  int deltaX = m_char.getX() - getX();
  int deltaY = m_char.getY() - getY();

  // Calculate the distance between the monster and the player
  float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

  // Normalize the direction to get a unit vector
  float directionX = deltaX / distance;
  float directionY = deltaY / distance;

  // Add some variability to the monster's speed
  float speedVariability = static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f;

  // If the player is within attack distance, move towards the player
  if (distance <= ATTACKDISTANCE) {
    if (m_char.getX() > getX()) {
      m_direction["right"] = true;
      m_direction["left"] = false;
      if (!m_collision["right"]) {
        moveX(static_cast<int>(directionX * m_speed * speedVariability));
        moveY(static_cast<int>(directionY * m_speed * speedVariability));
      }
    } else {
      m_direction["right"] = false;
      m_direction["left"] = true;
      if (!m_collision["left"]) {
        moveX(static_cast<int>(directionX * m_speed * speedVariability));
        moveY(static_cast<int>(directionY * m_speed * speedVariability));
      }
    }
  } else {
    // Move the monster if beyond attack distance
    if (m_direction["right"] && !m_collision["right"]) {
      m_direction["jump"] = false;
      moveX(m_speed);
    }

    if (m_direction["left"] && !m_collision["left"]) {
      m_direction["jump"] = false;
      moveX(-m_speed);
    } else if(m_direction["left"] && m_collision["left"]) {
      if(getX() <= 0){
        m_direction["right"] = true;
        m_direction["left"] = false;
      } else {
        m_direction["jump"] = true;
      }
    }

    if (m_collision["up"] && !m_collision["down"]) {
      m_direction["fall"] = true;
      moveY(m_speed);
    }
  }

  // Additional movement logic and collision handling
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
  } else if (m_collision["down"]) { // if the monster touches the ground
    m_direction["fall"] = false;
  } else { // if the monster is in the air
    m_direction["fall"] = true;
  }

  if ((!m_direction["jump"] || m_collision["up"]) && m_direction["up"]) {
    m_direction["up"] = false;
    m_direction["fall"] = true;
  }

  if(m_direction["right"] && m_collision["right"]) {
    m_direction["jump"] = true;
  }

  if(getX() >= MAP_WIDTH * (TILE_SIZE - 1)){
    m_direction["right"] = false;
    m_direction["left"] = true;
  }

  if(m_direction["left"] && m_collision["left"]) {
    if(getX() <= 0){
      m_direction["right"] = true;
      m_direction["left"] = false;
    } else {
      m_direction["jump"] = true;
    }
  }

  m_collision["up"] = false;
  m_collision["down"] = false;
  m_collision["left"] = false;
  m_collision["right"] = false;
}