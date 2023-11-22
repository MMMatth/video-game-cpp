#ifndef MENU_HPP
#define MENU_HPP

#include "../utils/const.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "soundSettings.hpp"
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
  RenderWindow &m_window;
  SoundSettings m_soundSettings;
  int m_clickOnOff;

public:
  Menu(RenderWindow &window);
  void handleEvent(sf::Event &event);
  void run();
  void render();
  void quit();
  void setIsNewGame(bool newGame);
  void resetClickOnOff();
  bool isActive() const;
  bool isNewGame() const;
  bool volumeOff() const;
};

#endif