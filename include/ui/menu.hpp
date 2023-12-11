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
#include "ui.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Menu : public Ui {
private:
  // unordered_map<string, SoundBuffer> m_buffers;
  // Sound m_sound;

  // what we do in the menu
  bool menu;
  bool new_game;
  bool play_input;
  bool play_save;

  SoundSettings *m_soundSettings; /**< Sound settings for the menu. */

  Cam m_cam; /**< Camera for the menu. */

  int m_phase; /**< Phase of the menu. */

  unordered_map<string, Sprite> m_sprites; /**< Sprites for the menu. */
  Sprite m_spriteVolumeOff;                /**< Sprite for volume off. */
  Sprite m_spriteVolumeOn;                 /**< Sprite for volume on. */

  DayNightCycle m_dayNightCycle; /**< Day-night cycle for the menu. */

  Map m_map;               /**< Map for the menu background. */
  MapRender m_mapRenderer; /**< Map renderer for the menu background. */
  function<void(int volume)> m_volume;

public:
  void initButtons();

  Menu(RenderWindow &window, unordered_map<string, Sprite> &sprites,
       SoundSettings &soundSettings);

  /**
   * Handle events for the menu.
   * @param event SFML Event object.
   */
  void handleEvent(Event &event);

  void run();

  void renderButtons();

  void render();

  void quit();

  /** update*/
  void update();

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