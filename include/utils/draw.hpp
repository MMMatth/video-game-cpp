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

unordered_map<string, Sprite> initSprites();

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

void initSprite(string path, string type);

Sprite createSprite(string type, string path);

/* text */
void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

void drawTextWithEdge(int x, int y, string text, RenderWindow *window, int size,
                      Color color, Color edgeColor, string fontPath);

int getTextWidth(string text, int size, string fontPath);

int getTextHeight(string text, int size, string fontPath);
/* rect */
void drawRectangle(int x, int y, int width, int height, RenderWindow *window,
                   Color color, int alpha);

void drawEdge(int x, int y, int width, int height, RenderWindow *window,
              Color color, int alpha);
/* sound */
unordered_map<string, SoundBuffer> initBuffers();

void play_sound(SoundBuffer *buffer, Sound *sound);

#endif /* DRAW_HPP */