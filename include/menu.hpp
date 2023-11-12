#include "const.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
private:
  Texture menuTexture;
  Sprite menuSprite;
  SoundBuffer buffer;
  Sound sound;
  bool m_menu;

public:
  Menu();
  void handleEvent(sf::Event &event);
  void draw(sf::RenderWindow &window);
  bool isActive() const;
  void setActive(bool active);
};
