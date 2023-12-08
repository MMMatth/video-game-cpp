#ifndef MONSTER_RENDER_HPP
#define MONSTER_RENDER_HPP

#include "../entity/monster.hpp"
#include "entityRender.hpp"

using namespace std;

class MonsterRender : public EntityRender {
private:
  /* data */
public:
  MonsterRender(Monster &monster) : EntityRender(monster) {}

  void renderLife(RenderWindow &window,
                  unordered_map<string, Sprite> &sprites) {
    // Position of the health bar
    float healthBarX = m_entity.getX() + m_entity.getWidth() / 2;
    float healthBarY = m_entity.getY() - HEALTH_BAR_HEIGHT;

    // Create the black background of the health bar
    RectangleShape backgroundBar(Vector2f(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT));
    backgroundBar.setPosition(healthBarX, healthBarY);
    backgroundBar.setFillColor(Color::Black);

    // Create the red health bar
    float healthBarLength =
        static_cast<float>(m_entity.getLife()) / 100 * HEALTH_BAR_WIDTH;
    RectangleShape healthBar(Vector2f(healthBarLength, HEALTH_BAR_HEIGHT));
    healthBar.setPosition(healthBarX, healthBarY);
    healthBar.setFillColor(Color::Red);

    // Draw the health bars
    if (m_entity.getLife() < 100) {
      window.draw(backgroundBar);
    }
    if (m_entity.getLife() > 0) {
      window.draw(healthBar);
    }
  }
};

#endif // MONSTER_RENDER_HPP