#include "../include/cartes.hpp"

using namespace std;

Carte::Carte() { initCarte("../assets/carte.txt"); }

Tile Carte::chooseTile(char c, int x, int y) {
  Block block;
  switch (c) {
  case '1':
    block = blockMap["GRASS"];
    break;
  case '2':
    block = blockMap["DIRT"];
    break;
  case '3':
    block = blockMap["STONE"];
    break;
  default:
    block = blockMap["AIR"];
    break;
  }
  return Tile(block, x, y);
}

void Carte::collide(Personnage *perso) {
  for (int i = 0; i < carte.size(); i++) {
    carte[i].collide(perso);
  }
}

void Carte::initCarte(const char *nomFichier) {
  ifstream fichier(nomFichier);
  if (fichier) {
    string ligne;
    int y = 0;
    while (getline(fichier, ligne)) {
      for (int x = 0; x < ligne.size(); x++) {
        carte.push_back(chooseTile(ligne[x], x, y));
      }
      y++;
    }
  } else {
    cout << "Erreur lors de l'ouverture du fichier" << endl;
  }
}

vector<Tile> Carte::getCarte() { return carte; }

int Carte::getSize() { return carte.size(); }

Tile Carte::getTile(int i) { return carte[i]; }

void Carte::clean() { carte.clear(); }

string Carte::toString() {
  string res;
  for (int i = 0; i < carte.size(); i++) {
    res += carte[i].toString();
  }
  return res;
}