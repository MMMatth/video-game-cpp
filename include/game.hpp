#ifndef JEU_HPP
#define JEU_HPP

#include "characterRender.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "inventory.hpp"
#include "inventoryRender.hpp"
#include "map.hpp"
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
  RenderWindow &m_window; /* window */
  Map m_map;              /* map */
  Map m_newMap;
  /* character */
  Character m_char;
  CharacterRender m_charRenderer;
  Coord m_posCam;                          /* camera position */
  unordered_map<string, Sprite> m_sprites; /* sprites */
  /* inventory */
  Inventory m_inv;
  InventoryRenderer m_invRender;
  /* mouse_pos */
  Coord m_mousePosCam;
  Coord m_mousePosWorld;

  /* sound*/
  SoundBuffer buffer;
  Sound sound;
  Clock jumpClock;
  const Time minimalTime = seconds(1.0f);

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

  void menu();

  void save();

  void reset();
};

#endif /* GAME_HPP */
