#include "../include/personnage.hpp"
#include <iostream>

using namespace std;

Personnage::Personnage(int x, int y, int taille){
    this->coord.x = x;
    this->coord.y = y;
    this->taille = taille;
}

Personnage::Personnage(){
    this->coord.x = 0;
    this->coord.y = 0;
    this->taille = 0;
}

int Personnage::getTaille(){
    return taille;
}

int Personnage::getX(){
    return coord.x;
}

int Personnage::getY(){
    return coord.y;
}

void Personnage::setX(int x){
    this->coord.x = x;
}

void Personnage::setY(int y){
    this->coord.y = y;
}

void Personnage::deplacerX(int x){
    this->coord.x += x;
}

void Personnage::deplacerY(int y){
    this->coord.y += y;
}

void Personnage::printPersonnage(){
    cout << "x: " << coord.x << " y: " << coord.y << endl;
}

void Personnage::clean(){
    // pas de memoir aloué
}