#include "../include/personnage.hpp"
#include <iostream>

using namespace std;

Personnage::Personnage(int x, int y, int taille){
    this->x = x;
    this->y = y;
    this->taille = taille;
}

int Personnage::getTaille(){
    return taille;
}

int Personnage::getX(){
    return x;
}

int Personnage::getY(){
    return y;
}

void Personnage::setX(int x){
    this->x = x;
}

void Personnage::setY(int y){
    this->y = y;
}

void Personnage::deplacerX(int x){
    this->x += x;
}

void Personnage::deplacerY(int y){
    this->y += y;
}

void Personnage::printPersonnage(){
    cout << "x: " << x << " y: " << y << endl;
}