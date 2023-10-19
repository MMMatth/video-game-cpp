#include "../include/cartes.hpp"

using namespace std;

Carte::Carte()
{
    initCarte("../assets/carte.txt");
}

Block Carte::chooseBlock(char c, int x, int y){
    switch (c)
    {
    case '1':
        return Block(0,0, 1, "grass", x * TAILLE_CASE, y * TAILLE_CASE, true);
        break;
    case '2':
        return Block(16,0, 2, "dirt", x * TAILLE_CASE, y * TAILLE_CASE, true);
        break;
    case '3':
        return Block(32,0, 3, "stone", x * TAILLE_CASE, y * TAILLE_CASE, true);
        break;
    default:
        return Block(0,0, 0, "air", x * TAILLE_CASE, y * TAILLE_CASE, false);
        break;
    }
}

bool Carte::collide(int persoX, int persoY, int persoLargeur, int persoHauteur){
    for (int i = 0; i < carte.size(); i++){
        if (carte[i].collide(persoX, persoY, persoLargeur, persoHauteur)){
            return true;
        }
    }
    return false;
}

void Carte::initCarte(const char* nomFichier){
    ifstream fichier(nomFichier);
    if (fichier){
        string ligne;
        int y = 0;
        while (getline(fichier, ligne)){
            for (int x = 0; x < ligne.size(); x++){
                carte.push_back(Block(chooseBlock(ligne[x], x, y)));
            }
            y++;
        }
    }else{
        cout << "Erreur lors de l'ouverture du fichier" << endl;
    }
}


vector<Block> Carte::getCarte(){
    return carte;
}

int Carte::getSize(){
    return carte.size();
}

Block Carte::getBlock(int i){
    return carte[i];
}

void Carte::clean(){
    carte.clear();
}


string Carte::toString(){
    string res;
    for (int i = 0; i < carte.size(); i++){
        res += carte[i].toString();
    }
    return res;
}