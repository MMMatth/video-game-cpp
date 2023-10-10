#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

class Personnage{

    public:
        Personnage(int x, int y, int taille);

        Personnage();

        int getTaille();

        int getX();

        int getY();

        void setX(int x);

        void setY(int y);

        void deplacerX(int x);

        void deplacerY(int y);

        void printPersonnage();

        void clean();

    private:
        int x, y;
        int taille;

};

#endif