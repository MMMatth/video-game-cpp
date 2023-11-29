#ifndef MENUPAUSE_HPP
#define MENUPAUSE_HPP

#include "../utils/cam.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "soundSettings.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/**
 * @class MenuPause
 * @brief Represents the pause menu in the game.
 *
 * The MenuPause class handles the functionality of the pause menu,
 * including rendering, event handling, and sound settings.
 */
class MenuPause {
private:
  bool m_pause;         /**< Flag indicating whether the game is paused. */
  Texture pauseTexture; /**< SFML texture for the pause menu background. */
  Sprite pauseSprite;   /**< SFML sprite for the pause menu background. */
  Sound &m_sound; /**< Reference to the SFML Sound object for sound settings. */
  SoundSettings &m_soundSettings; /**< Reference to the sound settings. */
  int m_clickOnOff; /**< Counter to prevent rapid menu interactions. */

public:
  /**
   * Parameterized constructor for MenuPause.
   * @param soundSettings Reference to the SoundSettings object.
   * @param sound Reference to the SFML Sound object.
   */
  MenuPause(SoundSettings &soundSettings, Sound &sound)
      : m_pause(false), m_clickOnOff(2), m_soundSettings(soundSettings),
        m_sound(sound) {
    Error(!pauseTexture.loadFromFile(IMG_PAUSE_ON),
          "Error loading IMG_PAUSE_ON texture");
    pauseSprite.setTexture(pauseTexture);
  }

  /**
   * Handle the pause action.
   */
  void handlePause() {
    m_pause = true;
    m_soundSettings.setVolume(0);
    m_sound.setVolume(m_soundSettings.getVolume());
  }

  /**
   * Handle mouse button press events for the pause menu.
   * @param event SFML MouseButtonEvent.
   */
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

  /**
   * Render the pause menu on the game window.
   * @param m_window SFML RenderWindow.
   * @param cam Cam object for camera information.
   */
  void render(RenderWindow &m_window, Cam &cam) {
    if (m_pause) {
      m_window.clear();
      drawSprites(cam.getX() - cam.getWidth() / 2,
                  cam.getY() - cam.getHeight() / 2, pauseSprite, &m_window,
                  cam.getWidth(), cam.getHeight());
    }
  }

  /**
   * Check if the game is paused.
   * @return True if the game is paused, false otherwise.
   */
  bool isPause() const { return m_pause; }
};

#endif /* MENUPAUSE_HPP */