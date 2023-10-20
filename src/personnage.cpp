#include "../include/personnage.hpp"
#include <iostream>

using namespace std;

Personnage::Personnage(int x, int y, int taille):
    coord(x, y)
{
    this->taille = taille;

    this->isFalling = true;
    this->isJumping = false;
    this->isGoingUp = false;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->jumpHeight = 15;
    this->timeJump = 0;
}

Personnage::Personnage():
    coord(0, 0)
{
    this->taille = 0;
    this->isFalling = true;
    this->isJumping = false;
    this->isGoingUp = false;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->jumpHeight = 0;
}

void Personnage::update(bool collide){
    if (isJumping && collide && !isGoingUp){
        this->isGoingUp = true;
        this->timeJump = 0;
    }
    if (!isJumping){
        this->isGoingUp = false;
        this->isFalling = true;
    }
    if (isGoingUp){
        this->timeJump++;
        if (timeJump < jumpHeight){
            this->setY(this->getY() - 3);
        }else{
            this->isGoingUp = false;
            this->isFalling = true;
        }
        
    }
    if (isFalling && !collide && !isGoingUp){
        this->setY(this->getY() + 3);
    }
    if (isGoingRight){
        this->setX(this->getX() + 3);
    }
    if (isGoingLeft){
        this->setX(this->getX() - 3);
    }
    if (isGoingUp){
        this->setY(this->getY() - 3);
    }
}

void Personnage::jump(){
    if (timeJump >= jumpHeight){
        this->isGoingUp = false;
        this->isFalling = true;
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

// setters
void Personnage::setX(int x){
    coord.setX(x);
}

void Personnage::setY(int y){
    coord.setY(y);
}

void Personnage::setTimeJump(int time){
    this->timeJump = time;
}

void Personnage::setFalling(bool falling){
    this->isFalling = falling;
}
void Personnage::setJumping(bool jumping){
    this->isJumping = jumping;
}
void Personnage::setGoingUp(bool jumping ){
    this->isGoingUp = jumping;
}
void Personnage::setGoingRight(bool inRight ){
    this->isGoingRight = inRight;
}
void Personnage::setGoingLeft(bool inLeft ){
    this->isGoingLeft = inLeft;
}



// other methods
void Personnage::deplacerX(int x){
    cout << "deplacerX pas fait" << endl;
}

void Personnage::deplacerY(int y){
    cout << "deplacerY pas fait" << endl;
}

bool Personnage::isInFall(){
    return isFalling;
}
bool Personnage::isInJump(){
    return isGoingUp;
}

void Personnage::clean(){
    // pas de memoir aloué
}