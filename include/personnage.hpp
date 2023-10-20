#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "point.hpp"
#include <string>

class Personnage{

    public:
        Personnage(int x, int y, int taille);

        Personnage();

        void update(bool colide);

        void jump();

        // getter
        int getHauteur();
        int getLargeur();
        int getX();
        int getY();
        int getTimeJump();
        int getJumpHeight();

        // setter
        void setX(int x);
        void setY(int y);
        void setFalling(bool falling);
        void setJumping(bool jumping);
        void setGoingUp(bool inUp);
        void setTimeJump(int time);
        void setGoingRight(bool inRight);
        void setGoingLeft(bool inLeft);

        void deplacerX(int x);
        void deplacerY(int y);

        std::string toString();

        bool isInFall();
        bool isInJump();

        void clean();
        

    private:
        Point coord;
        bool isFalling;
        bool isJumping;
        bool isGoingUp;
        bool isGoingRight;
        bool isGoingLeft;
        int timeJump;
        int jumpHeight;
        int taille;
        int tempSaut;

};

#endif