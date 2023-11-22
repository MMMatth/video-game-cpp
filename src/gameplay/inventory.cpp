#include "../../include/gameplay/inventory.hpp"

/* constructor  */
Inventory::Inventory(string csvPath)
    : m_is_open(false), m_pos_item_hand(0), m_selected_tile(InventoryTile()),
      m_save(true) {
  for (int row = 0; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      m_inventory[row][column] = InventoryTile();
    }
  }
  if (!loadFromCSV(csvPath)) {
    cerr << "Failed to load csv from " << csvPath << "so inv is empty" << endl;
  };
}

Inventory::Inventory()
    : m_is_open(false), m_pos_item_hand(0), m_selected_tile(InventoryTile()),
      m_save(false) {
  for (int row = 0; row < INVENTORY_HEIGHT; row++) {
    for (int column = 0; column < INVENTORY_WIDTH; column++) {
      m_inventory[row][column] = InventoryTile();
    }
  }
}

bool Inventory::loadFromCSV(const string &csvPath) {
  ifstream file(csvPath);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << csvPath << "\n";
    return false;
  }
  string line;
  int row = 0;
  while (getline(file, line)) {
    if (row != 0) { // Skip header row
      istringstream ss(line);
      string cell;
      string id;
      int x, y, amount;
      int column = 0;

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
          cerr << "Inv: invalide csv file\n";
          return false;
          break;
        }
        column++;
      }

      if (x > INVENTORY_HEIGHT || y > INVENTORY_WIDTH) {
        cerr << "Invalid position: (" << x << ", " << y
             << ") is greater than the inventory size.\n";
      } else if (amount > MAX_STACK_SIZE || amount < 0) {
        cerr << "Invalid amount: " << amount
             << " is greater than MAX_STACK_SIZE.\n";
      } else if (blockMap.find(id) == blockMap.end() &&
                 toolMap.find(id) == toolMap.end()) {
        cerr << "Invalid id: " << id << " is not a valid id.\n";
      } else {
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
  file.close();
  return true; // all is ok
}

/* swap function */
void Inventory::swapItem(InventoryTile *tile_who_received,
                         InventoryTile *tile_who_give) {
  tile_who_received->swapWith(*tile_who_give);
}
/* add and remove item*/
void Inventory::addItem(Item item) {
  // we browse a first time the inventory to see if we can stack the item
  for (int column = 0; column < INVENTORY_HEIGHT; column++) {
    for (int row = 0; row < INVENTORY_WIDTH; row++) {
      // if we found an item with the same name and it's stackable
      if (m_inventory[column][row].getItem()->getName() == item.getName() &&
          m_inventory[column][row].getItem()->isStackable()) {
        int totalAmount =
            m_inventory[column][row].getItem()->getAmount() + item.getAmount();
        if (totalAmount <= MAX_STACK_SIZE) {
          m_inventory[column][row].setAmount(totalAmount);
          return;
        } else {
          m_inventory[column][row].getItem()->setAmount(MAX_STACK_SIZE);
          item.setAmount(totalAmount - MAX_STACK_SIZE);
          return;
        }
      }
    }
  }
  // we browse a second time the inventory to see if we can add the item
  for (int column = 0; column < INVENTORY_HEIGHT; column++) {
    for (int row = 0; row < INVENTORY_WIDTH; row++) {
      if (m_inventory[column][row].isEmpty()) {
        m_inventory[column][row].setItem(item);
        return;
      }
    }
  }
  cerr << "addItem : the inventory is full" << endl;
}
void Inventory::removeItem(Coord pos, int amount) {
  assert((pos.getX() >= 0 && pos.getX() < INVENTORY_HEIGHT && pos.getY() >= 0 &&
          pos.getY() < INVENTORY_WIDTH) &&
         "removeItem : valeur depasse la taille de l'inventaire");
  if (m_inventory[pos.getX()][pos.getY()].getItem()->getAmount() > amount) {
    m_inventory[pos.getX()][pos.getY()].getItem()->setAmount(
        m_inventory[pos.getX()][pos.getY()].getItem()->getAmount() - amount);
  } else if (m_inventory[pos.getX()][pos.getY()].getItem()->getAmount() ==
             amount) {
    m_inventory[pos.getX()][pos.getY()].setItem(Item());
    m_inventory[pos.getX()][pos.getY()].setIsEmpty(true);
  } else {
    cerr << "removeItem : the amount is greater than the amount of the item"
         << endl;
  }
}

bool isOverTile(int mx, int my, int x, int y) {
  return mx >= x && mx <= x + INVENTORY_TILE_SIZE && my >= y &&
         my <= y + INVENTORY_TILE_SIZE;
}

