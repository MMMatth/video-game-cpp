
#ifndef MENUPAUSE_HPP
#define MENUPAUSE_HPP

#include "cam.hpp"
#include "draw.hpp"
#include "otherFunctions.hpp"
#include "soundSettings.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class MenuPause {
private:
  bool m_pause;
  Texture pauseTexture;
  Sprite pauseSprite;
  Sound &m_sound;
  SoundSettings &m_soundSettings;
  int m_clickOnOff;

public:
  MenuPause(SoundSettings &SoundSettings, Sound &sound)
      : m_pause(false), m_clickOnOff(2), m_soundSettings(SoundSettings),
        m_sound(sound) {
    Error(!pauseTexture.loadFromFile(IMG_PAUSE_ON),
          "Error loading IMG_PAUSE_ON texture");
    pauseSprite.setTexture(pauseTexture);
  }

  void handlePause() {
    m_pause = true;
    m_soundSettings.setVolume(0);
    m_sound.setVolume(m_soundSettings.getVolume());
  }

  void handleMouseButtonPressed(sf::Event::MouseButtonEvent &event) {
    if (event.button == Mouse::Left) {
      if (m_pause) {
        int mouseX = event.x;
        int mouseY = event.y;

        if (isInside(mouseX, mouseY, 75, 162, 314, 211)) {
          m_pause = false;
        }
        /*sound*/
        if (isInside(mouseX, mouseY, 37, 33, 62, 62)) {
          if (m_clickOnOff == 2) {
            Error(!pauseTexture.loadFromFile(IMG_PAUSE_OFF),
                  "Error loading IMG_PAUSE_OFF texture");
            m_soundSettings.setVolume(0);
            m_sound.setVolume(m_soundSettings.getVolume());
            m_clickOnOff--;
          } else {
            Error(!pauseTexture.loadFromFile(IMG_PAUSE_ON),
                  "Error loading IMG_PAUSE_ON texture");
            m_soundSettings.setVolume(5);
            m_sound.setVolume(m_soundSettings.getVolume());
            m_clickOnOff++;
          }
        }
      }
    }
  }

  void render(RenderWindow &m_window, Cam &cam) {
    if (m_pause) {
      m_window.clear();
      drawSprites(cam.getX() - cam.getWidth() / 2,
                  cam.getY() - cam.getHeight() / 2, pauseSprite, &m_window,
                  cam.getWidth(), cam.getHeight());
    }
  }

  bool isPause() const { return m_pause; }
};

#endif /*MENUPAUSE_HPP*/