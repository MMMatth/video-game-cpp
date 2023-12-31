#include "../../include/rendering/inventoryRender.hpp"

void InventoryRenderer::drawTile(sf::RenderWindow &window,
                                 unordered_map<string, Sprite> sprites, int x,
                                 int y, int row, int column) {
  // first we draw the empty tile
  drawSprites(x + column * INV_TILE_SIZE, y, sprites["TILE"], &window,
              INV_TILE_SIZE, INV_TILE_SIZE);
  if (!m_inventory.getTile(Coord(row, column)).isEmpty()) {
    // then we draw the item
    drawSprites(x + column * INV_TILE_SIZE + TOP_LEFT_INV_TILE,
                y + TOP_LEFT_INV_TILE,
                sprites[m_inventory.getItemAt(Coord(row, column)).getName()],
                &window, INV_OBJ_SIZE, INV_OBJ_SIZE);
    // if the item is stackable we draw the amount
    if (m_inventory.getItemAt(Coord(row, column)).isStackable()) {
      drawTextWithEdge(
          x + column * INV_TILE_SIZE + TOP_LEFT_INV_TILE, y + TOP_LEFT_INV_TILE,
          to_string(m_inventory.getItemAt(Coord(row, column)).getAmount()),
          &window, INV_TILE_SIZE / 5, WITE_COLOR, BLACK_COLOR, FONT_PATH);
    }
  }
  // if the tile is selected we draw the selected tile
  if (column == m_inventory.getPosHand() && row == INV_HEIGHT - 1)
    drawSprites(x + column * INV_TILE_SIZE, y, sprites["SELECTED_TILE"],
                &window, INV_TILE_SIZE, INV_TILE_SIZE);
}

void InventoryRenderer::drawLowerBar(sf::RenderWindow &window,
                                     unordered_map<string, Sprite> sprites,
                                     int camX, int camY) {
  int x = camX - X_LOWER_BAR_OFFSET;
  int y = camY - Y_LOWER_BAR_OFFSET;
  for (int column = 0; column < INV_WIDTH; column++) {
    drawTile(window, sprites, x, y, INV_HEIGHT - 1, column);
  }
}

void InventoryRenderer::drawInv(sf::RenderWindow &window,
                                unordered_map<string, Sprite> sprites, int camX,
                                int camY) {
  int x = camX - X_INV_OFFSET;
  int y = camY - Y_INV_OFFSET;
  for (int row = 0; row < INV_HEIGHT - 1; row++) {
    for (int column = 0; column < INV_WIDTH; column++) {
      drawTile(window, sprites, x, y + row * INV_TILE_SIZE, row, column);
    }
  }
}

void InventoryRenderer::drawSelectedItem(sf::RenderWindow &window,
                                         unordered_map<string, Sprite> sprites,
                                         int camX, int camY, int mouseX,
                                         int mouseY) {
  drawSprites(mouseX, mouseY,
              sprites[m_inventory.getSelectedTile().getItem()->getName()],
              &window, INV_OBJ_SIZE, INV_OBJ_SIZE);
  if (m_inventory.getSelectedTile().getItem()->isStackable()) {
    drawText(mouseX, mouseY,
             to_string(m_inventory.getSelectedTile().getItem()->getAmount()),
             &window, INV_TILE_SIZE / 6, FONT_COLOR, FONT_PATH);
  }
}

void InventoryRenderer::render(sf::RenderWindow &window,
                               unordered_map<string, Sprite> sprites, Cam &cam,
                               int mouseX, int mouseY) {

  drawLowerBar(window, sprites, cam.getX(), cam.getY());
  if (m_inventory.isOpen()) {
    drawInv(window, sprites, cam.getX(), cam.getY());
  }
  drawSelectedItem(window, sprites, cam.getX(), cam.getY(), mouseX, mouseY);
}