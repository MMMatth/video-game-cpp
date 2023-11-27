#ifndef OTHERFUNCTIONS_HPP
#define OTHERFUNCTIONS_HPP

#include "../ui/soundSettings.hpp"
#include "const.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/**
 * @brief Displays an error message and terminates the program if a condition is true.
 *
 * @param condition Condition to evaluate.
 * @param message Error message to display if the condition is true.
 */
void Error(bool condition, const string &message);

/**
 * @brief Displays an error message and terminates the program.
 *
 * @param message Error message to display.
 */
void Error(const string &message);

/**
 * @brief Displays a file-related error message and terminates the program.
 *
 * @param filePath Path of the file causing the error.
 */
void handleFileError(const string &filePath);

/**
 * @brief Checks if the coordinates (mouseX, mouseY) are inside a rectangular area defined by (x, y, width, height).
 *
 * @param mouseX Horizontal position of the mouse.
 * @param mouseY Vertical position of the mouse.
 * @param x Horizontal position of the top-left corner of the rectangular area.
 * @param y Vertical position of the top-left corner of the rectangular area.
 * @param width Width of the rectangular area.
 * @param height Height of the rectangular area.
 * @return true if the mouse coordinates are inside the rectangular area, otherwise false.
 */
bool isInside(int mouseX, int mouseY, int x, int y, int width, int height);

#endif /* OTHERFUNCTIONS_HPP */