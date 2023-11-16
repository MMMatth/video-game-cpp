#include "../include/game.hpp"

using namespace std;
using namespace sf;

Game::Game(RenderWindow &window)
    : m_window(window), m_char(CHARACTER_SAVE_PATH), m_charRenderer(m_char),
      m_posCam(m_char.getX(), m_char.getY()), m_inv(INVENTORY_SAVE_PATH),
      m_invRender(m_inv), m_mousePosCam(0, 0), m_map(MAP_PATH),
      m_mapRenderer(m_map), m_sound(), m_clock(), m_mode(2),
      m_isBreaking(false), m_breakClock() {
  m_sprites = initSprites();
  m_buffers = initBuffers();
  m_sound.setVolume(VOLUME);
}

void Game::run() {
  m_clock.restart();
  render();
  update();
}
void Game::reset() {
  m_char.setX(MAP_WIDTH * TILE_SIZE / 2);
  m_char.setY(128);
  m_posCam.setX(MAP_WIDTH * TILE_SIZE / 2);
  m_posCam.setY(128);
  Createmap map(MAP_WIDTH);
  map.generate();
  m_map = Map(MAP_PATH);
}

void Game::updateCam() {
  if (m_char.getX() - CAM_WIDTH / 2 > 0 &&
      m_char.getX() + CAM_WIDTH / 2 < m_map.get_width() * TILE_SIZE) {
    m_posCam.setX(m_posCam.getX() +
                  (m_char.getX() + m_char.getWidth() / 4 - m_posCam.getX()) /
                      20);
  }
  if (m_char.getY() + CAM_HEIGHT / 2 < m_map.get_height() * TILE_SIZE &&
      m_char.getY() - CAM_HEIGHT / 2 > 0) {
    m_posCam.setY(m_posCam.getY() +
                  (m_char.getY() + m_char.getWidth() / 2 - m_posCam.getY()) /
                      20);
  }
  m_window.setView(View(Vector2f(m_posCam.getX(), m_posCam.getY()),
                        Vector2f(CAM_WIDTH, CAM_HEIGHT)));
}

void Game::updateCollide() {
  m_map.collide(&m_char, m_posCam.getX(), m_posCam.getY());
  m_map.collide(&m_char);
}

void Game::updateMousePos() {
  Vector2i pixelPos = sf::Mouse::getPosition(m_window);
  Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);

  Vector2f camPos = m_window.getView().getCenter();
  Vector2f viewSize = m_window.getView().getSize();

  sf::Vector2f adjustedPos = worldPos - (camPos - viewSize / 2.f);
  m_mousePosCam.setX(adjustedPos.x);
  m_mousePosCam.setY(adjustedPos.y);

  m_mousePosWorld.setX(m_mousePosCam.getX() + m_posCam.getX() - CAM_WIDTH / 2);
  m_mousePosWorld.setY(m_mousePosCam.getY() + m_posCam.getY() - CAM_HEIGHT / 2);
}

void Game::update() {
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
  updateCam();
  updateMousePos();
  m_map.update(m_posCam.getX(), m_posCam.getY());
  m_char.update();
  updateCollide();
}

void Game::clean() {
  m_window.clear();
  m_map.clear();
}

