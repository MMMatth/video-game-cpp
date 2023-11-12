#include "../include/game.hpp"
#include <SFML/Audio.hpp>
#include "../include/otherFunctions.hpp"

using namespace std;
using namespace sf;

Game::Game(RenderWindow &window)
    : m_window(window), m_char(CHARACTER_SAVE_PATH), m_charRenderer(m_char),
      m_posCam(m_char.getX(), m_char.getY()), m_inv(INVENTORY_SAVE_PATH),
      m_invRender(m_inv), m_mousePosCam(0, 0), m_map(MAP_PATH) {
  m_sprites = getSpriteMap();
}

void Game::run() {
  update();
  render();
}

void Game::updateCam() {
  m_posCam.setX(m_posCam.getX() +
                (m_char.getX() + m_char.getWidth() / 4 - m_posCam.getX()) / 20);
  m_posCam.setY(m_posCam.getY() +
                (m_char.getY() + m_char.getWidth() / 2 - m_posCam.getY()) / 20);
  m_window.setView(View(Vector2f(m_posCam.getX(), m_posCam.getY()),
                        Vector2f(CAM_WIDTH, CAM_HEIGHT)));
}

void Game::updateCollide() { m_map.collide(&m_char); }

void Game::updateMousePos() {
  Vector2i pixelPos = sf::Mouse::getPosition(m_window);
  Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);

  Vector2f camPos = m_window.getView().getCenter();
  Vector2f viewSize = m_window.getView().getSize();

  sf::Vector2f adjustedPos = worldPos - (camPos - viewSize / 2.f);
  m_mousePosCam.setX(adjustedPos.x);
  m_mousePosCam.setY(adjustedPos.y);

  m_mousePosWorld.setX(m_mousePosCam.getX() + m_posCam.getX());
  m_mousePosWorld.setY(m_mousePosCam.getY() + m_posCam.getY());
}

void Game::update() {
  updateCam();
  updateCollide();
  updateMousePos();
  m_char.update();
}

void Game::clean() {
  this->m_window.clear();
  this->m_map.clean();
}

void Game::handleEvent(Event &event) {
  if (event.type == Event::Closed) {
    quit();
  }
  if (event.type == Event::KeyPressed) {
    switch (event.key.code) {
    case Keyboard::Space:
      if (jumpClock.getElapsedTime() >= minimalTime) {
        Error(!buffer.loadFromFile(SOUND_JUMP), "Error loading sound");
        sound.setBuffer(buffer);
        sound.play();

        m_char.setJumping(true);

        jumpClock.restart();
      }
      break;
    case Keyboard::Q:
      // if(!buffer.loadFromFile(SOUND_MOVE)){
      //   cerr << "Error loading sound" << endl;
      // }
      // sound.setBuffer(buffer);
      // sound.play();
      m_char.setGoingLeft(true);
      break;
    case Keyboard::D:
      // if(!buffer.loadFromFile(SOUND_MOVE)){
      //   cerr << "Error loading sound" << endl;
      // }
      // sound.setBuffer(buffer);
      // sound.play();
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
    case Keyboard::Num4:
      m_inv.setPosHand(3);
      break;
    case Keyboard::Num5:
      m_inv.setPosHand(4);
      break;
    case Keyboard::Num6:
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
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
     Error(!buffer.loadFromFile(SOUND_BREAK_A_BLOCK), "Error loading sound");

      if (m_inv.isOpen())
        m_inv.handleClick(m_mousePosCam.getX(), m_mousePosCam.getY(),
                          m_posCam.getX(), m_posCam.getY());
      else {
        if (m_inv.getItemPosHand().getType() == "TOOL") {
          sound.setBuffer(buffer);
          sound.play();
          m_map.suprTile(m_mousePosWorld.getX() - CAM_WIDTH / 2,
                         m_mousePosWorld.getY() - CAM_HEIGHT / 2);
        }
      }
    }
    if (event.mouseButton.button == Mouse::Right) {
     Error(!buffer.loadFromFile(SOUND_PUT_A_BLOCK), "Error loading sound");

      if (!m_inv.isOpen()) {
        if (m_inv.getItemPosHand().getType() == "BLOCK") {
          sound.setBuffer(buffer);
          sound.play();
          m_map.addTile(blockMap[m_inv.getItemPosHand().getName()],
                        m_mousePosWorld.getX() - CAM_WIDTH / 2,
                        m_mousePosWorld.getY() - CAM_HEIGHT / 2);
        }
      }
    }
  }
}

void Game::render() {
  m_window.clear(SKY_COLOR);

  m_charRenderer.draw(m_window, m_sprites);

  for (int i = 0; i < m_map.getSize(); i++) {
    int x, y;
    x = m_map.getTile(i).getX();
    y = m_map.getTile(i).getY();
    if (m_map.getTile(i).estDansCam(m_posCam.getX(), m_posCam.getY(),
                                    WINDOW_WIDTH, WINDOW_HEIGHT)) {
      drawSprites(x, y, m_sprites[m_map.getTile(i).getBlock().getName()],
                  &m_window, TILE_SIZE, TILE_SIZE);
    }
  }
  m_invRender.render(m_window, m_sprites, m_posCam.getX(), m_posCam.getY(),
                     m_mousePosWorld.getX(), m_mousePosWorld.getY());
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
