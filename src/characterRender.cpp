#include "../include/characterRender.hpp"
#include "../include/character.hpp"
#include "../include/draw.hpp"

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

void CharacterRender::draw(RenderWindow &window,
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
    drawSprites(x, y, sprites["CHAR_JUMP"], &window, character.getWidth() * 2,
                character.getHeight());
  } else if (direction["fall"] && !collision["down"]) {
    drawSprites(x, y, sprites["CHAR_FALL"], &window, character.getWidth() * 2,
                character.getHeight());
  } else {
    drawSprites(x, y, sprites["CHAR_FRONT"], &window, character.getWidth(),
                character.getHeight());
  }
}
