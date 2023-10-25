#include "../include/personnage.hpp"
#include <iostream>

using namespace std;

Personnage::Personnage(int x, int y, int taille):
    coord(x, y)
{
    this->taille = taille;

    this->direction  = {
        {"isJumping", false},
        {"isGoingUp", false},
        {"isFalling", true},
        {"isGoingRight", false},
        {"isGoingLeft", false}
    };

    this->collision = {
        {"up", false},
        {"down", false},
        {"left", false},
        {"right", false}
    };

    this->jumpHeight = 15;
    this->timeJump = 0;
    this->vitesse = 3;
}

Personnage::Personnage():
    coord(0, 0)
{
    this->taille = 0;
    this->direction["isFalling"] = true;
        this->direction  = {
        {"isJumping", false},
        {"isGoingUp", false},
        {"isFalling", false},
        {"isGoingRight", false},
        {"isGoingLeft", false}
    };

    this->collision = {
        {"up", false},
        {"down", false},
        {"left", false},
        {"right", false}
    };
    this->jumpHeight = 0;
}

void Personnage::update(){
    if (direction["isJumping"] && collision["down"] && !direction["isGoingUp"]){
        this->direction["isGoingUp"] = true;
        this->timeJump = 0;
        this->collision["down"] = false;
    }
    if (!direction["isJumping"]){
        this->direction["isGoingUp"] = false;
        this->direction["isFalling"] = true;
    }
    if (direction["isGoingUp"]){
        this->timeJump++;
        if (timeJump < jumpHeight){
            this->setY(this->getY() - vitesse);
        }else{
            this->direction["isGoingUp"] = false;
            this->direction["isFalling"] = true;
        }
        
    }
    printf("collisiondown : %d\n", collision["down"]);
    if (direction["isFalling"] && !collision["down"] && !direction["isGoingUp"]){
        this->setY(this->getY() + vitesse);
    }
    if (direction["isGoingRight"] && !collision["right"]){
        this->setX(this->getX() + vitesse);
    }
    if (direction["isGoingLeft"] && !collision["left"]){
        this->setX(this->getX() - vitesse);
    }
    if (direction["isGoingUp"]){
        this->setY(this->getY() - vitesse);
    }
}


// getters
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
int Personnage::getTimeJump(){
    return timeJump;
}

int Personnage::getJumpHeight(){
    return jumpHeight;
}

int Personnage::getVitesse(){
    return vitesse;
}

// setters
void Personnage::setX(int x){
    coord.setX(x);
}

void Personnage::setY(int y){
    coord.setY(y);
}

void Personnage::setCollision(string key, bool value){
    this->collision[key] = true;
}

void Personnage::setTimeJump(int time){
    this->timeJump = time;
}

void Personnage::setFalling(bool falling){
    this->direction["isFalling"] = falling;
}
void Personnage::setJumping(bool jumping){
    this->direction["isJumping"] = jumping;
}
void Personnage::setGoingUp(bool jumping ){
    this->direction["isGoingUp"] = jumping;
}
void Personnage::setGoingRight(bool inRight ){
    this->direction["isGoingRight"] = inRight;
}
void Personnage::setGoingLeft(bool inLeft ){
    this->direction["isGoingLeft"] = inLeft;
}



// other methods
void Personnage::deplacerX(int x){
    cout << "deplacerX pas fait" << endl;
}

void Personnage::deplacerY(int y){
    cout << "deplacerY pas fait" << endl;
}

bool Personnage::isInFall(){
    return direction["isFalling"];
}
bool Personnage::isInJump(){
    return direction["isGoingUp"];
}

void Personnage::clean(){
    // pas de memoir aloué
}