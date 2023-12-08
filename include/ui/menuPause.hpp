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
            SoundSettings &soundSettings, bool ispause);

  /**
   * Handle the pause action.
   */
  void handle();

  void updateButtonColor(string buttonName, Color colorOf, Color colorTo,
                         int mouseX, int mouseY, int x, int y, int width,
                         int height);
  void updateButtonColors();

  void update();

  /**
   * Handle mouse button press events for the pause menu.
   * @param event SFML MouseButtonEvent.
   */
  void handleEvent(Event &event);

  void renderButton(int x, int y, Color edgeColor, string text, string key);

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);
  /**
   * Render the pause menu on the game window.
   * @param m_window SFML RenderWindow.
   * @param cam Cam object for camera information.
   */
  void render(Cam &cam);

  /**
   * Check if the game is paused.
   * @return True if the game is paused, false otherwise.
   */
  bool isPause() const;
};

#endif /* MENUPAUSE_HPP */