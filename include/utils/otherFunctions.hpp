#ifndef OTHERFUNCTIONS_HPP
#define OTHERFUNCTIONS_HPP

#include "../ui/soundSettings.hpp"
#include "const.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void Error(bool condition, const string &message);
void Error(const string &message);
void handleFileError(const string &filePath);
bool isInside(int mouseX, int mouseY, int x, int y, int width, int height);

#endif /*OTHERFUNCTIONS_HPP*/
