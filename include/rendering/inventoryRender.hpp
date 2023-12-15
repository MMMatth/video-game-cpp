#ifndef INVENTORYRENDERER_HPP
#define INVENTORYRENDERER_HPP

#include "../gameplay/inventory.hpp"
#include "../utils/cam.hpp"
#include "../utils/draw.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace sf;
using namespace std;

/** @brief Renders the player's inventory. */
class InventoryRenderer {
private:
  Inventory &m_inventory; /**< Reference to the player's inventory. */

  /** Draw an inventory tile at a specific position on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the inventory tile images.
   * @param x X-coordinate of the tile on the window.
   * @param y Y-coordinate of the tile on the window.
   * @param row Row index of the tile in the inventory grid.
   * @param column Column index of the tile in the inventory grid.
   */
  void drawTile(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
                int x, int y, int row, int column);

  /** Draw the lower bar of the inventory.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the lower bar images.
   * @param persoX X-coordinate of the player.
   * @param persoY Y-coordinate of the player.
   */
  void drawLowerBar(sf::RenderWindow &window,
                    unordered_map<string, Sprite> sprites, int persoX,
                    int persoY);

  /** Draw the entire inventory grid.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the inventory tile images.
   * @param camX X-coordinate of the camera.
   * @param camY Y-coordinate of the camera.
   */
  void drawInv(sf::RenderWindow &window, unordered_map<string, Sprite> sprites,
               int camX, int camY);

  /** Draw the selected item overlay in the inventory.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the inventory tile images.
   * @param camX X-coordinate of the camera.
   * @param camY Y-coordinate of the camera.
   * @param mouseX X-coordinate of the mouse.
   * @param mouseY Y-coordinate of the mouse.
   */
  void drawSelectedItem(sf::RenderWindow &window,
                        unordered_map<string, Sprite> sprites, int camX,
                        int camY, int mouseX, int mouseY);

public:
  /** @brief constructor for the inventory render */
  InventoryRenderer(Inventory &inv) : m_inventory(inv) {}

  /** Render the entire inventory on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the inventory tile images.
   * @param cam Reference to the camera.
   * @param mouseX X-coordinate of the mouse.
   * @param mouseY Y-coordinate of the mouse.
   */
  void render(sf::RenderWindow &window,
              std::unordered_map<std::string, sf::Sprite> sprites, Cam &cam,
              int mouseX, int mouseY);
};

#endif /* INVENTORYRENDERER_HPP */