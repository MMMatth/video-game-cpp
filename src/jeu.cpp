#include "../include/jeu.hpp"

using namespace std;
using namespace sf;

Jeu::Jeu(sf::Texture &texture)
    : window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
      perso(0, 0,
            texture), // Passer la texture (spritesheet)
      posCam(0, 0), inv() {
  this->carte = Carte();
}

void Jeu::run() {
  miniWindow.setViewport(
      sf::FloatRect(0.9f, 0.1f, 0.2f, 0.25f)); // position du mini carte
  Clock clock;
  Time timePerFrame = seconds(1.f / 60.f);
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
  if (x < 0 || x >= TAILLE_FENETRE_X || y < 0 || y >= TAILLE_FENETRE_Y) {
    return true;
  }

  return false;
}

void Jeu::updateCam() {
  posCam.setX(posCam.getX() +
              (perso.getX() + perso.getHauteur() / 4 - posCam.getX()) / 20);
  posCam.setY(posCam.getY() +
              (perso.getY() + perso.getHauteur() / 2 - posCam.getY()) / 20);
  window.setView(
      View(Vector2f(posCam.getX(), posCam.getY()),
           Vector2f(TAILLE_FENETRE_X / 1.5, TAILLE_FENETRE_Y / 1.5)));
}

void Jeu::updateCollide() { carte.collide(&perso); }

void Jeu::update() {
  updateCam();
  updateCollide();
  perso.update();
}

void Jeu::clean() {
  this->window.clear();
  this->perso.clean();
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
        inv.addItem(blockMap[GRASS]);
        break;
      case Keyboard::R:
        inv.swapItem(0, 0, 0, 1);
        break;
      case Keyboard::I:
        if (inv.isOpen()) {
          inv.setIsOpen(false);
        } else if (!inv.isOpen()) {
          inv.setIsOpen(true);
        }
        break;
      case Keyboard::Num1:
        inv.setItemSelected(0);
        break;
      case Keyboard::Num2:
        inv.setItemSelected(1);
        break;
      case Keyboard::Num3:
        inv.setItemSelected(2);
        break;
      case Keyboard::Num4:
        inv.setItemSelected(3);
        break;
      case Keyboard::Num5:
        inv.setItemSelected(4);
        break;
      case Keyboard::Num6:
        inv.setItemSelected(5);
        break;
      case Keyboard::Num7:
        inv.setItemSelected(6);
        break;
      case Keyboard::Num8:
        inv.setItemSelected(7);
        break;
      case Keyboard::Num9:
        inv.setItemSelected(8);
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
  }
}

void Jeu::render() {
  window.clear(COULEUR_CIEL);

  perso.draw(window);

  Texture spritesheet, invTile;
  assert(spritesheet.loadFromFile("../assets/img/spritesheet.png") &&
         "Erreur de chargement de la spritesheet.");
  assert(invTile.loadFromFile("../assets/img/inventoryTile.png") &&
         "Erreur de chargement de la invTile.");
  for (auto it = blockMap.begin(); it != blockMap.end(); it++) {
    if (it->second.getName() != "air")
      sprites.emplace(make_pair(
          it->second.getName(),
          Sprite(spritesheet,
                 IntRect(it->second.getSpriteSheet().getX(),
                         it->second.getSpriteSheet().getY(), 16, 16))));
  }
  sprites.emplace(
      make_pair("invTileSelected", Sprite(invTile, IntRect(0, 0, 22, 22))));
  sprites.emplace(
      make_pair("invTile", Sprite(invTile, IntRect(23, 0, 22, 22))));

  for (int i = 0; i < carte.getSize(); i++) {
    int x, y;
    x = carte.getTile(i).getX();
    y = carte.getTile(i).getY();

    if (carte.getTile(i).estDansCam(posCam.getX(), posCam.getY(),
                                    TAILLE_FENETRE_X, TAILLE_FENETRE_Y)) {
      drawSprites(x, y, sprites[carte.getTile(i).getBlock().getName()], &window,
                  TAILLE_CASE, TAILLE_CASE);
    }
  }
  inv.render(window, sprites, posCam.getX(), posCam.getY());
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
