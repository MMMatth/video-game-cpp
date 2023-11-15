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
#include <unordered_map>

using namespace sf;
using namespace std;

class Game {
private:
  /* graphics */
  RenderWindow &m_window;
  unordered_map<string, Sprite> m_sprites;
  /* character */
  Character m_char;
  CharacterRender m_charRenderer;
  /* map */
  Map m_map;
  // Map m_newMap;
  MapRender m_mapRenderer;
  Coord m_posCam; /* camera position */
  Clock m_clock;  /* clock */
  Clock m_clock2;
  /* inventory */
  Inventory m_inv;
  InventoryRenderer m_invRender;
  /* mouse_pos */
  Coord m_mousePosCam;
  Coord m_mousePosWorld;
  /* sound*/
  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;
  /* other */
  int m_mode; // 1 = creative, 2 = survival
  bool m_isBreaking;
  Clock m_breakClock;

public:
  /* constructor */
  Game(RenderWindow &window);
  void run();
  /* update*/
  void update();
  void updateCam();
  void updateCollide();
  void updateMousePos();
  void render();
  void clean();
  void handleEvent(Event &event);
  void quit();
  void save();
  /* map interaction */
  void putBlock();
  bool is_breakable();
  void breakBlock();

  void reset();
};

#endif /* GAME_HPP */
