#ifndef JEU_HPP
#define JEU_HPP

#include "../include/otherFunctions.hpp"
#include "characterRender.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "inventory.hpp"
#include "inventoryRender.hpp"
#include "map.hpp"
#include "mapGenerator.hpp"
#include "mapRender.hpp"
#include "menu.hpp"
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
  /* inventory */
  Inventory m_inv;               /** inventory */
  InventoryRenderer m_invRender; /** inventory render part*/
  /* mouse_pos */
  Coord m_mousePosCam;   /** mouse coord in the cam (Top Left = 0, 0) */
  Coord m_mousePosWorld; /** mouse coord in the entire world*/
  /* sound*/
  unordered_map<string, SoundBuffer> m_buffers; /** all sound*/
  Sound m_sound;                                /** SFML sound*/
  /* other */
  int m_game_mode; /** 1 = creative, 2 = survival*/
  Clock m_clock;   /* clock */

public:
  /* constructor */
  Game(RenderWindow &window);
  void run();
  /* update*/
  void update();
  void updateCam();
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
  void handleMouseButton(sf::Event::MouseButtonEvent &event);
  void handleMouseWheel(float delta);
  void handleSpacePress();
  void quit();
  /*save*/
  void save();
  /* map interaction */
  void putBlock();
  bool is_breakable();
  void breakBlock();
  /* reset */
  void reset();
};

#endif /* GAME_HPP */
