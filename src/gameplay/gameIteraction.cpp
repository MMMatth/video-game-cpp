#include "../../include/gameplay/game.hpp"

/* map iteraction */
void Game::putBlock(bool isBackground) {

  int mouseX = m_mousePosWorld.getX();
  int mouseY = m_mousePosWorld.getY();
  int charX = m_char.getX();
  int charY = m_char.getY();
  int charWidth = m_char.getWidth();
  int charHeight = m_char.getHeight();

  bool isMouseOutsideChar =
      mouseX > charX - TILE_SIZE && mouseX < charX + charWidth &&
      mouseY > charY - TILE_SIZE && mouseY < charY + charHeight + TILE_SIZE;

  if (!isMouseOutsideChar) {
    if (m_map.find_tile(mouseX, mouseY)->getBlock()->getId() == '0') {
      m_soundSettings->playSound("PUT_BLOCK");
      m_map.add_tile(blockMap[m_inv.getItemPosHand().getName()], mouseX, mouseY,
                     isBackground);
      if (m_game_mode == 2) {
        m_inv.removeItem(Coord(INVENTORY_HEIGHT - 1, m_inv.getPosHand()), 1);
      }
    }
  }
}

bool Game::is_breakable() {
  if (m_mousePosWorld.getX() < 0 || m_mousePosWorld.getY() < 0 ||
      m_mousePosWorld.getX() > m_map.get_width() * TILE_SIZE ||
      m_mousePosWorld.getY() > m_map.get_height() * TILE_SIZE) {
    return false;
  }
  Tile *tile = m_map.find_tile(m_mousePosWorld.getX(), m_mousePosWorld.getY());
  if (tile) {
    return true;
  }
  return false;
}

void Game::breakBlock() {
  int mouseX = m_mousePosWorld.getX();
  int mouseY = m_mousePosWorld.getY();
  if (is_breakable()) {
    if (m_map.find_tile(mouseX, mouseY)->getBlock()->getId() != '0') {
      if (m_game_mode == 2) {
        m_inv.addItem(*m_map.find_tile(mouseX, mouseY)->getBlock());
      }
      m_soundSettings->playSound("BREAK");
      m_map.supr_tile(mouseX, mouseY);
    }
  }
}

void Game::updateBreaking() {
  Tile *tile = m_map.find_tile(m_mousePosWorld.getX(), m_mousePosWorld.getY());
  if (tile) {
    if (tile->isBreaking() &&
        tile->getBreakingClock().getElapsedTime().asMilliseconds() >
            tile->getBlock()->getTimeToBreak()) {
      breakBlock();
      m_map.setIsBreaking(false, m_mousePosWorld.getX(),
                          m_mousePosWorld.getY());
    }
  }
}