/* handle */
void Inventory::handleClick(int mouseX, int mouseY, int camX, int camY) {
  if (m_is_open && isOverInv(mouseX, mouseY, camX, camY)) {
    Coord coord_tile_selected = getTileCoord(mouseX, mouseY, camX, camY);
    InventoryTile *tile_selected =
        &m_inventory[coord_tile_selected.getX()][coord_tile_selected.getY()];
    swapItem(&m_selected_tile, tile_selected);
  } else {
    cerr << "handleClick : the inventory is not open or the mouse is not over "
            "the inventory"
         << endl;
  }
}
/* setter */
void Inventory::open() {
  if (m_is_open) {
    m_is_open = false;
    addItem(*m_selected_tile.getItem());
    m_selected_tile = InventoryTile();
  } else {
    m_is_open = true;
  }
}

void Inventory::setPosHand(int indice) {
  if (indice >= 0 && indice < INVENTORY_WIDTH) {
    m_pos_item_hand = indice;
  } else {
    cerr << "setPosHand : the indice is not in the inventory" << endl;
  }
}
void Inventory::nextPosHand() {
  if (m_pos_item_hand < INVENTORY_WIDTH - 1) {
    m_pos_item_hand++;
  } else {
    m_pos_item_hand = 0;
  }
}
void Inventory::prevPosHand() {
  if (m_pos_item_hand > 0) {
    m_pos_item_hand--;
  } else {
    m_pos_item_hand = INVENTORY_WIDTH - 1;
  }
}

/* getters */
bool Inventory::isOverInv(int mx, int my, int camX, int camY) {
  if (!m_is_open) {
    cerr << "isOverInv : inv is not open " << endl;
    return false;
  }
  // we check we are in the inventory ( not the low bar)
  for (int row = 0; row < INVENTORY_WIDTH; row++) {
    for (int column = 0; column < INVENTORY_HEIGHT - 1; column++) {
      if (isOverTile(mx, my,
                     camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2 +
                         row * INVENTORY_TILE_SIZE,
                     camY - (INVENTORY_HEIGHT * INVENTORY_TILE_SIZE) / 2 +
                         column * INVENTORY_TILE_SIZE)) {
        return true;
      }
    }
  }
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    if (isOverTile(mx, my,
                   camX - X_LOWER_BAR_OFFSET + column * INVENTORY_TILE_SIZE,
                   camY - Y_LOWER_BAR_OFFSET)) {
      return true;
    }
  }

  return false;
}

Coord Inventory::getTileCoord(int mouseX, int mouseY, int camX, int camY) {
  for (int row = 0; row < INVENTORY_WIDTH; row++) {
    for (int column = 0; column < INVENTORY_HEIGHT - 1; column++) {
      if (isOverTile(mouseX, mouseY,
                     camX - X_INV_OFFSET + row * INVENTORY_TILE_SIZE,
                     camY - Y_INV_OFFSET + column * INVENTORY_TILE_SIZE)) {
        return Coord(column, row);
      }
    }
  }
  for (int column = 0; column < INVENTORY_WIDTH; column++) {
    if (isOverTile(mouseX, mouseY,
                   camX - X_LOWER_BAR_OFFSET + column * INVENTORY_TILE_SIZE,
                   camY - Y_LOWER_BAR_OFFSET)) {
      return Coord(INVENTORY_HEIGHT - 1, column);
    }
  }
  return Coord(-1, -1); // if the mouse is not over a tile
}

InventoryTile Inventory::getSelectedTile() { return m_selected_tile; }

InventoryTile Inventory::getTile(Coord tile_coord) {
  return m_inventory[tile_coord.getX()][tile_coord.getY()];
}

int Inventory::getPosHand() { return m_pos_item_hand; }

Item Inventory::getItemAt(Coord tile_coord) {
  return *m_inventory[tile_coord.getX()][tile_coord.getY()].getItem();
}

bool Inventory::isOpen() { return m_is_open; }

Item Inventory::getItemPosHand() {
  return *m_inventory[INVENTORY_HEIGHT - 1][m_pos_item_hand].getItem();
}

/* other */

void Inventory::save(string csvPath) {
  if (m_save) {
    ofstream file(csvPath);
    if (file.is_open()) {
      file << "id;x;y;amount\n";
      for (int i = 0; i < INVENTORY_HEIGHT; i++) {
        for (int j = 0; j < INVENTORY_WIDTH; j++) {
          if (!m_inventory[i][j].isEmpty() &&
              m_inventory[i][j].getItem() != NULL) {
            file << m_inventory[i][j].getItem()->getName() << ";" << i << ";"
                 << j << ";" << m_inventory[i][j].getItem()->getAmount()
                 << "\n";
          }
        }
      }
    }
    file.close();
  }
}

string Inventory::toString() {
  string str = "\n";
  for (int i = 0; i < INVENTORY_HEIGHT; i++) {
    for (int j = 0; j < INVENTORY_WIDTH; j++) {
      str += "[";
      str += m_inventory[i][j].isEmpty() ? " " : "x";
      str += "] ";
    }
    str += "\n";
  }
  str += "[ " + string(m_selected_tile.isEmpty() ? " " : "x") + " ]\n";
  str += "pos_hand : " + to_string(m_pos_item_hand) + "\n";
  return str;
}