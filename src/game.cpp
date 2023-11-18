#include "../include/game.hpp"

using namespace std;
using namespace sf;

Game::Game(RenderWindow &window)
    : m_window(window), m_char(CHARACTER_SAVE_PATH), m_charRenderer(m_char),
      m_cam(CAM_SAVE_PATH), m_inv(INVENTORY_SAVE_PATH), m_invRender(m_inv),
      m_mousePosCam(0, 0), m_map(MAP_PATH), m_mapRenderer(m_map), m_sound(),
      m_clock(), m_soundSettings(5), m_game_mode(2),
      m_day_night_cycle(DAY_NIGHT_CYCLE_CSV_PATH, DAY_NIGHT_CYCLE_IMG_PATH),
      m_menuPause(m_soundSettings, m_sound) {
  m_sprites = initSprites();
  m_buffers = initBuffers();
  m_sound.setVolume(m_soundSettings.getVolume());
}

void Game::run() {
  m_clock.restart();
  render();
  update();
}

void Game::reset() {
  m_char.setX(CHAR_DEFAULT_COORD_X);
  m_char.setY(CHAR_DEFAULT_COORD_Y);
  m_cam.reset(CHAR_DEFAULT_COORD_X, CHAR_DEFAULT_COORD_Y);
  Createmap map(MAP_WIDTH);
  map.generate();
  m_map = Map(MAP_PATH);
}

void Game::updateCam() {
  if (m_char.getX() - CAM_WIDTH / 2 > 0 &&
      m_char.getX() + CAM_WIDTH / 2 < m_map.get_width() * TILE_SIZE) {
    m_cam.setX(m_cam.getX() +
               (m_char.getX() + m_char.getWidth() / 4 - m_cam.getX()) / 20);
  }
  if (m_char.getY() + CAM_HEIGHT / 2 < m_map.get_height() * TILE_SIZE &&
      m_char.getY() - CAM_HEIGHT / 2 > 0) {
    m_cam.setY(m_cam.getY() +
               (m_char.getY() + m_char.getWidth() / 2 - m_cam.getY()) / 20);
  }
  m_window.setView(View(Vector2f(m_cam.getX(), m_cam.getY()),
                        Vector2f(CAM_WIDTH, CAM_HEIGHT)));
}

void Game::updateCollide() {
  m_map.collide(&m_char, m_cam.getX(), m_cam.getY());
  m_map.collide(&m_char);
}

void Game::updateMousePos() {
  Vector2f adjustedPos =
      m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)) -
      (m_window.getView().getCenter() - m_window.getView().getSize() / 2.f);

  m_mousePosCam.setX(adjustedPos.x);
  m_mousePosCam.setY(adjustedPos.y);

  m_mousePosWorld.setX(m_mousePosCam.getX() + m_cam.getX() - CAM_WIDTH / 2);
  m_mousePosWorld.setY(m_mousePosCam.getY() + m_cam.getY() - CAM_HEIGHT / 2);
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
  m_day_night_cycle.update();
  updateCam();
  updateMousePos();
  m_map.update(m_cam.getX(), m_cam.getY());
  m_char.update();
  updateCollide();
}

void Game::clean() {
  m_window.clear();
  m_map.clear();
  m_day_night_cycle.clear();
}

void Game::handleEvent(Event &event) {
  if (event.type == Event::Closed) {
    quit();
  } else if (event.type == Event::KeyPressed) {
    handleKeyPress(event.key.code);
  } else if (event.type == Event::KeyReleased) {
    handleKeyRelease(event.key.code);
  } else if (event.type == Event::MouseButtonPressed) {
    handleMouseButtonPressed(event.mouseButton);
  } else if (event.type == Event::MouseButtonReleased) {
    handleMouseButtonReleased(event.mouseButton);
  } else if (event.type == Event::MouseWheelScrolled) {
    handleMouseWheel(event.mouseWheelScroll.delta);
  }
}

void Game::handleSpacePress() {
  if (!m_char.getDirection()["up"] && !m_char.getDirection()["fall"]) {
    play_sound(&m_buffers["JUMP"], &m_sound);
    m_char.setJumping(true);
  }
}

