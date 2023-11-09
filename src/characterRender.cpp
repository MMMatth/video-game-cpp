#include "../include/characterRender.hpp"
#include "../include/character.hpp"

CharacterRender::CharacterRender(Character& character) 
    : character(character) {

}
void CharacterRender::draw(RenderWindow &window) {
  map<string, bool> direction = character.getDirection();
  map<string, bool> collision = character.getCollision();
  unordered_map<string, Sprite> sprites = character.getSprites();

  if (direction["isGoingLeft"]) {
    int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) % NUM_FRAMES;
    window.draw(sprites["moveLeft" + to_string(frame + 1)]);
  } else if (direction["isGoingRight"]) {
    int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) % NUM_FRAMES;
    window.draw(sprites["moveRight" + to_string(frame + 1)]);
  } else if (direction["isJumping"] && !collision["right"]) {
    window.draw(sprites["jump"]);
  } else if (direction["isFalling"] && !collision["down"]) {
    window.draw(sprites["fall"]);
  } else {
    window.draw(sprites["stop"]);
  }
}
