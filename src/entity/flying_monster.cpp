#include "../../include/entity/flying_monster.hpp"

void FlyingMonster::update() {
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