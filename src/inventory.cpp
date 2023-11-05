#include "../include/inventory.hpp"

/* constructeur */
Inventory::Inventory(string csvPath)
    : m_is_open(false), m_pos_hand(0), m_selected_tile(InventoryTile()) {
  for (int row = 0; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      m_inventory[row][column] = InventoryTile();
    }
  }
  ifstream file(csvPath);
  string line;
  int row = 0, column = 0;
  if (file.is_open()) {
    while (getline(file, line)) {
      if (row != 0) {
        std::istringstream ss(line);
        std::string cell;
        std::string id;
        int x, y, amount;

        while (getline(ss, cell, ';')) {
          switch (column) {
          case 0:
            id = cell;
            break;
          case 1:
            x = stoi(cell);
            break;
          case 2:
            y = stoi(cell);
            break;
          case 3:
            amount = stoi(cell);
            break;
          default:
            std ::cerr << "Invalid csv file : " << csvPath << "\n";
            std ::exit(EXIT_FAILURE);
            break;
          }
          column++;
        }
        column = 0;

        /* we check the data */
        if (x > INVENTORY_HEIGHT || y > INVENTORY_WIDTH) { // we check the pos
          std::cerr << "Invalid position: (" << x << ", " << y
                    << ") is greater than the inventory size.\n";
        } else if (amount > MAX_STACK_SIZE ||
                   amount < 0) { // we check the amount
          std::cerr << "Invalid amount: " << amount
                    << " is greater than MAX_STACK_SIZE.\n";
          // on verifie que l'id est un clée de blockMap ou toolMap
        } else if (blockMap.find(id) != blockMap.end() &&
                   toolMap.find(id) != toolMap.end()) {
          std::cerr << "Invalid id: " << id << " is not a valid id.\n";
        } else { // if everything is ok, we add the item
          if (blockMap.find(id) != blockMap.end()) {
            m_inventory[x][y].setItem(blockMap[id]);
          } else if (toolMap.find(id) != toolMap.end()) {
            m_inventory[x][y].setItem(toolMap[id]);
          }
          m_inventory[x][y].setAmount(amount);
          if (amount > 1) {
            m_inventory[x][y].setIsStackable(true);
          }
        }
      }
      row++;
    }
  }
}

Inventory::Inventory()
    : m_is_open(false), m_pos_hand(0), m_selected_tile(InventoryTile()) {
  for (int row = 0; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      m_inventory[row][column] = InventoryTile();
      // m_inventory[row][column].setPos(row, column);
    }
  }
}
/* destructeur */
Inventory::~Inventory() {}
/* swap */
void Inventory::swapItem(Coord p1, Coord p2) {
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
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      if (m_inventory[i][j].getItem().getId() == item.getId() &&
          m_inventory[i][j].getItem().isStackable()) {
        int totalAmount =
            m_inventory[i][j].getItem().getAmount() + item.getAmount();
        if (totalAmount <= MAX_STACK_SIZE) {
          m_inventory[i][j].setAmount(totalAmount);
          return;
        } else {
          m_inventory[i][j].getItem().setAmount(MAX_STACK_SIZE);
          item.setAmount(totalAmount - MAX_STACK_SIZE);
        }
      }
      if (m_inventory[i][j].isEmpty()) {
        m_inventory[i][j].setItem(item);
        return;
      }
    }
  }
}
void Inventory::removeItem(Coord pos) {
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

/* handle */
void Inventory::handleClick(int mouseX, int mouseY, int camX, int camY) {
  if (m_is_open) {
    if (!getInventoryPosition(mouseX, mouseY, camX, camY)
             .isEqual(Coord(-1, -1))) {
      Coord pos = getInventoryPosition(mouseX, mouseY, camX, camY);
      int tileToMoveX = pos.getX();
      int tileToMoveY = pos.getY();
      swapItem(&m_inventory[tileToMoveX][tileToMoveY], &m_selected_tile);
    } else {
      cout << "hors inventaire" << endl;
    }
  }
}
/* getters */
Coord Inventory::getInventoryPosition(int mouseX, int mouseY, int camX,
                                      int camY) {
  int mx = camX - CAM_WIDTH / 2 + mouseX;
  int my = camY - CAM_HEIGHT / 2 + mouseY;

  if (!m_is_open) {
    cout << "getInventoryPosition : l'inventaire n'est pas ouvert" << endl;
    return Coord(-1, -1);
  }

  int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
  int y = camY - (INVENTORY_HEIGHT * INVENTORY_TILE_SIZE) / 2;

  for (int row = 0; row < INVENTORY_HEIGHT - 1; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      if (isWithinTile(mx, my, x + column * INVENTORY_TILE_SIZE,
                       y + row * INVENTORY_TILE_SIZE)) {
        return Coord(row, column);
      }
    }
  }
  y = camY - INVENTORY_TILE_SIZE + WINDOW_HEIGHT / 4;
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    if (isWithinTile(mx, my, x + column * INVENTORY_TILE_SIZE, y)) {
      return Coord(INVENTORY_HEIGHT - 1, column);
    }
  }
  return Coord(-1, -1);
}

string Inventory::toString() {
  string str = "\n";
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      str += "[";
      str += m_inventory[i][j].getItem().getId();
      str += "] ";
    }
    str += "\n";
  }
  return str;
}

void Inventory::save(string csvPath) {
  ofstream file(csvPath);
  if (file.is_open()) {
    file << "id;x;y;amount\n";
    for (int i = 0; i < INVENTORY_HEIGHT; i++) {
      for (int j = 0; j < INVENTORY_WIDTH; j++) {
        if (!m_inventory[i][j].isEmpty()) {
          file << m_inventory[i][j].getItem().getId() << ";" << i << ";" << j
               << ";" << m_inventory[i][j].getItem().getAmount() << "\n";
        }
      }
    }
  }
  file.close();
}