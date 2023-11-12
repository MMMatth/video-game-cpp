#ifndef JEU_HPP
#define JEU_HPP


#include "characterRender.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "inventory.hpp"
#include "inventoryRender.hpp"
#include "map.hpp"
#include "tool.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <unordered_map>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class Game {
private:
  RenderWindow m_window;
  Map m_map;
  Character m_char;
  CharacterRender m_charRenderer;
  Coord m_posCam;
  unordered_map<string, Sprite> m_sprites;
  Inventory m_inv;
  InventoryRenderer m_invRender;
  Coord m_mousePosCam;
  Coord m_mousePosWorld;
  Texture m_texture;
  bool m_game;
  bool m_menu;
  SoundBuffer buffer;
  Sound sound;
  

public:
  Game();

  void run();

  void update();

  void updateCam();

  void updateCollide();

  void updateMousePos();

  void render();

  void clean();

  void event();

  void quit();

  void menu();

  void save();
};

#endif /* GAME_HPP */
