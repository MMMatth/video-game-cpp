#ifndef OTHERFUNCTIONS_HPP
#define OTHERFUNCTIONS_HPP

#include "const.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../include/soundSettings.hpp"
#include <iostream>

using namespace std;
using namespace sf;

void Error(bool condition, const string &message);
void Error(const string &message);
void handleFileError(const string &filePath);

#endif /*OTHERFUNCTIONS_HPP*/
