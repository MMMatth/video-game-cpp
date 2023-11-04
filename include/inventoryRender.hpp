#ifndef INVENTORYRENDERER_HPP
#define INVENTORYRENDERER_HPP

#include "inventory.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class InventoryRenderer {
private:
  Inventory &m_inventory;

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

public:
  InventoryRenderer(Inventory &inv) : m_inventory(inv) {}

  void render(sf::RenderWindow &window,
              std::unordered_map<std::string, sf::Sprite> sprites, int camX,
              int camY, int mouseX, int mouseY);
};

#endif /* INVENTORYRENDERER_HPP */