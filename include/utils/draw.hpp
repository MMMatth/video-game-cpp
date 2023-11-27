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
 * @brief Initializes a set of sprites from image files.
 *
 * @return An associative array (unordered_map) of sprites.
 */
unordered_map<string, Sprite> initSprites();

/**
 * @brief Draws a sprite at a specified position on the window.
 *
 * @param x Horizontal position of the sprite.
 * @param y Vertical position of the sprite.
 * @param sprite Sprite to draw.
 * @param window SFML window on which to draw.
 * @param width Width of the sprite.
 * @param height Height of the sprite.
 */
void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

/**
 * @brief Draws text at a specified position on the window.
 *
 * @param x Horizontal position of the text.
 * @param y Vertical position of the text.
 * @param text Text string to draw.
 * @param window SFML window on which to draw.
 * @param size Size of the text.
 * @param color Color of the text.
 * @param fontPath Path to the font file.
 */
void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

/**
 * @brief Draws text with an outline at a specified position on the window.
 *
 * @param x Horizontal position of the text.
 * @param y Vertical position of the text.
 * @param text Text string to draw.
 * @param window SFML window on which to draw.
 * @param size Size of the text.
 * @param color Color of the text.
 * @param edgeColor Color of the text outline.
 * @param fontPath Path to the font file.
 */
void drawTextWithEdge(int x, int y, string text, RenderWindow *window, int size,
                      Color color, Color edgeColor, string fontPath);

/**
 * @brief Initializes a set of audio buffers from sound files.
 *
 * @return An associative array (unordered_map) of audio buffers.
 */
unordered_map<string, SoundBuffer> initBuffers();

/**
 * @brief Plays a sound from a given audio buffer.
 *
 * @param buffer Audio buffer of the sound to play.
 * @param sound SFML Sound object to play the sound.
 */
void play_sound(SoundBuffer *buffer, Sound *sound);

#endif /* DRAW_HPP */