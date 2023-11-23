#include "../../include/rendering/entityRender.hpp"

EntityRender::EntityRender(Entity &entity) : m_entity(entity) {}

void EntityRender::render(RenderWindow &window,
                          unordered_map<string, Sprite> sprites, string key,
                          int nbFrame) {
  /* first we recover the collision and direction map*/
  map<string, bool> direction = m_entity.getDirection();
  map<string, bool> collision = m_entity.getCollision();
  /* next we recover the frame of the animation */
  int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) % 3;

  /*Calculate the position of the Monster for drawing*/
  int x = m_entity.getX() + (m_entity.getWidth() / 2); // center the entity
  int y = m_entity.getY();
  // we check the string key is a key in the unordered maps
  bool isLeftKey = sprites.find(key + "_LEFT") != sprites.end();
  bool isRightKey = sprites.find(key + "_RIGHT") != sprites.end();
  bool isFrontKey = sprites.find(key + "_FRONT") != sprites.end();
  bool isJumpKey = sprites.find(key + "_JUMP") != sprites.end();
  bool isFallKey = sprites.find(key + "_FALL") != sprites.end();

  /*Check the direction and draw the appropriate sprite*/
  if (direction["right"] && isRightKey) {
    drawEnityAnimation(window, sprites, key + "_RIGHT", frame, x, y);
  } else if (direction["left"] && isLeftKey) {
    drawEnityAnimation(window, sprites, key + "_LEFT", frame, x, y);
  } else if (direction["jump"] && isJumpKey) {
    drawEntityStatic(window, sprites, key + "_JUMP", x, y);
  } else if (direction["fall"] && isFallKey) {
    drawEntityStatic(window, sprites, key + "_FALL", x, y);
  } else if (isFrontKey) {
    drawEntityStatic(window, sprites, key + "_FRONT", x, y);
  } else {
    cerr << "ERROR: " << key << " is not a valid key in the sprites map"
         << endl;
  }
}

void EntityRender::drawEnityAnimation(RenderWindow &window,
                                      unordered_map<string, Sprite> &sprites,
                                      const string &spriteKey, int frame, int x,
                                      int y) {
  Sprite sprite = sprites[spriteKey];
  sprite.setTextureRect(
      IntRect(sprites[spriteKey].getTextureRect().left + frame * 25,
              sprites[spriteKey].getTextureRect().top, 25, 48));
  drawSprites(x, y, sprite, &window, m_entity.getWidth(), m_entity.getHeight());
}

void EntityRender::drawEntityStatic(RenderWindow &window,
                                    unordered_map<string, Sprite> &sprites,
                                    const string &spriteKey, int x, int y) {
  if (spriteKey == "CHAR_JUMP" || spriteKey == "CHAR_FALL") {
    drawSprites(x, y, sprites[spriteKey], &window, m_entity.getWidth() * 2,
                m_entity.getHeight());
    return;
  }
  drawSprites(x, y, sprites[spriteKey], &window, m_entity.getWidth(),
              m_entity.getHeight());
}