#ifndef JEU_HPP
#define JEU_HPP

#include "cartes.hpp"
#include "const.hpp"
#include "draw.hpp"
#include "personnage.hpp"
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

class Jeu {
private:
  Carte carte;
  Personnage perso;
  RenderWindow window;
  View miniWindow;
  bool collideDown;
  bool collideSide;
  Point posCam;
  unordered_map<string, Sprite> sprites;

public:
  Jeu();
  void run();
  void update();
  void updateCam();
  void updateCollide();
  void render();
  void clean();
  void event();
  bool collisionAvecCarte(int x, int y);
};

#endif