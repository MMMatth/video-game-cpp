#include "../../include/rendering/monsterRender.hpp"

MonsterRender::MonsterRender(Monster &monster) : m_monster(monster) {}

void MonsterRender::drawSprite(RenderWindow &window,
                               unordered_map<string, Sprite> &sprites,
                               const string &spriteKey, int frame, int x,
                               int y) {
  Sprite sprite = sprites[spriteKey];
  sprite.setTextureRect(
      IntRect(sprites[spriteKey].getTextureRect().left + frame * 25,
              sprites[spriteKey].getTextureRect().top, 25, 48));
  drawSprites(x, y, sprite, &window, m_monster.getWidth(),
              m_monster.getHeight());
}

/*Draw function for MonsterRender class*/
void MonsterRender::render(RenderWindow &window,
                           unordered_map<string, Sprite> sprites) {
  /*Calculate the frame for animation based on elapsed time*/
  map<string, bool> direction = m_monster.getDirection();
  int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) % 3;

  /*Calculate the position of the Monster for drawing*/
  int x = m_monster.getX() + (m_monster.getWidth() / 2);
  int y = m_monster.getY();

  /*Check the direction and draw the appropriate sprite*/
  if (direction["right"]) {
    drawSprite(window, sprites, "FLYING_MONSTER_RIGHT", frame, x, y);
  } else if (direction["left"]) {
    drawSprite(window, sprites, "FLYING_MONSTER_LEFT", frame, x, y);
  } else {
    drawSprites(x, y, sprites["FLYING_MONSTER_RIGHT"], &window,
                m_monster.getWidth(), m_monster.getHeight());
  }
}
