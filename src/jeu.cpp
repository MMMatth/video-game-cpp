#include "../include/jeu.hpp"

using namespace std;
using namespace sf;

Jeu::Jeu(sf::Texture &texture)
    : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITRE_FENETRE),
      perso(0, 0,
            texture), // Passer la texture (spritesheet)
      posCam(0, 0), inv(), mousePosInCam(0, 0) {
  this->carte = Carte();
}

void Jeu::run() {
  Clock clock;
  Time timePerFrame = seconds(1.f / FPS_MAX);
  Time timeSinceLastUpdate = Time::Zero;
  while (window.isOpen()) {
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      event();
      update();
    }
    render();
  }
  clean();
}

bool Jeu::collisionAvecCarte(int x, int y) {
  if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
    return true;
  }

  return false;
}

void Jeu::updateCam() {
  posCam.setX(posCam.getX() +
              (perso.getX() + perso.getHauteur() / 4 - posCam.getX()) / 20);
  posCam.setY(posCam.getY() +
              (perso.getY() + perso.getHauteur() / 2 - posCam.getY()) / 20);
  window.setView(View(Vector2f(posCam.getX(), posCam.getY()),
                      Vector2f(CAM_WIDTH, CAM_HEIGHT)));
}

void Jeu::updateCollide() { carte.collide(&perso); }

void Jeu::updateMousePos() {
  sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
  sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

  sf::Vector2f camPos = window.getView().getCenter();
  sf::Vector2f viewSize = window.getView().getSize();

  sf::Vector2f adjustedPos = worldPos - (camPos - viewSize / 2.f);
  mousePosInCam.setX(adjustedPos.x);
  mousePosInCam.setY(adjustedPos.y);

  mousePosInWorld.setX(mousePosInCam.getX() + posCam.getX());
  mousePosInWorld.setY(mousePosInCam.getY() + posCam.getY());
}

void Jeu::update() {
  updateCam();
  updateCollide();
  updateMousePos();
  perso.update();
}

void Jeu::clean() {
  this->window.clear();
  this->carte.clean();
}

void Jeu::event() {
  Event event;
  while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
      window.close();
    }
    if (event.type == Event::KeyPressed) {
      switch (event.key.code) {
      case Keyboard::Up:
        perso.setJumping(true);
        break;
      case Keyboard::Left:
        perso.setGoingLeft(true);
        break;
      case Keyboard::Right:
        perso.setGoingRight(true);
        break;
      case Keyboard::Escape:
        window.close();
        break;
      case Keyboard::A:
        cout << "Inventaire : " << inv.toString() << endl;
        break;
      case Keyboard::E:
        // inv.addItem(blockMap[GRASS]);
        inv.addItem(toolMap[IRON_PICKAXE]);
        break;
      case Keyboard::R:
        inv.swapItem(Point(0, 0), Point(0, 1));
        break;
      case Keyboard::I:
        inv.setIsOpen();
        break;
      case Keyboard::Num1:
        inv.setPosHand(0);
        break;
      case Keyboard::Num2:
        inv.setPosHand(1);
        break;
      case Keyboard::Num3:
        inv.setPosHand(2);
        break;
      case Keyboard::Num4:
        inv.setPosHand(3);
        break;
      case Keyboard::Num5:
        inv.setPosHand(4);
        break;
      case Keyboard::Num6:
        inv.setPosHand(5);
        break;
      case Keyboard::Num7:
        inv.setPosHand(6);
        break;
      case Keyboard::Num8:
        inv.setPosHand(7);
        break;
      case Keyboard::Num9:
        inv.setPosHand(8);
        break;
      default:
        break;
      }
    }
    if (event.type == Event::KeyReleased) {
      switch (event.key.code) {
      case Keyboard::Up:
        perso.setJumping(false);
        break;
      case Keyboard::Left:
        perso.setGoingLeft(false);
        break;
      case Keyboard::Right:
        perso.setGoingRight(false);
        break;
      default:
        break;
      }
    }
    if (event.type == Event::MouseButtonPressed) {
      if (event.mouseButton.button == Mouse::Left) {
        inv.handleClick(mousePosInCam.getX(), mousePosInCam.getY(),
                        posCam.getX(), posCam.getY());
      }
    }
  }
}

void Jeu::render() {
  window.clear(COULEUR_CIEL);

  perso.draw(window);

  Texture spritesheet;
  assert(spritesheet.loadFromFile("../assets/img/spritesheet.png") &&
         "Erreur de chargement de la spritesheet.");
  for (auto it = blockMap.begin(); it != blockMap.end(); it++) {
    if (it->second.getName() != "air")
      sprites.emplace(make_pair(
          it->second.getName(),
          Sprite(spritesheet,
                 IntRect(it->second.getSpriteSheet().getX(),
                         it->second.getSpriteSheet().getY(), 16, 16))));
  }
  sprites.emplace(make_pair("invTileSelected",
                            Sprite(spritesheet, IntRect(0, 64, 22, 22))));
  sprites.emplace(
      make_pair("invTile", Sprite(spritesheet, IntRect(23, 64, 22, 22))));
  for (auto it = toolMap.begin(); it != toolMap.end(); it++) {
    sprites.emplace(
        make_pair(it->second.getName(),
                  Sprite(spritesheet,
                         IntRect(it->second.getSpriteSheet().getX(),
                                 it->second.getSpriteSheet().getY(), 16, 16))));
  }

  for (int i = 0; i < carte.getSize(); i++) {
    int x, y;
    x = carte.getTile(i).getX();
    y = carte.getTile(i).getY();

    if (carte.getTile(i).estDansCam(posCam.getX(), posCam.getY(), WINDOW_WIDTH,
                                    WINDOW_HEIGHT)) {
      drawSprites(x, y, sprites[carte.getTile(i).getBlock().getName()], &window,
                  TAILLE_CASE, TAILLE_CASE);
    }
  }
  inv.render(window, sprites, posCam.getX(), posCam.getY(),
             mousePosInWorld.getX(), mousePosInWorld.getY());
  // drawMiniMap();

  window.display();
}

int main(int arg, char **argv) {

  Texture spritesheet;
  if (!spritesheet.loadFromFile("../assets/img/personnage.png")) {
    cout << "Erreur de chargement de la spritesheet." << endl;
  }

  Jeu jeu(spritesheet);
  jeu.run();
  return 0;
}
