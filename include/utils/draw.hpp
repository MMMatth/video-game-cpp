#ifndef DRAW_HPP
#define DRAW_HPP

#include "const.hpp"
#include "otherFunctions.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;
using namespace sf;

/**
 * @brief Initialise un ensemble de sprites à partir des fichiers d'images.
 *
 * @return Un tableau associatif (unordered_map) de sprites.
 */
unordered_map<string, Sprite> initSprites();

/**
 * @brief Dessine un sprite à une position spécifiée sur la fenêtre.
 *
 * @param x Position horizontale du sprite.
 * @param y Position verticale du sprite.
 * @param sprite Sprite à dessiner.
 * @param window Fenêtre SFML sur laquelle dessiner.
 * @param width Largeur du sprite.
 * @param height Hauteur du sprite.
 */
void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

/**
 * @brief Dessine un texte à une position spécifiée sur la fenêtre.
 *
 * @param x Position horizontale du texte.
 * @param y Position verticale du texte.
 * @param text Chaîne de texte à dessiner.
 * @param window Fenêtre SFML sur laquelle dessiner.
 * @param size Taille du texte.
 * @param color Couleur du texte.
 * @param fontPath Chemin vers le fichier de police (font).
 */
void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

/**
 * @brief Dessine un texte avec une bordure à une position spécifiée sur la fenêtre.
 *
 * @param x Position horizontale du texte.
 * @param y Position verticale du texte.
 * @param text Chaîne de texte à dessiner.
 * @param window Fenêtre SFML sur laquelle dessiner.
 * @param size Taille du texte.
 * @param color Couleur du texte.
 * @param edgeColor Couleur de la bordure du texte.
 * @param fontPath Chemin vers le fichier de police (font).
 */
void drawTextWithEdge(int x, int y, string text, RenderWindow *window, int size,
                      Color color, Color edgeColor, string fontPath);

/**
 * @brief Initialise un ensemble de buffers audio à partir de fichiers sonores.
 *
 * @return Un tableau associatif (unordered_map) de buffers audio.
 */
unordered_map<string, SoundBuffer> initBuffers();

/**
 * @brief Joue un son à partir d'un buffer audio donné.
 *
 * @param buffer Buffer audio du son à jouer.
 * @param sound Objet SFML Sound pour jouer le son.
 */
void play_sound(SoundBuffer *buffer, Sound *sound);

#endif /* DRAW_HPP */