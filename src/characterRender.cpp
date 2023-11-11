#include "../include/characterRender.hpp"
#include "../include/character.hpp"
#include "../include/draw.hpp"

CharacterRender::CharacterRender(Character &character) : character(character) {}

void CharacterRender::draw(RenderWindow &window,
                           unordered_map<string, Sprite> sprites) {
  map<string, bool> direction = character.getDirection();
  map<string, bool> collision = character.getCollision();
  int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) %
              NUM_FRAMES;

  if (direction["isGoingLeft"]) {
    Sprite sprite = sprites["CHAR_LEFT"]; // we use a variable to modify the
                                          // x position of the sprite
    sprite.setTextureRect(
        IntRect(sprites["CHAR_LEFT"].getTextureRect().left +
                    frame * 25, // we add the width of the sprite for each frame
                sprites["CHAR_LEFT"].getTextureRect().top, 25, 48));
    drawSprites(character.getX(), character.getY(), sprite, &window,
                character.getWidth(), character.getHeight());
  } else if (direction["isGoingRight"]) {
    Sprite sprite = sprites["CHAR_RIGHT"];
    sprite.setTextureRect(
        IntRect(sprites["CHAR_RIGHT"].getTextureRect().left + frame * 25,
                sprites["CHAR_RIGHT"].getTextureRect().top, 25, 48));
    drawSprites(character.getX(), character.getY(), sprite, &window,
                character.getWidth(), character.getHeight());
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
