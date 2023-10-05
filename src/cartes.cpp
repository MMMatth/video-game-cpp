#include "../include/cartes.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

Carte::Carte()
{
    initCarte("../assets/carte.txt");
}

void Carte::initCarte(const char* nomFichier){
    ifstream fichier(nomFichier);
    if (fichier){
        string ligne;
        int i = 0;
        while (getline(fichier, ligne)){
            carte.push_back(vector<char>());
            for (int j = 0; j < ligne.size(); j++){
                carte[i].push_back(ligne[j]);
            }
            i++;
        }
    }else{
        cout << "Erreur lors de l'ouverture du fichier" << endl;
    }
}

vector<vector<char>> Carte::getCarte(){
    return carte;
}

void Carte::libererCarte(){
    for (int i = 0; i < carte.size(); i++){
        carte[i].clear();
    }
    carte.clear();
}

void Carte::printCarte(){
    for (int i = 0; i < carte.size(); i++){
        for (int j = 0; j < carte[i].size(); j++){
            cout << carte[i][j];
        }
        cout << endl;
    }
}