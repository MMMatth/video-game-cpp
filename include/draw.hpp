#ifndef DRAW_HPP
#define DRAW_HPP

#include "../include/const.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;
using namespace sf;

unordered_map<string, Sprite> getSpriteMap();

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height);

void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath);

#endif /* DRAW_HPP*/