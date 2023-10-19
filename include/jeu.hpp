#ifndef JEU_HPP
#define JEU_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "cartes.hpp"
#include "const.hpp"
#include "personnage.hpp"
#include "draw.hpp"
#include "point.hpp"

using namespace std;
using namespace sf;



class Jeu{
    private:
        Carte carte;
        Personnage perso;
        RenderWindow window;
        View miniWindow;
        bool isCollision;
        Point posCam;
        unordered_map<string, Sprite> sprites;
        
        


    public:
        Jeu();
        void run();
        void initSprites();
        void update();
        void render();
        void clean();
        void event();
        void drawMiniMap();
        bool collisionAvecCarte (int x, int y);

};

#endif