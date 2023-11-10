/*!
 * \file jeu.hpp
 * \brief Définition de la classe Jeu.
 * \author Matthieu Gaudel and Papa El Hadji G Cissé
 */
#ifndef JEU_HPP
#define JEU_HPP


#include "characterRender.hpp"
#include "const.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include "inventory.hpp"
#include "inventoryRender.hpp"
#include "json.hpp"
#include "map.hpp"
#include "tool.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <unordered_map>

using namespace sf;
using namespace std;

class Jeu {
private:
  Map m_map;
  Character m_char;
  RenderWindow m_window;
  Coord m_posCam;
  unordered_map<string, Sprite> m_sprites;
  Inventory m_inv;
  InventoryRenderer m_invRender;
  Coord m_mousePosCam;
  Coord m_mousePosWorld;
  Texture m_texture;
  CharacterRender m_charRenderer;
  bool m_jeu;
  bool m_menu;

public:
  Jeu();

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

  bool collisionAvecCarte(int x, int y);
};

#endif /* JEU_HPP */
