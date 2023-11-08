#include "../include/characterRender.hpp"
#include "../include/character.hpp"

CharacterRender::CharacterRender(Character& character, Texture& texture) : m_character(character), m_texture(texture){

  if (!m_texture.loadFromFile("../assets/img/personnage.png")) {
    cout << "Erreur de chargement de la texture du personnage" << endl;
  }
  
  m_character.initSprites(m_texture);
}

void CharacterRender::draw(RenderWindow &window) {
  map<string, bool> direction = m_character.getDirection();
  map<string, bool> collision = m_character.getCollision();
  unordered_map<string, Sprite> sprites = m_character.getSprites();

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
