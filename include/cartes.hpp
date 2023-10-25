#ifndef CARTE_HPP
#define CARTE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "block.hpp"
#include "personnage.hpp"

using namespace std;

class Carte
{

    public:
        Carte();

        void initCarte(const char* nomFichier);

        // getters
        vector<Block> getCarte();
        int getSize();
        Block getBlock(int i);
        void collide(Personnage * perso);
        Block chooseBlock(char c, int x, int y);

        void clean();

        string toString();
        

    private:

        vector<Block> carte;

};

#endif // CARTE_HPP