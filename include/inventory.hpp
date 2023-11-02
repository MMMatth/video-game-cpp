/**
 * \file inventory.hpp
 * \author Matthieu Gaudel et Papa El Hadji G Cissé
 * \brief class Inventory
 *
 */

#ifndef inventory_hpp
#define inventory_hpp

#include "const.hpp"
#include "draw.hpp"
#include "inventoryTile.hpp"
#include "item.hpp"
#include "point.hpp"
#include <cassert>
#include <string>
#include <vector>

using namespace std;

/**
 * \brief class Inventory
 * la premiere ligne de l'inventaire contient les objet dans la main du joueur
 */
class Inventory {
private:
  InventoryTile m_inventory[INVENTORY_HEIGHT][INVENTORY_WIDTH];
  InventoryTile m_selected_tile;
  int m_pos_hand;
  bool m_is_open;

public:
  /* Constructeur */
  Inventory();
  Inventory(string csvPath);
  /* Destruceur */
  ~Inventory();
  /**
   * \brief fonction qui echange les items de deux cases
   *
   * \param p1 : position de la premiere case
   * \param p2 : position de la deuxieme case
   */
  void swapItem(Point p1, Point p2);

  /**
   * \brief fonction qui echange les items de deux cases
   *
   * \param t1 : premiere case
   * \param t2 : deuxieme case
   */
  void swapItem(InventoryTile *t1, InventoryTile *t2);
  /**
   * \brief add item to the inventory
   *
   * \param item
   */
  void addItem(Item item);
  /**
   * \brief remove item from the inventory
   *
   * \param pos : position of the item
   */
  void removeItem(Point pos);

  /* render */
  void drawItem(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
                int x, int y, int row, int column);
  void drawLowerBar(sf::RenderWindow &window,
                    unordered_map<string, Sprite> sprites, int persoX,
                    int persoY);
  void drawInv(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
               int camX, int camY);
  void drawSelectedItem(sf::RenderWindow &window,
                        unordered_map<string, Sprite> sprites, int camX,
                        int camY, int mouseX, int mouseY);
  void render(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
              int camX, int camY, int mouseX, int mouseY);

  /* handle */
  void handleClick(int mouseX, int mouseY, int persoX, int persoY);

  /* setters */
  void setIsOpen() {
    if (m_is_open) {
      m_is_open = false;
      addItem(m_selected_tile.getItem());
      m_selected_tile = InventoryTile();
    } else {
      m_is_open = true;
    }
  }

  void setPosHand(int indice) { m_pos_hand = indice; }
  int getPosHand() { return m_pos_hand; }

  /* getters */
  InventoryTile getSelectedTile() { return m_selected_tile; }
  Point getInventoryPosition(int mouseX, int mouseY, int persoX, int persoY);
  InventoryTile getTile(Point pos) {
    return m_inventory[pos.getX()][pos.getY()];
  }
  bool isOpen() { return m_is_open; }

  string toString();
};

#endif /* inventory_hpp */