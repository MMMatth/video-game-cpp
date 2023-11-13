#ifndef MENU_HPP
#define MENU_HPP

#include "../include/otherFunctions.hpp"
#include "const.hpp"
#include "draw.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Menu {
private:
  Texture menuTexture;
  Sprite menuSprite;
  SoundBuffer buffer;
  Sound m_sound;
  bool m_menu;
  RenderWindow &m_window;

public:
  Menu(RenderWindow &window);
  void handleEvent(sf::Event &event);
  void run();
  void render();
  void quit();
  bool isActive() const;
};

#endif