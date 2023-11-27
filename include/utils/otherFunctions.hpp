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
 * @brief Affiche un message d'erreur et termine le programme si une condition est vraie.
 *
 * @param condition Condition à évaluer.
 * @param message Message d'erreur à afficher si la condition est vraie.
 */
void Error(bool condition, const string &message);

/**
 * @brief Affiche un message d'erreur et termine le programme.
 *
 * @param message Message d'erreur à afficher.
 */
void Error(const string &message);

/**
 * @brief Affiche un message d'erreur lié à un fichier et termine le programme.
 *
 * @param filePath Chemin du fichier causant l'erreur.
 */
void handleFileError(const string &filePath);

/**
 * @brief Vérifie si les coordonnées (mouseX, mouseY) sont à l'intérieur d'une zone rectangulaire définie par (x, y, width, height).
 *
 * @param mouseX Position horizontale de la souris.
 * @param mouseY Position verticale de la souris.
 * @param x Position horizontale du coin supérieur gauche de la zone rectangulaire.
 * @param y Position verticale du coin supérieur gauche de la zone rectangulaire.
 * @param width Largeur de la zone rectangulaire.
 * @param height Hauteur de la zone rectangulaire.
 * @return true Si les coordonnées de la souris sont à l'intérieur de la zone rectangulaire, sinon false.
 */
bool isInside(int mouseX, int mouseY, int x, int y, int width, int height);

#endif /* OTHERFUNCTIONS_HPP */