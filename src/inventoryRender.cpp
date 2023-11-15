#include "../include/inventoryRender.hpp"

void InventoryRenderer::drawItem(sf::RenderWindow &window,
                                 unordered_map<string, Sprite> sprites, int x,
                                 int y, int row, int column) {
  drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["TILE"], &window,
              INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
  if (!m_inventory.getTile(Coord(row, column)).isEmpty()) {
    drawSprites(x + column * INVENTORY_TILE_SIZE +
                    (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
                y + (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
                sprites[m_inventory.getItemAt(Coord(row, column)).getName()],
                &window, INVENTORY_OBJECT_SIZE, INVENTORY_OBJECT_SIZE);
    if (m_inventory.getItemAt(Coord(row, column)).isStackable()) {
      drawText(x + column * INVENTORY_TILE_SIZE +
                   (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
               y + (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
               to_string(m_inventory.getItemAt(Coord(row, column)).getAmount()),
               &window, INVENTORY_TILE_SIZE / 6, FONT_COLOR, FONT_PATH);
    }
  }
  if (column == m_inventory.getPosHand() && row == INVENTORY_HEIGHT - 1)
    drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["SELECTED_TILE"],
                &window, INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
}

void InventoryRenderer::drawLowerBar(sf::RenderWindow &window,
                                     unordered_map<string, Sprite> sprites,
                                     int camX, int camY) {
  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY + CAM_HEIGHT / 2 - INVENTORY_TILE_SIZE * 2;
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    drawItem(window, sprites, x, y, INVENTORY_HEIGHT - 1, column);
  }
}

void InventoryRenderer::drawInv(sf::RenderWindow &window,
                                unordered_map<string, Sprite> sprites, int camX,
                                int camY) {
  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY - (INVENTORY_HEIGHT * INVENTORY_TILE_SIZE) / 2;
  for (int row = 0; row < INVENTORY_HEIGHT - 1; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      drawItem(window, sprites, x, y + row * INVENTORY_TILE_SIZE, row, column);
    }
  }
}

void InventoryRenderer::drawSelectedItem(sf::RenderWindow &window,
                                         unordered_map<string, Sprite> sprites,
                                         int camX, int camY, int mouseX,
                                         int mouseY) {
  drawSprites(mouseX, mouseY,
              sprites[m_inventory.getSelectedTile().getItem().getName()],
              &window, INVENTORY_OBJECT_SIZE, INVENTORY_OBJECT_SIZE);
  if (m_inventory.getSelectedTile().getItem().isStackable()) {
    drawText(mouseX, mouseY,
             to_string(m_inventory.getSelectedTile().getItem().getAmount()),
             &window, INVENTORY_TILE_SIZE / 6, FONT_COLOR, FONT_PATH);
  }
}

void InventoryRenderer::render(sf::RenderWindow &window,
                               unordered_map<string, Sprite> sprites, int camX,
                               int camY, int mouseX, int mouseY) {

  drawLowerBar(window, sprites, camX, camY);
  if (m_inventory.isOpen()) {
    drawInv(window, sprites, camX, camY);
  }
  drawSelectedItem(window, sprites, camX, camY, mouseX, mouseY);
}