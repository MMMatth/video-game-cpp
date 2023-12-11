#include "../../include/gameplay/game.hpp"

using namespace std;
using namespace sf;

// clang-format off
Game::Game(RenderWindow &window,
           unordered_map<string, Sprite> &sprites,
           SoundSettings &soundSettings, 
           bool save, bool input)
    : 
    m_window(window), 
    m_char( string(input ? INPUT_PATH : SAVE_PATH) + CHARACTER_SAVE_PATH, save, CHARACTER_MAX_LIFE), m_charRenderer(m_char),
    m_cam( string(input ? INPUT_PATH : SAVE_PATH) + CAM_SAVE_PATH, save), 
    m_inv(string(input ? INPUT_PATH : SAVE_PATH) + INVENTORY_SAVE_PATH, save), m_invRender(m_inv),
    m_mousePosCam(0, 0), 
    m_map( string(input ? INPUT_PATH : SAVE_PATH) + MAP_SAVE_PATH, save), m_mapRenderer(m_map),
    m_fpsCounter(10, 10), 
    // m_sound(sound), 
    m_soundSettings(&soundSettings),
    m_game_mode(2),
    m_day_night_cycle( string(input ? INPUT_PATH : SAVE_PATH) + DAY_NIGHT_CYCLE_CSV_PATH, DAY_NIGHT_CYCLE_IMG_PATH),
    m_menuPause(window,  soundSettings, false, [&]() { quit(); }), 
    m_monsters(m_map, m_char),
    m_save(save),
    m_menuEnd(window, soundSettings, false, [&]() { quitMenuEnd(); }, [&]() {restartGame(); }){
  m_sprites = sprites;
  // m_buffers = buffers;
}
// clang-format on

void Game::run() {
  render();
  update();
}

void Game::reset(bool save) {
  /* we reset the */
  m_char.reset(save, CHAR_DEFAULT_COORD_X, CHAR_DEFAULT_COORD_Y,
               string(SAVE_PATH) + CHARACTER_SAVE_PATH);
  /*we reset the monsters*/
  // m_monsters.reset();
  /* reset cam */
  m_cam.reset(CHAR_DEFAULT_COORD_X, CHAR_DEFAULT_COORD_Y);
  /* reset inventory*/
  m_inv.reset(save, string(SAVE_PATH) + INVENTORY_SAVE_PATH);
  /* we add items*/
  m_inv.addItem(toolMap["IRON_PICKAXE"]);
  m_inv.addItem(weaponMap["IRON_SWORD"]);
  /* reset day night cycle */
  m_day_night_cycle.reset(save, DEFAULT_TIME_DAY, DAY_NIGHT_CYCLE_IMG_PATH);
  /* reset map */
  m_map.reset(string(SAVE_PATH) + MAP_SAVE_PATH);       // we reset de map
  m_map = Map(string(SAVE_PATH) + MAP_SAVE_PATH, save); // we reload the map
}

void Game::updateCollide() {
  m_char.collide(&m_map, m_cam.getX(), m_cam.getY());
  m_monsters.collide(&m_map, m_cam.getX(), m_cam.getY());
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
  if (m_menuPause.isPause()) {
    m_menuPause.update();
  } else {

    updateMousePos();

    updateBreaking();

    if (!m_day_night_cycle.isDay()) {
      m_monsters.update();
    }

    m_day_night_cycle.update();

    m_cam.update(m_char.getX(), m_char.getY(), m_char.getWidth(),
                 m_char.getHeight(), m_map.get_width(), m_map.get_height(),
                 m_window);

    m_map.update(m_cam.getX(), m_cam.getY());

    m_char.update();

    m_fpsCounter.update();

    // m_sound.setVolume(m_soundSettings->getVolume());

    updateCollide();
  }

  if (m_char.getLife() == 0 && !m_menuEnd.isEnd()) {
    m_menuEnd.handle();
  }
}

void Game::clean() {}

