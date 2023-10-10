#include "../include/jeu.hpp"

using namespace std;
using namespace sf;

Jeu::Jeu() : 
window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), "jeu"),
perso(0,0,TAILLE_PERSONNAGE)
{
    this->carte = Carte();
}

void Jeu::run(){
    while (window.isOpen())
    {
        event();
        update();
        render();
    }   
    clean();
}

void Jeu::update(){
    // pass
}

void Jeu::clean(){
    this->window.clear();
    this->perso.clean();
    this->carte.clean();
}

void Jeu::event(){
    Event event;
    while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Up:
                    perso.deplacerY(-5);
                    break;
                case Keyboard::Down:
                    perso.deplacerY(5);
                    break;
                case Keyboard::Left:
                    perso.deplacerX(-5);
                    break;
                case Keyboard::Right:
                    perso.deplacerX(5);
                    break;
                case Keyboard::Escape:
                    window.close(); 
                    break;
                default:
                    break;
                }
            }
        }

}

void Jeu::render(){
    window.clear(COULEUR_CIEL);

    drawRectangle(perso.getX(), perso.getY(), Color::Blue, &window, TAILLE_PERSONNAGE/2, TAILLE_PERSONNAGE);

    for (int x = 0; x < carte.getCarte().size() ; x++){
        for (int y = 0; y < carte.getCarte()[x].size(); y++){
            if (carte.getCarte()[x][y] == '1'){
                drawMap(y, x, Color::Green, &window, TAILLE_CASE, TAILLE_CASE);
            }
            if (carte.getCarte()[x][y] == '2'){
                drawMap(y, x, Color::Red, &window, TAILLE_CASE, TAILLE_CASE);
            }
        }
    }

    window.display();
}

int main(int arg, char ** argv)
{
    Jeu jeu;
    jeu.run();
    return 0;
}