#include "../include/jeu.hpp"

using namespace std;
using namespace sf;

Jeu::Jeu(sf::Texture &texture)
    : window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
      perso(0, 0,
            texture), // Passer la texture (spritesheet)
      posCam(0, 0) {
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

  Texture spritesheet;
  if (!spritesheet.loadFromFile("../assets/img/spritesheet.png")) {
    cout << "Erreur de chargement de la spritesheet." << endl;
  }
  sprites.emplace(
      make_pair("grass", Sprite(spritesheet, IntRect(0, 0, 16, 16))));
  sprites.emplace(
      make_pair("dirt", Sprite(spritesheet, IntRect(16, 0, 16, 16))));
  sprites.emplace(
      make_pair("stone", Sprite(spritesheet, IntRect(32, 0, 16, 16))));

  for (int i = 0; i < carte.getSize(); i++) {
    int x, y;
    x = carte.getTile(i).getX();
    y = carte.getTile(i).getY();

    if (carte.getTile(i).estDansCam(posCam.getX(), posCam.getY(),
                                    TAILLE_FENETRE_X, TAILLE_FENETRE_Y)) {
      drawSprites(x, y, sprites[carte.getTile(i).getBlock().getName()],
                  &window);
    }
  }

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
