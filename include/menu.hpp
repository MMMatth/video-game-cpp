#ifndef MENU_HPP
#define MENU_HPP

#include "../include/otherFunctions.hpp"
#include "../include/soundSettings.hpp"
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
  bool m_newGame;
  int m_clickOnOff;
  RenderWindow &m_window;
  SoundSettings m_soundSettings;


public:
  Menu(RenderWindow &window);
  void handleEvent(sf::Event &event);
  void run();
  void render();
  void quit();
  bool isActive() const;
  bool isNewGame() const;
  bool volumeOff()const;
  void setIsNewGame(bool newGame);
  void resetClickOnOff();
};

#endif