#ifndef CARTE_HPP
#define CARTE_HPP

#include <iostream>
#include <vector>

using namespace std;

class Carte
{

    public:
        Carte();

        void initCarte(const char* nomFichier);

        vector<vector<char>> getCarte();

        void libererCarte();

        void printCarte();

        void clean();
        // void sauvegarderCarte(const char* nomFichier);

        

    private:

        vector<vector<char>> carte;

};

#endif // CARTE_HPP