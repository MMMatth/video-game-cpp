#include "../include/jeu.hpp"

using namespace std;
using namespace sf;


Jeu::Jeu() : 
window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
perso(0,0,TAILLE_PERSONNAGE),
posCam{0, 0}
{
    this->carte = Carte();
}

void Jeu::run(){
    miniWindow.setViewport(sf::FloatRect(0.9f, 0.1f, 0.2f, 0.25f)); // position du mini carte
    while (window.isOpen())
    {
        event();
        update();
        render();
      
    }   
    clean();
}

void Jeu::update(){
    posCam[0] += (perso.getX() + perso.getTaille() / 4 - posCam[0]) / 20;
    posCam[1] += (perso.getY() + perso.getTaille() / 2 - posCam[1]) / 20;
    window.setView(View(Vector2f(posCam[0], posCam[1]), Vector2f(TAILLE_FENETRE_X, TAILLE_FENETRE_Y)));
    
    
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
                drawMap(y, x, Color::Red, &window,TAILLE_CASE, TAILLE_CASE);
            }
        }
    }

    drawMiniMap();
    
    window.display();
}

void Jeu::drawMiniMap() {

    window.setView(miniWindow);
    drawMiniCarte(perso.getX(), perso.getY(), Color::Blue, &window, TAILLE_PERSONNAGE_MINI_CARTE/2, TAILLE_PERSONNAGE_MINI_CARTE);
    for (int x = 0; x < carte.getCarte().size() ; x++){
        for (int y = 0; y < carte.getCarte()[x].size(); y++){
            if (carte.getCarte()[x][y] == '1'){
                drawMap(y, x, Color::Green, &window, TAILLE_CASE_MINI_CARTE, TAILLE_CASE_MINI_CARTE);
            }
            if (carte.getCarte()[x][y] == '2'){
                drawMap(y, x, Color::Red, &window,TAILLE_CASE_MINI_CARTE, TAILLE_CASE_MINI_CARTE);
            }
        }
    }
}


int main(int arg, char ** argv)
{
    Jeu jeu;
    jeu.run();
    return 0;
}
