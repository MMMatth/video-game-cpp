#include "../include/personnage.hpp"
#include <iostream>

using namespace std;

Personnage::Personnage(int x, int y, int taille):
    coord(x, y)
{
    this->taille = taille;
}

Personnage::Personnage():
    coord(0, 0)
{
    this->taille = 0;
}

int Personnage::getHauteur(){
    return taille;
}

int Personnage::getLargeur(){
    return taille / 2;
}

int Personnage::getX(){
    return coord.getX();
}

int Personnage::getY(){
    return coord.getY();
}

void Personnage::setX(int x){
    coord.setX(x);
}

void Personnage::setY(int y){
    coord.setY(y);
}

void Personnage::deplacerX(int x){
    cout << "deplacerX pas fait" << endl;
}

void Personnage::deplacerY(int y){
    cout << "deplacerY pas fait" << endl;
}

// std::string Personnage::toString(){
//     return "personnage(" + coord.toString() + ", " + to_string(taille) + ")";
// }




void Personnage::clean(){
    // pas de memoir aloué
}