#include "../include/inventory.hpp"

/* constructeur */
Inventory::Inventory(string csvPath) {}
Inventory::Inventory()
    : m_is_open(false), m_pos_hand(0), m_selected_tile(InventoryTile()) {
  for (int row = 0; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      m_inventory[row][column] = InventoryTile();
      m_inventory[row][column].setPos(row, column);
    }
  }
}
/* destructeur */
Inventory::~Inventory() {}
/* swap */
void Inventory::swapItem(Point p1, Point p2) {
  assert((p1.getX() >= 0 && p1.getX() < INVENTORY_HEIGHT && p1.getY() >= 0 &&
          p1.getY() < INVENTORY_WIDTH) &&
         "swapItem : valeur depasse la taille de l'inventaire");
  assert((p2.getX() >= 0 && p2.getX() < INVENTORY_HEIGHT && p2.getY() >= 0 &&
          p2.getY() < INVENTORY_WIDTH) &&
         "swapItem : valeur depasse la taille de l'inventaire");
  m_inventory[p1.getX()][p1.getY()].swapItem(m_inventory[p2.getX()][p2.getY()]);
}
void Inventory::swapItem(InventoryTile *t1, InventoryTile *t2) {
  if (t1->isEmpty() && !t2->isEmpty()) {
    t2->setIsEmpty(true);
    t1->setIsEmpty(false);
  } else if (t2->isEmpty() && !t1->isEmpty()) {
    t1->setIsEmpty(true);
    t2->setIsEmpty(false);
  }
  t1->swapItem(*t2);
}
/* add and remove item*/
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
void Inventory::removeItem(Point pos) {
  assert((pos.getX() >= 0 && pos.getX() < INVENTORY_HEIGHT && pos.getY() >= 0 &&
          pos.getY() < INVENTORY_WIDTH) &&
         "removeItem : valeur depasse la taille de l'inventaire");
  m_inventory[pos.getX()][pos.getY()].setItem(Item());
}
/* render */
bool isWithinTile(int mx, int my, int x, int y) {
  return mx >= x && mx <= x + INVENTORY_TILE_SIZE && my >= y &&
         my <= y + INVENTORY_TILE_SIZE;
}
void Inventory::drawItem(sf::RenderWindow &window,
                         unordered_map<string, Sprite> sprites, int x, int y,
                         int row, int column) {
  drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["invTile"], &window,
              INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
  if (!m_inventory[row][column].isEmpty())
    drawSprites(x + column * INVENTORY_TILE_SIZE +
                    (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
                y + (INVENTORY_TILE_SIZE - INVENTORY_OBJECT_SIZE) / 2,
                sprites[m_inventory[row][column].getItem().getName()], &window,
                INVENTORY_OBJECT_SIZE, INVENTORY_OBJECT_SIZE);
  if (column == m_pos_hand && row == INVENTORY_HEIGHT - 1)
    drawSprites(x + column * INVENTORY_TILE_SIZE, y, sprites["invTileSelected"],
                &window, INVENTORY_TILE_SIZE, INVENTORY_TILE_SIZE);
}

void Inventory::drawLowerBar(sf::RenderWindow &window,
                             unordered_map<string, Sprite> sprites, int camX,
                             int camY) {
  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY - INVENTORY_TILE_SIZE + WINDOW_HEIGHT / 4;
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    drawItem(window, sprites, x, y, INVENTORY_HEIGHT - 1, column);
  }
}

void Inventory::drawInv(sf::RenderWindow &window,
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

void Inventory::drawSelectedItem(sf::RenderWindow &window,
                                 unordered_map<string, Sprite> sprites,
                                 int camX, int camY, int mouseX, int mouseY) {
  drawSprites(mouseX - CAM_WIDTH / 2, mouseY - CAM_HEIGHT / 2,
              sprites[m_selected_tile.getItem().getName()], &window, 32, 32);
}

void Inventory::render(sf::RenderWindow &window,
                       unordered_map<string, Sprite> sprites, int camX,
                       int camY, int mouseX, int mouseY) {

  drawLowerBar(window, sprites, camX, camY);
  if (m_is_open) {
    drawInv(window, sprites, camX, camY);
  }
  drawSelectedItem(window, sprites, camX, camY, mouseX, mouseY);
}

/* handle */
void Inventory::handleClick(int mouseX, int mouseY, int camX, int camY) {
  if (m_is_open) {
    if (!getInventoryPosition(mouseX, mouseY, camX, camY)
             .isEqual(Point(-1, -1))) {
      Point pos = getInventoryPosition(mouseX, mouseY, camX, camY);
      int tileToMoveX = pos.getX();
      int tileToMoveY = pos.getY();
      swapItem(&m_inventory[tileToMoveX][tileToMoveY], &m_selected_tile);
    } else {
      cout << "hors inventaire" << endl;
    }
  }
}
/* getters */
Point Inventory::getInventoryPosition(int mouseX, int mouseY, int camX,
                                      int camY) {
  int mx = camX - CAM_WIDTH / 2 + mouseX;
  int my = camY - CAM_HEIGHT / 2 + mouseY;

  if (!m_is_open) {
    cout << "getInventoryPosition : l'inventaire n'est pas ouvert" << endl;
    return Point(-1, -1);
  }

  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY - (INVENTORY_HEIGHT * INVENTORY_TILE_SIZE) / 2;

  for (int row = 0; row < INVENTORY_HEIGHT - 1; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      if (isWithinTile(mx, my, x + column * INVENTORY_TILE_SIZE,
                       y + row * INVENTORY_TILE_SIZE)) {
        return Point(row, column);
      }
    }
  }
  y = camY - INVENTORY_TILE_SIZE + WINDOW_HEIGHT / 4;
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    if (isWithinTile(mx, my, x + column * INVENTORY_TILE_SIZE, y)) {
      return Point(INVENTORY_HEIGHT - 1, column);
    }
  }
  return Point(-1, -1);
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
