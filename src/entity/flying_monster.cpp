#include "../../include/entity/flying_monster.hpp"

void FlyingMonster::update(const Character &m_char) {
  // Calculate the direction towards which the monster should move to reach the player
  int deltaX = m_char.getX() - getX() - DISTANCEMONSTERPLAYER;
  int deltaY = m_char.getY() - getY() - DISTANCEMONSTERPLAYER;

  // Calculate the distance between the monster and the player
  float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

  // Normalize the direction to get a unit vector
  float directionX = deltaX / distance;
  float directionY = deltaY / distance;

  // Add some variability to the monster's speed
  float speedVariability = static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f;
 
  // If the player is within attack distance, move towards the player
  if(distance <= ATTACKDISTANCE){
    if (m_char.getX() - DISTANCEMONSTERPLAYER > getX()) {
      m_direction["right"] = true;
      m_direction["left"] = false;
      moveX(static_cast<int>(directionX * m_speed * speedVariability));
      moveY(static_cast<int>(directionY * m_speed * speedVariability));
    }
    if(m_char.getX()< getX() - DISTANCEMONSTERPLAYER) {
      m_direction["right"] = false;
      m_direction["left"] = true;
      moveX(static_cast<int>(directionX * m_speed * speedVariability));
      moveY(static_cast<int>(directionY * m_speed * speedVariability));
    }
    
  }else{
    // Move the monster if beyond attack distance
    if (m_direction["right"] && !m_collision["right"]) {
      m_direction["left"] = false; 
      moveX(m_speed); 
    }else{
      m_direction["left"] = true;
    }
    if (m_direction["left"] && !m_collision["left"]) {
      m_direction["right"] = false;
      moveX(-m_speed); 
    }else{
      m_direction["right"] = true;
    }

    m_collision["up"] = false;
    m_collision["down"] = false;
    m_collision["left"] = false;
    m_collision["right"] = false;
  }
}