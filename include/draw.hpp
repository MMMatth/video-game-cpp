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

/*!
 * \brief Dessine un sprite à une position donnée.
 *
 * Cette fonction dessine un sprite à une position spécifiée dans une fenêtre.
 *
 * \param x La position horizontale du sprite.
 * \param y La position verticale du sprite.
 * \param window Un pointeur vers la fenêtre de rendu.
 * \param path Le chemin du fichier image du sprite.
 */
void drawSprite(int x, int y, RenderWindow *window, string path);

/*!
 * \brief Dessine un sprite à une position donnée.
 *
 * Cette fonction dessine un sprite à une position spécifiée dans une fenêtre.
 *
 * \param x La position horizontale du sprite.
 * \param y La position verticale du sprite.
 * \param sprite Le sprite à dessiner.
 * \param window Un pointeur vers la fenêtre de rendu.
 * \param width La largeur du sprite.
 * \param height La hauteur du sprite.
 */
void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

/*!
 * \brief Dessine une carte de couleur unie.
 *
 * Cette fonction dessine une carte de couleur unie à une position donnée dans
 * une fenêtre.
 *
 * \param x La position horizontale de la carte.
 * \param y La position verticale de la carte.
 * \param color La couleur de la carte.
 * \param window Un pointeur vers la fenêtre de rendu.
 * \param largeur La largeur de la carte.
 * \param hauteur La hauteur de la carte.
 */
void drawMap(int x, int y, Color color, RenderWindow *window, int largeur,
             int hauteur);

/*!
 * \brief Dessine un rectangle de couleur unie.
 *
 * Cette fonction dessine un rectangle de couleur unie à une position donnée
 * dans une fenêtre.
 *
 * \param x La position horizontale du rectangle.
 * \param y La position verticale du rectangle.
 * \param color La couleur du rectangle.
 * \param window Un pointeur vers la fenêtre de rendu.
 * \param largeur La largeur du rectangle.
 * \param hauteur La hauteur du rectangle.
 */
void drawRectangle(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);

/*!
 * \brief Dessine une mini-carte de couleur unie.
 *
 * Cette fonction dessine une mini-carte de couleur unie à une position donnée
 * dans une fenêtre.
 *
 * \param x La position horizontale de la mini-carte.
 * \param y La position verticale de la mini-carte.
 * \param color La couleur de la mini-carte.
 * \param window Un pointeur vers la fenêtre de rendu.
 * \param largeur La largeur de la mini-carte.
 * \param hauteur La hauteur de la mini-carte.
 */
void drawMiniCarte(int x, int y, Color color, RenderWindow *window, int largeur,
                   int hauteur);

void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

#endif /* DRAW_HPP*/