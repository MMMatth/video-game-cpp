#include "../include/jeu.hpp"


using namespace std;
using namespace sf;


Jeu::Jeu() : 
window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
perso(TAILLE_FENETRE_X/2, TAILLE_FENETRE_Y/2, TAILLE_PERSONNAGE),
posCam{0, 0}
{
    this->carte = Carte();
    this->isCollision = false;
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
    window.setView(View(Vector2f(posCam[0], posCam[1]), Vector2f(TAILLE_FENETRE_X / 1.5, TAILLE_FENETRE_Y  / 1.5)));
    
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
                int newX = perso.getX();
                int newY = perso.getY();
                
                switch (event.key.code)
                {
                case Keyboard::Up:
                    newY -= DEPLACEMENT;
                    break;
                case Keyboard::Down:
                    newY += DEPLACEMENT;
                    break;
                case Keyboard::Left:
                    newX -= DEPLACEMENT;
                    break;
                case Keyboard::Right:
                    newX += DEPLACEMENT;
                    break;
                case Keyboard::Escape:
                    window.close(); 
                    break;
                default:
                    break;
                }
                if (!this->isCollision){
                    perso.setX(newX);
                    perso.setY(newY);
                }

                
            }
        }

}

void Jeu::render(){
    window.clear(COULEUR_CIEL);

    drawRectangle(perso.getX(), perso.getY(), Color::Blue, &window, TAILLE_PERSONNAGE/2, TAILLE_PERSONNAGE);

    for (int y = 0; y < carte.getCarte().size() ; y++){
        for (int x = 0; x < carte.getCarte()[y].size(); x++){
            if ( y * TAILLE_CASE < posCam[1] + TAILLE_FENETRE_Y/ 3 &&
                x * TAILLE_CASE < posCam[0] + TAILLE_FENETRE_X / 3 &&
                y * TAILLE_CASE > posCam[1] - TAILLE_FENETRE_Y / 3 &&
                x * TAILLE_CASE > posCam[0] - TAILLE_FENETRE_X / 3){

                    if (carte.getCarte()[y][x] == '1' || carte.getCarte()[y][x] == '2' || carte.getCarte()[y][x] == '3'){
                        if ( y * TAILLE_CASE < perso.getY() + perso.getTaille() &&
                            y * TAILLE_CASE + TAILLE_CASE > perso.getY() &&
                            x * TAILLE_CASE < perso.getX() + perso.getLargeur() &&
                            x * TAILLE_CASE + TAILLE_CASE > perso.getX())
                        {
                            cout << "collision" << endl;
                        }
                    }
                    switch (carte.getCarte()[y][x])
                    {
                    case '1':
                        drawSprite(x * TAILLE_CASE, y * TAILLE_CASE, &window, "../assets/img/grass.png");
                        break;
                    case '2':
                        drawSprite(x * TAILLE_CASE, y * TAILLE_CASE, &window, "../assets/img/dirt.png");
                        break;
                    case '3':
                        drawSprite(x * TAILLE_CASE, y * TAILLE_CASE, &window, "../assets/img/stone.png");
                        break;
                    
                    default:
                        break;
                    }
                }
        }
    }

    drawMiniMap();
    
    window.display();
}

void Jeu::drawMiniMap() {
    window.setView(miniWindow);
    drawMiniCarte(perso.getX(), perso.getY(), Color::Blue, &window, TAILLE_PERSONNAGE_MINI_CARTE/2, TAILLE_PERSONNAGE_MINI_CARTE);
    for (int y = 0; y < carte.getCarte().size() ; y++){
        for (int x = 0; x < carte.getCarte()[y].size(); x++){
            switch (carte.getCarte()[y][x])
            {
            case '1':
                drawMap(x, y, Color(0,100,0), &window, TAILLE_CASE_MINI_CARTE, TAILLE_CASE_MINI_CARTE);
                break;
            case '2':
                drawMap(x, y, Color(91,60,17), &window,TAILLE_CASE_MINI_CARTE, TAILLE_CASE_MINI_CARTE);
                break;
            case '3':
                drawMap(x, y, Color(128,128,128), &window, TAILLE_CASE_MINI_CARTE, TAILLE_CASE_MINI_CARTE);
                break;
            default:
                break;
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
