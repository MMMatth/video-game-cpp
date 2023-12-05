#ifndef MENU_HPP
#define MENU_HPP

#include "../gameplay/dayNightCycle.hpp"
#include "../map/map.hpp"
#include "../rendering/mapRender.hpp"
#include "../utils/cam.hpp"
#include "../utils/const.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "soundSettings.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;
using namespace std;

/**
 * @class Menu
 * @brief Represents the main menu of the game.
 *
 * The Menu class handles the main menu functionality, including rendering,
 * event handling, and managing sound settings.
 */
class Menu {
private:
  unordered_map<string, SoundBuffer> m_buffers; /**< Sound buffers for the*/
  Sound m_sound; /**< SFML sound for menu interactions. */

  // what we do in the menu
  bool menu;
  bool new_game;
  bool play_input;
  bool play_save;

  RenderWindow &m_window;        /**< Reference to the SFML RenderWindow. */
  SoundSettings m_soundSettings; /**< Sound settings for the menu. */
  int m_clickOnOff; /**< Counter to prevent rapid menu interactions. */

  Cam m_cam; /**< Camera for the menu. */

  int phase; /**< Phase of the menu. */

  unordered_map<string, Sprite> m_sprites; /**< Sprites for the menu. */

  DayNightCycle m_dayNightCycle; /**< Day-night cycle for the menu. */

  Map m_map;               /**< Map for the menu background. */
  MapRender m_mapRenderer; /**< Map renderer for the menu background. */

  map<string, Color> m_menuButtonColor; /**< Map of menu buttons pressed. */

public:
  /**
   * Parameterized constructor for Menu.
   * @param window Reference to the SFML RenderWindow.
   */
  Menu(RenderWindow &window, Sound &sound,
       unordered_map<string, Sprite> &sprites,
       unordered_map<string, SoundBuffer> &buffers,
       SoundSettings &soundSettings);

  /**
   * Handle events for the menu.
   * @param event SFML Event object.
   */
  void handleEvent(sf::Event &event);

  /**
   * Run the menu loop.
   */
  void run();

  void renderButton(int x, int y, Color edgeColor, string text, string key);

  void renderButtons();

  /** Render the menu on the game window. */
  void render();

  /** Quit the menu.*/
  void quit();

  void updateButtonColor(string buttonName, Color colorOf, Color colorTo,
                         int mouseX, int mouseY, int x, int y, int width,
                         int height);

  void updateButtonColors();

  /** update*/
  void update();

  void resetClickOnOff();

  bool isActive() const;
  bool isNewGame() const;
  bool isPlayInput() const;
  bool isPlaySave() const;

  void setActive(bool active);
  void setIsNewGame(bool newGame);
  void setIsPlayInput(bool playInput);
  void setIsPlaySave(bool playSave);

  bool volumeOff() const;
};

#endif // MENU_HPP