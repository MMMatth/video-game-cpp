#include "../include/draw.hpp"
#include "../include/const.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void drawSprite(int x, int y, RenderWindow *window, string path) {
  Sprite sprite;
  Texture texture;
  texture.loadFromFile(path);
  sprite.setTexture(texture);
  sprite.setPosition(x, y);
  sprite.setScale(TAILLE_CASE / sprite.getLocalBounds().width,
                  TAILLE_CASE / sprite.getLocalBounds().height);
  window->draw(sprite);
}

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height) {
  sprite.setPosition(x, y);
  sprite.setScale(width / sprite.getLocalBounds().width,
                  height / sprite.getLocalBounds().height);
  window->draw(sprite);
}

void drawMap(int x, int y, Color color, RenderWindow *window, int largeur,
             int hauteur) {
  RectangleShape rectangle(Vector2f(largeur, hauteur));
  rectangle.setFillColor(color);
  rectangle.setPosition(x * largeur, y * hauteur);
  window->draw(rectangle);
}

void drawRectangle(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur) {
  RectangleShape rectangle(Vector2f(largeur, hauteur));
  rectangle.setFillColor(color);
  rectangle.setPosition(x, y);
  window->draw(rectangle);
}

void drawMiniCarte(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur) {
  RectangleShape miniCarteRect;
  miniCarteRect.setSize(sf::Vector2f(largeur, hauteur));
  miniCarteRect.setFillColor(color);
  miniCarteRect.setPosition(x, y);
  window->draw(miniCarteRect);
}

void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath) {
  Font font;
  if (!font.loadFromFile("../" + fontPath)) {
    cout << "Erreur lors du chargement de la police" << endl;
  }
  Text textObj;
  textObj.setFont(font);
  textObj.setString(text);
  textObj.setCharacterSize(size);
  textObj.setFillColor(color);
  textObj.setPosition(x, y);
  window->draw(textObj);
  cout << "texte dessine" << endl;
}