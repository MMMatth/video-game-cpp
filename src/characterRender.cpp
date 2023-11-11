#include "../include/characterRender.hpp"
#include "../include/character.hpp"
#include "../include/draw.hpp"

CharacterRender::CharacterRender(Character &character) : character(character) {}

void CharacterRender::drawSprite(RenderWindow &window,
                                 unordered_map<string, Sprite> &sprites,
                                 const string &spriteKey, int frame) {
  Sprite sprite = sprites[spriteKey];
  sprite.setTextureRect(
      IntRect(sprites[spriteKey].getTextureRect().left + frame * 25,
              sprites[spriteKey].getTextureRect().top, 25, 48));
  drawSprites(character.getX(), character.getY(), sprite, &window,
              character.getWidth(), character.getHeight());
}

void CharacterRender::draw(RenderWindow &window,
                           unordered_map<string, Sprite> sprites) {
  map<string, bool> direction = character.getDirection();
  map<string, bool> collision = character.getCollision();
  int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) %
              NUM_FRAMES;

  if (direction["isGoingLeft"]) {
    drawSprite(window, sprites, "CHAR_LEFT", frame);
  } else if (direction["isGoingRight"]) {
    drawSprite(window, sprites, "CHAR_RIGHT", frame);
  } else if (direction["isJumping"] && !collision["right"]) {
    drawSprites(character.getX(), character.getY(), sprites["CHAR_JUMP"],
                &window, character.getWidth() * 2, character.getHeight());
  } else if (direction["isFalling"] && !collision["down"]) {
    drawSprites(character.getX(), character.getY(), sprites["CHAR_FALL"],
                &window, character.getWidth() * 2, character.getHeight());
  } else {
    drawSprites(character.getX(), character.getY(), sprites["CHAR_FRONT"],
                &window, character.getWidth(), character.getHeight());
  }
}