void Game::handleEvent(Event &event) {
  if (event.type == Event::Closed) {
    quit();
  }
  if (event.type == Event::KeyPressed) {
    switch (event.key.code) {
    case Keyboard::Space:
      if (!m_char.getDirection()["up"] && !m_char.getDirection()["fall"])
        play_sound(&m_buffers["JUMP"], &m_sound);
      m_char.setJumping(true);
      break;
    case Keyboard::Q:
      m_char.setGoingLeft(true);
      break;
    case Keyboard::D:
      m_char.setGoingRight(true);
      break;
    case Keyboard::Escape:
      quit();
      break;
    case Keyboard::E:
      m_inv.addItem(toolMap["IRON_PICKAXE"]);
      break;
    case Keyboard::I:
      m_inv.open();
      break;
    case Keyboard::Num1:
      m_inv.setPosHand(0);
      break;
    case Keyboard::Num2:
      m_inv.setPosHand(1);
      break;
    case Keyboard::Num3:
      m_inv.setPosHand(2);
      break;
    case Keyboard::Quote:
      m_inv.setPosHand(3);
      break;
    case Keyboard::Num5:
      m_inv.setPosHand(4);
      break;
    case Keyboard::Dash:
      m_inv.setPosHand(5);
      break;
    case Keyboard::Num7:
      m_inv.setPosHand(6);
      break;
    case Keyboard::Num8:
      m_inv.setPosHand(7);
      break;
    case Keyboard::Num9:
      m_inv.setPosHand(8);
      break;
    default:
      break;
    }
  }
  if (event.type == Event::KeyReleased) {
    switch (event.key.code) {
    case Keyboard::Space:
      m_char.setJumping(false);
      break;
    case Keyboard::Q:
      m_char.setGoingLeft(false);
      break;
    case Keyboard::D:
      m_char.setGoingRight(false);
      break;
    default:
      break;
    }
  }
  /* right click ( you can stay )*/
  if (Mouse::isButtonPressed(Mouse::Right)) {
    if (!m_inv.isOpen()) {
      if (m_inv.getItemPosHand().getType() == "BLOCK") {
        putBlock();
      }
    }
  }
  if (Mouse::isButtonPressed(Mouse::Left)) {
    if (!m_inv.isOpen()) {
      if (m_inv.getItemPosHand().getType() == "TOOL" && is_breakable() &&
          m_mode == 1) {
        breakBlock();
      }
    }
  }

  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (m_inv.isOpen()) {
        m_inv.handleClick(m_mousePosCam.getX(), m_mousePosCam.getY(),
                          m_posCam.getX(), m_posCam.getY());
      } else {
        if (m_inv.getItemPosHand().getType() == "TOOL" && m_mode == 2) {
          m_map.setIsBreaking(true, m_mousePosWorld.getX(),
                              m_mousePosWorld.getY());
          m_map.resetBreakingClock(m_mousePosWorld.getX(),
                                   m_mousePosWorld.getY());
        }
      }
    }
  }
  if (event.type == Event::MouseButtonReleased) {
    if (event.mouseButton.button == Mouse::Left) {
      if (m_inv.getItemPosHand().getType() == "TOOL" && m_mode == 2) {
        m_map.setIsBreaking(false, m_mousePosWorld.getX(),
                            m_mousePosWorld.getY());
      }
    }
  }
  if (event.type == Event::MouseWheelScrolled) {
    if (event.mouseWheelScroll.delta > 0) {
      if (m_inv.getPosHand() > 0)
        m_inv.setPosHand(m_inv.getPosHand() - 1);
      else
        m_inv.setPosHand(INVENTORY_WIDTH - 1);
    } else {
      if (m_inv.getPosHand() == INVENTORY_WIDTH - 1)
        m_inv.setPosHand(0);
      else
        m_inv.setPosHand(m_inv.getPosHand() + 1);
    }
  }
}

void Game::render() {
  m_window.clear(SKY_COLOR);

  m_charRenderer.draw(m_window, m_sprites);

  m_mapRenderer.render(m_window, m_sprites);

  m_invRender.render(m_window, m_sprites, m_posCam.getX(), m_posCam.getY(),
                     m_mousePosWorld.getX(), m_mousePosWorld.getY());
  drawText(m_posCam.getX() - CAM_WIDTH / 2, m_posCam.getY() - CAM_HEIGHT / 2,
           "FPS : " +
               to_string((int)(1 / m_clock.getElapsedTime().asSeconds())),
           &m_window, 20, Color::White, FONT_PATH);

  m_window.display();
}

void Game::quit() {
  save();
  m_window.close();
  clean();
}

void Game::save() {
  m_inv.save(INVENTORY_SAVE_PATH);
  m_map.save(MAP_PATH);
  m_char.save(CHARACTER_SAVE_PATH);
}

/* map iteraction */
void Game::putBlock() {

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
      play_sound(&m_buffers["PUT_BLOCK"], &m_sound);
      m_map.add_tile(blockMap[m_inv.getItemPosHand().getName()], mouseX,
                     mouseY);
      if (m_mode == 2) {
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
  play_sound(&m_buffers["BREAK"], &m_sound);
  int mouseX = m_mousePosWorld.getX();
  int mouseY = m_mousePosWorld.getY();
  if (m_mode = 2) {
    m_inv.addItem(*m_map.find_tile(mouseX, mouseY)->getBlock());
  }
  m_map.supr_tile(mouseX, mouseY);
}