void Game::handleEvent(Event &event) {
  if (m_menuPause.isPause()) {
    m_menuPause.handleEvent(event);
  } else if (m_menuEnd.isEnd()) {
    m_menuEnd.handleEvent(event);
  } else {

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
}

void Game::handleSpacePress() {
  if (!m_char.getDirection()["up"] && !m_char.getDirection()["fall"]) {
    m_soundSettings->playSound("JUMP");
    m_char.setDirection("jump", true);
  }
}

void Game::handleKeyPress(sf::Keyboard::Key key) {
  static const map<Keyboard::Key, function<void()>> keyPressActions = {
      {Keyboard::Space, [&]() { handleSpacePress(); }},
      {Keyboard::Q, [&]() { m_char.setDirection("left", true); }},
      {Keyboard::D, [&]() { m_char.setDirection("right", true); }},
      {Keyboard::Escape, [&]() { quit(); }},
      {Keyboard::E, [&]() { m_inv.addItem(toolMap["IRON_PICKAXE"]); }},
      {Keyboard::R, [&]() { m_char.hit(1); }},
      {Keyboard::F, [&]() { m_char.heal(1); }},
      {Keyboard::I, [&]() { m_inv.open(); }},
      {Keyboard::P, [&]() { m_menuPause.handle(); }},
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
      {Keyboard::Space, [&]() { m_char.setDirection("jump", false); }},
      {Keyboard::Q, [&]() { m_char.setDirection("left", false); }},
      {Keyboard::D, [&]() { m_char.setDirection("right", false); }}};
  auto action = keyReleaseActions.find(key);
  if (action != keyReleaseActions.end()) {
    action->second();
  }
}

void Game::handleMouseButtonPressed(sf::Event::MouseButtonEvent &event) {
  if (event.button == Mouse::Left) {
    if (m_inv.isOpen()) {
      m_inv.handleLeftClick(m_mousePosWorld.getX(), m_mousePosWorld.getY(),
                            m_cam.getX(), m_cam.getY());
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
  } else if (event.button == Mouse::Right) {
    if (m_inv.isOpen()) {
      m_inv.handleRightClick(m_mousePosWorld.getX(), m_mousePosWorld.getY(),
                             m_cam.getX(), m_cam.getY());
    } else {
      if (m_inv.getItemPosHand().getName() == "IRON_SWORD") {
        m_monsters.setKillAmonster(true);
      }
      if (m_inv.getItemPosHand().getType() == "BLOCK") {
        putBlock(false); // we add a not background block
      }
    }
  } else if (event.button == Mouse::Middle) {
    if (m_inv.getItemPosHand().getType() == "BLOCK") {
      putBlock(true); // we add a background block
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
    if (m_inv.getItemPosHand().getName() == "IRON_SWORD") {
      m_monsters.setKillAmonster(false);
    }
  }
}

void Game::handleMouseWheel(float delta) {
  if (delta < 0) {
    m_inv.nextPosHand();
  } else {
    m_inv.prevPosHand();
  }
}

void Game::render() {
  if (m_menuEnd.isEnd()) {
    m_window.clear(m_day_night_cycle.getColor());
    m_menuEnd.render(m_cam);
    m_window.display();
  } else {
    /* the sky */
    m_window.clear(m_day_night_cycle.getColor());

    m_charRenderer.render(m_window, m_sprites, "CHAR", NUM_FRAMES);

    m_mapRenderer.render(m_window, m_sprites);

    if (!m_day_night_cycle.isDay()) {
      m_monsters.render(m_window, m_sprites, NUM_FRAMES_MONSTER);
    }

    m_invRender.render(m_window, m_sprites, m_cam, m_mousePosWorld.getX(),
                       m_mousePosWorld.getY());

    /* hud */
    m_mapRenderer.renderMiniMap(m_window, m_sprites, m_cam.getX(),
                                m_cam.getY());
    m_charRenderer.renderLifeBar(m_window, m_sprites, m_cam.getX(),
                                 m_cam.getY());
    m_fpsCounter.render(m_window, m_cam);

    m_menuPause.render(m_cam);

    m_window.display();
  }
}

void Game::quit() {
  if (m_save) {
    save();
  }
  m_window.close();
  clean();
}

void Game::save() {
  m_inv.save(string(SAVE_PATH) + INVENTORY_SAVE_PATH);
  m_map.save(string(SAVE_PATH) + MAP_SAVE_PATH);
  m_cam.save(string(SAVE_PATH) + CAM_SAVE_PATH);
  m_day_night_cycle.save(string(SAVE_PATH) + DAY_NIGHT_CYCLE_CSV_PATH);
  m_char.save(string(SAVE_PATH) + CHARACTER_SAVE_PATH);
}

void Game::setGameVolume(float volume) { m_soundSettings->setVolume(volume); }

bool Game::isPause() { return m_menuPause.isPause(); }

void Game::restartGame() {
  reset(true);
  m_menuEnd.setIsEnd();
}

void Game::quitMenuEnd() {
  reset(true);
  quit();
}
