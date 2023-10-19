#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "point.hpp"
#include <string>

class Personnage{

    public:
        Personnage(int x, int y, int taille);

        Personnage();

        int getHauteur();

        int getLargeur();

        int getX();

        int getY();

        void setX(int x);

        void setY(int y);

        void deplacerX(int x);

        void deplacerY(int y);

        std::string toString();

        void clean();
        

    private:
        Point coord;
        int taille;

};

#endif