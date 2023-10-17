#include "../include/jeu.hpp"


using namespace std;
using namespace sf;


Jeu::Jeu() : 
window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
perso(TAILLE_FENETRE_X/2, TAILLE_FENETRE_Y/2, TAILLE_PERSONNAGE),
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

bool Jeu::collisionAvecCarte(int x, int y) {
    if (x < 0 || x  >= TAILLE_FENETRE_X || y < 0 || y  >= TAILLE_FENETRE_Y) {
        return true; 
    }

    return false;
}


void Jeu::update(){
    posCam[0] += (perso.getX() + perso.getTaille() / 4 - posCam[0]) / 20;
    posCam[1] += (perso.getY() + perso.getTaille() / 2 - posCam[1]) / 20;
    window.setView(View(Vector2f(posCam[0], posCam[1]), Vector2f(TAILLE_FENETRE_X, TAILLE_FENETRE_Y)));
    
    perso.printPersonnage();
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
                int nouvelleX = perso.getX();
                int nouvelleY = perso.getY();
                
                switch (event.key.code)
                {
                case Keyboard::Up:
                    nouvelleY -= DEPLACEMENT;
                    break;
                case Keyboard::Down:
                    nouvelleY += DEPLACEMENT;
                    break;
                case Keyboard::Left:
                    nouvelleX -= DEPLACEMENT;
                    break;
                case Keyboard::Right:
                    nouvelleX += DEPLACEMENT;
                    break;
                case Keyboard::Escape:
                    window.close(); 
                    break;
                default:
                    break;
                }
                
                if (!collisionAvecCarte(nouvelleX, nouvelleY)) {
                    perso.setX(nouvelleX);
                    perso.setY(nouvelleY);
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
