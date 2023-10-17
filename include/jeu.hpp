#ifndef JEU_HPP
#define JEU_HPP

#include <SFML/Graphics.hpp>
#include "cartes.hpp"
#include "const.hpp"
#include "personnage.hpp"
#include "draw.hpp"

using namespace std;
using namespace sf;



class Jeu{
    private:
        Carte carte;
        Personnage perso;
        RenderWindow window;
        View miniWindow;
        bool isCollision;
        point posCam;
        


    public:
        Jeu();
        void initJeu();
        void run();
        void update();
        void render();
        void clean();
        void event();
        void drawMiniMap();
        bool collisionAvecCarte (int x, int y);

};

#endif