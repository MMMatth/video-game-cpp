#include "../include/characterRender.hpp"

CharacterRender::CharacterRender(Character &character) : character(character) {}

void CharacterRender::drawSprite(RenderWindow &window,
                                 unordered_map<string, Sprite> &sprites,
                                 const string &spriteKey, int frame, int x,
                                 int y) {
  Sprite sprite = sprites[spriteKey];
  sprite.setTextureRect(
      IntRect(sprites[spriteKey].getTextureRect().left + frame * 25,
              sprites[spriteKey].getTextureRect().top, 25, 48));
  drawSprites(x, y, sprite, &window, character.getWidth(),
              character.getHeight());
}

void CharacterRender::renderCharacter(RenderWindow &window,
                                      unordered_map<string, Sprite> sprites) {
  map<string, bool> direction = character.getDirection();
  map<string, bool> collision = character.getCollision();
  int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) %
              NUM_FRAMES;
  int x = character.getX() - (character.getWidth() / 2); // center the character
  int y = character.getY();
  if (direction["left"]) {
    drawSprite(window, sprites, "CHAR_LEFT", frame, x, y);
  } else if (direction["right"]) {
    drawSprite(window, sprites, "CHAR_RIGHT", frame, x, y);
  } else if (direction["jump"] && !collision["right"]) {
    drawSprites(x - character.getWidth() / 2, y, sprites["CHAR_JUMP"], &window,
                character.getWidth() * 2, character.getHeight());
  } else if (direction["fall"] && !collision["down"]) {
    drawSprites(x - character.getWidth() / 2, y, sprites["CHAR_FALL"], &window,
                character.getWidth() * 2, character.getHeight());
  } else {
    drawSprites(x, y, sprites["CHAR_FRONT"], &window, character.getWidth(),
                character.getHeight());
  }
}

void CharacterRender::renderLife(RenderWindow &window,
                                 unordered_map<string, Sprite> sprites,
                                 int camX, int camY) {
  int life = character.getLife();
  int entire_heart = life / 2;
  int half_heart = life % 2;
  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY + CAM_HEIGHT / 2 - INVENTORY_TILE_SIZE * 2 - 20;

  for (int i = 0; i < 10; i++) {
    drawSprites(x + i * 15, y, sprites["BLACK_HEART"], &window, 15, 15);
  }
  for (int i = 0; i < entire_heart; i++) {
    drawSprites(x + i * 15, y, sprites["HEART"], &window, 15, 15);
  }
  for (int i = half_heart; i < entire_heart + half_heart; i++) {
    drawSprites(x + i * 15, y, sprites["HALF_HEART"], &window, 15, 15);
  }
}

void CharacterRender::render(RenderWindow &window,
                             unordered_map<string, Sprite> sprites, int camX,
                             int camY) {
  renderCharacter(window, sprites);
  renderLife(window, sprites, camX, camY);
}
