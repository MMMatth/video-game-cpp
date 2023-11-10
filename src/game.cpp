#include "../include/game.hpp"
#include "../include/characterRender.hpp"

using namespace std;
using namespace sf;

Game::Game()
    : m_window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITRE_FENETRE),
      m_char(0, 0, TAILLE_PERSONNAGE), 
      m_posCam(0, 0), m_inv("../assets/csv/inventory.csv"), m_mousePosCam(0, 0),
      m_invRender(m_inv),
      m_charRenderer(m_char, m_texture) { 
  m_map = Map();
  m_menu = true;
  m_game = false;
  
}

void Game::run() {
  Clock clock;
  Time timePerFrame = seconds(1.f / FPS_MAX);
  Time timeSinceLastUpdate = Time::Zero;

  Texture menuTexture;
  if (!menuTexture.loadFromFile("../assets/img/menu.JPEG")) {
    cout << "Erreur de chargement de la texture du menu." << endl;
  }
  Sprite menuSprite(menuTexture);
  menuSprite.setPosition(0, 0);

  while (m_window.isOpen()) {
    Event m_event;
    while (m_window.pollEvent(m_event)) {
      if (m_event.type == Event::Closed) {
        quit();
      }

      if (m_event.type == Event::KeyPressed) {
        switch (m_event.key.code) {
          case Keyboard::Space:
            if (m_menu) {
              m_menu = false;
              m_game = true;
              m_char.setX(0);
              m_char.setY(0);

            }
            break;
          case Keyboard::Escape:
            quit();
            break;
          default:
            break;
        }
      }
      // if (m_event.type == Event::MouseMoved && m_menu) {
      //   int mouseX = m_event.mouseMove.x;
      //   int mouseY = m_event.mouseMove.y;
      //   cout << "Position de la souris dans le menu : X=" << mouseX << ", Y=" << mouseY << endl;
      // }

      if (m_event.type == Event::MouseButtonPressed && m_menu) {
        if (m_event.mouseButton.button == Mouse::Left) {
          int mouseX = m_event.mouseButton.x;
          int mouseY = m_event.mouseButton.y;
          if (mouseX >= 630 && mouseX <= 787 && mouseY >= 216 && mouseY <= 295) {
            quit();
          }
          if (mouseX >= 32 && mouseX <= 230 && mouseY >= 214 && mouseY <= 297) {
            m_menu = false;
            m_game = true;
          }
          if (mouseX >= 318 && mouseX <= 508 && mouseY >= 131 && mouseY <= 210) {
            cout << "Nothing at the moment " << endl;
          }

        }
      }

      if (m_menu) {
        m_window.clear();
        m_window.draw(menuSprite);
        m_window.display();
      }

      while (m_game) {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
          timeSinceLastUpdate -= timePerFrame;
          event();
          update();
        }
        render();
      }
      if (!m_menu && !m_game) {
        quit();
      }
    }
  }

  cout << "Au revoir!" << endl;
}






bool Game::collisionAvecCarte(int x, int y) {
  if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
    return true;
  }

  return false;
}

void Game::updateCam() {
  m_posCam.setX(m_posCam.getX() +
                (m_char.getX() + m_char.getHauteur() / 4 - m_posCam.getX()) /
                    20);
  m_posCam.setY(m_posCam.getY() +
                (m_char.getY() + m_char.getHauteur() / 2 - m_posCam.getY()) /
                    20);
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

void Game::event() {
  Event event;
 
  while (m_window.pollEvent(event)) {
    if (event.type == Event::Closed) {
      m_game = false;
      quit();
    }
    if (event.type == Event::KeyPressed) {
      switch (event.key.code) {
      case Keyboard::Up:
        m_char.setJumping(true);
        break;
      case Keyboard::Left:
        m_char.setGoingLeft(true);
        break;
      case Keyboard::Right:
        m_char.setGoingRight(true);
        break;
      case Keyboard::Escape:
        m_game = false;
        quit();
        break;
      case Keyboard::E:
        // inv.addItem(blockMap[GRASS]);
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
      case Keyboard::Up:
        m_char.setJumping(false);
        break;
      case Keyboard::Left:
        m_char.setGoingLeft(false);
        break;
      case Keyboard::Right:
        m_char.setGoingRight(false);
        break;
      default:
        break;
      }
    }
    if (event.type == Event::MouseButtonPressed) {
      if (event.mouseButton.button == Mouse::Left) {
        m_inv.handleClick(m_mousePosCam.getX(), m_mousePosCam.getY(),
                          m_posCam.getX(), m_posCam.getY());
      }
    }
  }
}

void Game::render() {
  m_window.clear(COULEUR_CIEL);

  m_charRenderer.draw(m_window);
 
  m_sprites = getSpriteMap();

  for (int i = 0; i < m_map.getSize(); i++) {
    int x, y;
    x = m_map.getTile(i).getX();
    y = m_map.getTile(i).getY();

    if (m_map.getTile(i).estDansCam(m_posCam.getX(), m_posCam.getY(),
                                    WINDOW_WIDTH, WINDOW_HEIGHT)) {
      drawSprites(x, y, m_sprites[m_map.getTile(i).getBlock().getId()],
                  &m_window, TAILLE_CASE, TAILLE_CASE);
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

// void Game::menu(){
//   RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITRE_FENETRE);
//   while (window.isOpen()){
    
//     sf::Event event;
//     while (window.pollEvent(event)){
//       if (event.type == sf::Event::Closed) 
//         window.close();
//       }
   
//   }
// }

void Game::save() { m_inv.save("../assets/csv/inventory.csv"); }

int main(int arg, char **argv) {
  Game game;
  
  game.run();
  
  return 0;
}
