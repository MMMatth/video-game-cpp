#ifndef GAME_HPP
#define GAME_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"
#include "../item/tool.hpp"
#include "../item/weapon.hpp"

#include "../entity/character.hpp"
#include "../entity/entity.hpp"
#include "../entity/monsters.hpp"

#include "dayNightCycle.hpp"
#include "inventory.hpp"

#include "../ui/fpsCounter.hpp"
#include "../ui/menu.hpp"
#include "../ui/menuPause.hpp"
#include "../ui/soundSettings.hpp"

#include "../utils/cam.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "../utils/sprites.hpp"

#include "../map/map.hpp"

#include "../rendering/characterRender.hpp"
#include "../rendering/entityRender.hpp"
#include "../rendering/inventoryRender.hpp"
#include "../rendering/mapRender.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <functional>
#include <map>
#include <string>
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
  bool m_save;             /** true = save, false = not save*/
  FpsCounter m_fpsCounter; /* clock */
  /*pause*/
  MenuPause m_menuPause;
  /*monster*/
  Monsters m_monsters;

public:
  /* constructor */
  Game(RenderWindow &window, Sound &sound,
       unordered_map<string, Sprite> &sprites,
       unordered_map<string, SoundBuffer> &buffers,
       SoundSettings &soundSettings, bool save, bool input);
  void run();
  /* update*/
  void update();
  void updateCollide();
  void updateMousePos();
  void updateBreaking();
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
  void putBlock(bool isBreakable);
  bool is_breakable();
  void breakBlock();
  /* sound */
  void setGameVolume(float volume);
  /* reset */
  void reset(bool save);
  bool isPause();
  /* other */
  void setSave(bool mode) { m_save = mode; }
};

#endif /* GAME_HPP */
