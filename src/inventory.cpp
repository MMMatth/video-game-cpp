#include "../include/inventory.hpp"

Inventory::Inventory(string csvPath) {}

Inventory::Inventory() : m_is_open(false), m_object_selected(0) {
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      m_inventory[i][j] = InventoryTile();
    }
  }
}

void Inventory::swapItem(int x1, int y1, int x2, int y2) {
  assert(
      (x1 >= 0 && x1 < INVENTORY_HEIGHT && y1 >= 0 && y1 < INVENTORY_WIDTH) &&
      "swapItem : valeur depasse la taille de l'inventaire");
  assert(
      (x2 >= 0 && x2 < INVENTORY_HEIGHT && y2 >= 0 && y2 < INVENTORY_WIDTH) &&
      "swapItem : valeur depasse la taille de l'inventaire");
  InventoryTile tmp = m_inventory[x1][y1];
  m_inventory[x1][y1] = m_inventory[x2][y2];
  m_inventory[x2][y2] = tmp;
}
void Inventory::addItem(Item item) {
  bool itemAdded = false;
  int i = 0;
  while (i < INVENTORY_HEIGHT && !itemAdded) {
    int j = 0;
    while (j < INVENTORY_WIDTH && !itemAdded) {
      if (m_inventory[i][j].isEmpty()) {
        m_inventory[i][j].setItem(item);
        itemAdded = true;
      }
      j++;
    }
    i++;
  }
}

void Inventory::removeItem(int x, int y) {
  assert((x >= 0 && x < INVENTORY_HEIGHT && y >= 0 && y < INVENTORY_WIDTH) &&
         "removeItem : valeur depasse la taille de l'inventaire");
  m_inventory[x][y].setItem(Item());
}

void Inventory::drawInventoryItem(sf::RenderWindow &window,
                                  unordered_map<string, Sprite> sprites, int x,
                                  int y, int row, int column) {
  drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["invTile"], &window,
              INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
  drawSprites(x + column * INVENTORY_TILE_SIZE +
                  (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
              y + (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
              sprites[m_inventory[row][column].getItem().getName()], &window,
              INVENTORY_OBJECT_SIZE, INVENTORY_OBJECT_SIZE);
  if (column == m_object_selected && row == 0)
    drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["invTileSelected"],
                &window, INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
}

void Inventory::drawLowerBar(sf::RenderWindow &window,
                             unordered_map<string, Sprite> sprites, int persoX,
                             int persoY) {
  int x = persoX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = persoY - INVENTORY_TILE_SIZE + TAILLE_FENETRE_Y / 4;
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    drawInventoryItem(window, sprites, x, y, 0, column);
  }
}

void Inventory::drawInv(sf::RenderWindow &window,
                        unordered_map<string, Sprite> sprites, int persoX,
                        int persoY) {
  int x = persoX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = persoY - ((INVENTORY_WIDTH - 1) * INVENTORY_TILE_SIZE) / 2;
  for (int row = 1; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      drawInventoryItem(window, sprites, x, y + row * INVENTORY_TILE_SIZE, row,
                        column);
    }
  }
}
void Inventory::render(sf::RenderWindow &window,
                       unordered_map<string, Sprite> sprites, int persoX,
                       int persoY) {
  drawLowerBar(window, sprites, persoX, persoY);
  if (m_is_open) {
    drawInv(window, sprites, persoX, persoY);
  }
}

string Inventory::toString() {
  string str = "\n";
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      str += "[";
      str += m_inventory[i][j].getItem().getName();
      str += "] ";
    }
    str += "\n";
  }
  return str;
}

// void inventory::drawInv(){

// }
