#ifndef JEU_HPP
#define JEU_HPP

#include "../include/monsterRender.hpp"
#include "../include/otherFunctions.hpp"
#include "cam.hpp"
#include "characterRender.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "dayNightCycle.hpp"
#include "draw.hpp"
#include "fpsCounter.hpp"
#include "inventory.hpp"
#include "inventoryRender.hpp"
#include "map.hpp"
#include "mapGenerator.hpp"
#include "mapRender.hpp"
#include "menu.hpp"
#include "menuPause.hpp"
#include "tool.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <functional>
#include <unordered_map>

using namespace sf;
using namespace std;

class Game {
private:
  /* graphics */
  RenderWindow &m_window;                  /** SFML Window*/
  unordered_map<string, Sprite> m_sprites; /** all Sprite*/
  /* character */
  Character m_char;               /** Character */
  CharacterRender m_charRenderer; /** character render part*/
  /* map */
  Map m_map;
  MapRender m_mapRenderer;
  /* cam */
  Coord m_posCam; /* camera position */
  Cam m_cam;
  /* inventory */
  Inventory m_inv;               /** inventory */
  InventoryRenderer m_invRender; /** inventory render part*/
  /* mouse_pos */
  Coord m_mousePosCam;   /** mouse coord in the cam (Top Left = 0, 0) */
  Coord m_mousePosWorld; /** mouse coord in the entire world*/
  /* sound*/
  unordered_map<string, SoundBuffer> m_buffers; /** all sound*/
  SoundSettings m_soundSettings;
  Sound m_sound; /** SFML sound*/
  /* day_night_cycle */
  DayNightCycle m_day_night_cycle;
  /* other */
  int m_game_mode;         /** 1 = creative, 2 = survival*/
  FpsCounter m_fpsCounter; /* clock */
  /*pause*/
  MenuPause m_menuPause;
  bool m_pause;
  Texture pauseTexture;
  Sprite pauseSprite;
  int m_clickOnOff;
  /*monster*/
  vector<Monster> m_monsters;
  vector<MonsterRender> m_monsterRenders;
  Texture m_monsterTexture;

public:
  /* constructor */
  Game(RenderWindow &window);
  void run();
  /* update*/
  void update();
  void updateCollide();
  void updateMousePos();
  /* render */
  void render();
  /* clean */
  void clean();
  /* event */
  void handleEvent(Event &event);
  void handleKeyPress(Keyboard::Key key);
  void handleKeyRelease(Keyboard::Key key);
  void handleMouseButtonPressed(sf::Event::MouseButtonEvent &event);
  void handleMouseButtonReleased(sf::Event::MouseButtonEvent &event);
  void handleMouseWheel(float delta);
  void handleSpacePress();
  /* quit */
  void quit();
  /*save*/
  void save();
  /* map interaction */
  void putBlock();
  bool is_breakable();
  void breakBlock();
  /* sound */
  void setGameVolume(float volume);
  /* reset */
  void reset();
  bool isPause() const;
};

#endif /* GAME_HPP */
