#include "../include/draw.hpp"

using namespace std;
using namespace sf;

void drawMap(int x, int y, Color color, RenderWindow* window, int largeur, int hauteur){
    RectangleShape rectangle(Vector2f(largeur, hauteur));
    rectangle.setFillColor(color);
    rectangle.setPosition(x*largeur, y*hauteur);
    window->draw(rectangle);
}

void drawRectangle(int x, int y, Color color, RenderWindow* window, int largeur, int hauteur){
    RectangleShape rectangle(Vector2f(largeur, hauteur));
    rectangle.setFillColor(color);
    rectangle.setPosition(x, y);
    window->draw(rectangle);
}