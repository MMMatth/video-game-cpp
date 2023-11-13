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
  MapRender m_mapRenderer;
  Coord m_posCam; /* camera position */
  Clock m_clock;  /* clock */
  /* inventory */
  Inventory m_inv;
  InventoryRenderer m_invRender;
  /* mouse_pos */
  Coord m_mousePosCam;
  Coord m_mousePosWorld;
  /* sound*/
  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;

public:
  Game(RenderWindow &window);

  void run();

  void update();

  void updateCam();

  void updateCollide();

  void updateMousePos();

  void render();

  void clean();

  void handleEvent(Event &event);

  void quit();

  void save();
};

#endif /* GAME_HPP */
