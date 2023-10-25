#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "point.hpp"
#include <map>
#include <string>

using namespace std;

class Personnage{

    public:
        Personnage(int x, int y, int taille);

        Personnage();

        void update();

        void jump();

        // getter
        int getHauteur();
        int getLargeur();
        int getX();
        int getY();
        int getTimeJump();
        int getJumpHeight();
        int getVitesse();

        // setter
        void setX(int x);
        void setY(int y);
        void setFalling(bool falling);
        void setJumping(bool jumping);
        void setGoingUp(bool inUp);
        void setTimeJump(int time);
        void setGoingRight(bool inRight);
        void setGoingLeft(bool inLeft);
        void setCollision(string key, bool value);

        void deplacerX(int x);
        void deplacerY(int y);

        std::string toString();

        bool isInFall();
        bool isInJump();

        void clean();
        

    private:
        Point coord;
        bool isFalling;
        map<string, bool> direction;
        map<string , bool> collision;
        int timeJump;
        int jumpHeight;
        int taille;
        int tempSaut;
        int vitesse;

};

#endif