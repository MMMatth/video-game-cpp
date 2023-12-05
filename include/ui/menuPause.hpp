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

const int RESUME_BUTTON_X = 100;
const int RESUME_BUTTON_Y = 210;
const int RESUME_BUTTON_WIDTH = 184;
const int RESUME_BUTTON_HEIGHT = 50;

const int QUIT_BUTTON_X = 100;
const int QUIT_BUTTON_Y = 314;
const int QUIT_BUTTON_WIDTH = 320;
const int QUIT_BUTTON_HEIGHT = 50;

/**
 * @class MenuPause
 * @brief Represents the pause menu in the game.
 *
 * The MenuPause class handles the functionality of the pause menu,
 * including rendering, event handling, and sound settings.
 */
class MenuPause {
private:
  bool m_pause; /**< Flag indicating whether the game is paused. */

  RenderWindow &m_window;
  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;
  SoundSettings &m_soundSettings;

  map<string, Color> m_menuButtonColor; /**< Map of menu buttons pressed. */

public:
  /**
   * Parameterized constructor for MenuPause.
   * @param soundSettings Reference to the SoundSettings object.
   * @param sound Reference to the SFML Sound object.
   */
  MenuPause(RenderWindow &window, Sound &sound,
            unordered_map<string, SoundBuffer> &buffers,
            SoundSettings &soundSettings, bool ispause)
      : m_pause(ispause), m_window(window), m_sound(sound),
        m_soundSettings(soundSettings) {
    m_buffers = buffers;
    m_menuButtonColor["resume"] = Color::White;
    m_menuButtonColor["quit"] = Color::White;
  }

  /**
   * Handle the pause action.
   */
  void handle() {
    if (m_pause) {
      m_pause = false;
    } else {
      m_pause = true;
    }
  }

  void updateButtonColor(string buttonName, Color colorOf, Color colorTo,
                         int mouseX, int mouseY, int x, int y, int width,
                         int height) {
    if (isInside(mouseX, mouseY, x, y, width, height)) {
      m_menuButtonColor[buttonName] = colorOf;
    } else {
      m_menuButtonColor[buttonName] = colorTo;
    }
  }
  void updateButtonColors() {
    int mouseX = Mouse::getPosition(m_window).x;
    int mouseY = Mouse::getPosition(m_window).y;
    /* button resume */
    updateButtonColor("resume", Color::Yellow, Color::White, mouseX, mouseY,
                      RESUME_BUTTON_X, RESUME_BUTTON_Y, RESUME_BUTTON_WIDTH,
                      RESUME_BUTTON_HEIGHT);

    /* button quit */
    updateButtonColor("quit", Color::Yellow, Color::White, mouseX, mouseY,
                      QUIT_BUTTON_X, QUIT_BUTTON_Y, QUIT_BUTTON_WIDTH,
                      QUIT_BUTTON_HEIGHT);
  }

  void update() { updateButtonColors(); }

  /**
   * Handle mouse button press events for the pause menu.
   * @param event SFML MouseButtonEvent.
   */
  void handleEvent(Event &event) {
    if (event.type == Event::MouseButtonPressed) {
      if (event.mouseButton.button == Mouse::Left) {
        int mouseX = Mouse::getPosition(m_window).x;
        int mouseY = Mouse::getPosition(m_window).y;
        if (isInside(mouseX, mouseY, RESUME_BUTTON_X, RESUME_BUTTON_Y,
                     RESUME_BUTTON_WIDTH,
                     RESUME_BUTTON_HEIGHT)) { // resume button
          play_sound(&m_buffers["PLAY"], &m_sound);
          handle();
        } else if (isInside(mouseX, mouseY, QUIT_BUTTON_X, QUIT_BUTTON_Y,
                            QUIT_BUTTON_WIDTH,
                            QUIT_BUTTON_HEIGHT)) { // quit button
          play_sound(&m_buffers["PLAY"], &m_sound);
          m_window.close();
        }
      }
    }
    if (event.type == Event::KeyPressed) {
      if (event.key.code == Keyboard::P) {
        handle();
      }
    }
  }

  void renderButton(int x, int y, Color edgeColor, string text, string key) {
    drawTextWithEdge(x, y, text, &m_window, 50, m_menuButtonColor[key],
                     sf::Color::Black, MINECRAFT_FONT_PATH);
  }

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner) {
    /* button resume */

    renderButton(XtopLeftCorner + RESUME_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
                 YtopLeftCorner + RESUME_BUTTON_Y * WINDOW_HEIGHT / CAM_HEIGHT,
                 Color::Black, "Resume", "resume");

    /* button quit */
    renderButton(XtopLeftCorner + QUIT_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
                 YtopLeftCorner + QUIT_BUTTON_Y * WINDOW_HEIGHT / CAM_HEIGHT,
                 Color::Black, "Quit", "quit");
  }

  /**
   * Render the pause menu on the game window.
   * @param m_window SFML RenderWindow.
   * @param cam Cam object for camera information.
   */
  void render(Cam &cam) {
    int XtopLeftCorner = cam.getTopLeftX();
    int YtopLeftCorner = cam.getTopLeftY();
    if (m_pause) {
      /* buttons */
      renderButtons(XtopLeftCorner, YtopLeftCorner);
    }
  }

  /**
   * Check if the game is paused.
   * @return True if the game is paused, false otherwise.
   */
  bool isPause() const { return m_pause; }
};

#endif /* MENUPAUSE_HPP */