void Game::handleKeyPress(sf::Keyboard::Key key) {
  static const map<Keyboard::Key, function<void()>> keyPressActions = {
      {Keyboard::Space, [&]() { handleSpacePress(); }},
      {Keyboard::Q, [&]() { m_char.setGoingLeft(true); }},
      {Keyboard::D, [&]() { m_char.setGoingRight(true); }},
      {Keyboard::Escape, [&]() { quit(); }},
      {Keyboard::E, [&]() { m_inv.addItem(toolMap["IRON_PICKAXE"]); }},
      {Keyboard::R, [&]() { m_char.hit(1); }},
      {Keyboard::F, [&]() { m_char.heal(1); }},
      {Keyboard::I, [&]() { m_inv.open(); }},
      {Keyboard::P, [&]() { m_menuPause.handlePause(); }},
      {Keyboard::Num1, [&]() { m_inv.setPosHand(0); }},
      {Keyboard::Num2, [&]() { m_inv.setPosHand(1); }},
      {Keyboard::Num3, [&]() { m_inv.setPosHand(2); }},
      {Keyboard::Quote, [&]() { m_inv.setPosHand(3); }},
      {Keyboard::Num5, [&]() { m_inv.setPosHand(4); }},
      {Keyboard::Dash, [&]() { m_inv.setPosHand(5); }},
      {Keyboard::Num7, [&]() { m_inv.setPosHand(6); }},
      {Keyboard::Num8, [&]() { m_inv.setPosHand(7); }},
      {Keyboard::Num9, [&]() { m_inv.setPosHand(8); }}};
  auto action = keyPressActions.find(key);
  if (action != keyPressActions.end()) {
    action->second();
  }
}

void Game::handleKeyRelease(sf::Keyboard::Key key) {
  static const map<Keyboard::Key, function<void()>> keyReleaseActions = {
      {Keyboard::Space, [&]() { m_char.setJumping(false); }},
      {Keyboard::Q, [&]() { m_char.setGoingLeft(false); }},
      {Keyboard::D, [&]() { m_char.setGoingRight(false); }}};
  auto action = keyReleaseActions.find(key);
  if (action != keyReleaseActions.end()) {
    action->second();
  }
}

void Game::handleMouseButtonPressed(sf::Event::MouseButtonEvent &event) {
  if (event.button == Mouse::Left) {
    if (!m_menuPause.isPause()) {
      if (m_inv.isOpen()) {
        m_inv.handleClick(m_mousePosWorld.getX(), m_mousePosWorld.getY(),
                          m_char.getX(), m_char.getY());
      } else {
        if (m_inv.getItemPosHand().getType() == "TOOL") {
          if (m_game_mode == 2) {
            m_map.setIsBreaking(true, m_mousePosWorld.getX(),
                                m_mousePosWorld.getY());
            m_map.resetBreakingClock(m_mousePosWorld.getX(),
                                     m_mousePosWorld.getY());
          } else {
            breakBlock();
          }
        }
      }
    } else {
      m_menuPause.handleMouseButtonPressed(event);
    }
  } else if (event.button == Mouse::Right) {
    if (!m_inv.isOpen()) {
      if (m_inv.getItemPosHand().getType() == "BLOCK") {
        putBlock();
      }
    }
  }
}

void Game::handleMouseButtonReleased(sf::Event::MouseButtonEvent &event) {
  if (event.button == Mouse::Left) {
    if (!m_inv.isOpen()) {
      m_map.setIsBreaking(false, m_mousePosWorld.getX(),
                          m_mousePosWorld.getY());
    }
  } else if (event.button == Mouse::Right) {
    // nothing for this time
  }
}

void Game::handleMouseWheel(float delta) {
  if (delta > 0) {
    m_inv.nextPosHand();
  } else {
    m_inv.prevPosHand();
  }
}

void Game::render() {
  m_window.clear(m_day_night_cycle.getColor());

  m_mapRenderer.render(m_window, m_sprites);

  m_charRenderer.render(m_window, m_sprites, m_cam.getX(), m_cam.getY());

  m_invRender.render(m_window, m_sprites, m_cam.getX(), m_cam.getY(),
                     m_mousePosWorld.getX(), m_mousePosWorld.getY());
  drawText(m_cam.getX() - CAM_WIDTH / 2, m_cam.getY() - CAM_HEIGHT / 2,
           "FPS : " +
               to_string((int)(1 / m_clock.getElapsedTime().asSeconds())),
           &m_window, 20, Color::White, FONT_PATH);

  m_menuPause.render(m_window, m_cam.getX(), m_cam.getY());

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
  m_cam.save(CAM_SAVE_PATH);
  m_day_night_cycle.save(DAY_NIGHT_CYCLE_CSV_PATH);
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
  play_sound(&m_buffers["BREAK"], &m_sound);
  int mouseX = m_mousePosWorld.getX();
  int mouseY = m_mousePosWorld.getY();
  if (m_game_mode = 2) {
    if (m_map.find_tile(mouseX, mouseY)->getBlock()->getId() != '0') {
      m_inv.addItem(*m_map.find_tile(mouseX, mouseY)->getBlock());
    }
  }
  m_map.supr_tile(mouseX, mouseY);
}
void Game::setGameVolume(float volume) { m_sound.setVolume(volume); }

bool Game::isPause() const { return m_menuPause.isPause(); }