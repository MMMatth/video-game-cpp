#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void drawSprite(int x, int y, RenderWindow *window, string path);

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window);

void drawMap(int x, int y, Color color, RenderWindow *window, int largeur,
             int hauteur);

void drawRectangle(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);

void drawMiniCarte(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);