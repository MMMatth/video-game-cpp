/*!
 * \file draw.hpp
 * \brief Fonctions de dessin.
 * \author  Mathieu Gaudel and Papa El Hadji G Cissé
 */
#ifndef DRAW_HPP
#define DRAW_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void drawSprite(int x, int y, RenderWindow *window, string path);

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

void drawMap(int x, int y, Color color, RenderWindow *window, int largeur,
             int hauteur);

void drawRectangle(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);

void drawMiniCarte(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);

void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

#endif /* DRAW_HPP*/