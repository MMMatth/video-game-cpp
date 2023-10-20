#include "../include/jeu.hpp"


using namespace std;
using namespace sf;


Jeu::Jeu() : 
window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), TITRE_FENETRE),
perso(TAILLE_FENETRE_X/2, TAILLE_FENETRE_Y/2, TAILLE_PERSONNAGE),
posCam(0,0)
{
    this->carte = Carte();
    this->collide = false;

}

void Jeu::run(){
    miniWindow.setViewport(sf::FloatRect(0.9f, 0.1f, 0.2f, 0.25f)); // position du mini carte
    Clock clock;
    Time timePerFrame = seconds(1.f / 60.f);
    Time timeSinceLastUpdate = Time::Zero;
    while (window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate -= timePerFrame;
            event();
            update();
        }
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

void Jeu::updateCam(){
    posCam.setX(posCam.getX() + (perso.getX() + perso.getHauteur() / 4 - posCam.getX()) / 20);
    posCam.setY(posCam.getY() + (perso.getY() + perso.getHauteur() / 2 - posCam.getY()) / 20);
    window.setView(View(Vector2f(posCam.getX(), posCam.getY()), Vector2f(TAILLE_FENETRE_X / 1.5, TAILLE_FENETRE_Y  / 1.5)));
}

void Jeu::updateCollide(){
    collide = carte.collide(perso.getX(), perso.getY(), perso.getLargeur(), perso.getHauteur());
}

void Jeu::update(){
    updateCam();
    updateCollide();
    perso.update(collide);
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
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Up:
                    perso.setJumping(true);
                    break;
                case Keyboard::Left:
                    perso.setGoingLeft(true);
                    break;
                case Keyboard::Right:
                    perso.setGoingRight(true);
                    break;
                case Keyboard::Escape:
                    window.close(); 
                    break;
                default:
                    break;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case Keyboard::Up:
                    perso.setJumping(false); 
                    break;
                case Keyboard::Left:
                    perso.setGoingLeft(false);
                    break;
                case Keyboard::Right:
                    perso.setGoingRight(false);
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

    Texture spritesheet;
    spritesheet.loadFromFile("../assets/img/spritesheet.png");
    sprites.emplace(make_pair("grass", Sprite(spritesheet, IntRect(0, 0, 16, 16))));
    sprites.emplace(make_pair("dirt", Sprite(spritesheet, IntRect(16, 0, 16, 16))));
    sprites.emplace(make_pair("stone", Sprite(spritesheet, IntRect(32, 0, 16, 16))));

    for (int i = 0; i < carte.getSize(); i++)
    {
        int x,y;
        x = carte.getBlock(i).getX();
        y = carte.getBlock(i).getY();

        if ( carte.getBlock(i).estDansCam(posCam.getX(), posCam.getY() , TAILLE_FENETRE_X, TAILLE_FENETRE_Y))
        {
            drawSprites(x, y, sprites[carte.getBlock(i).getName()], &window);
        }
    }

    // drawMiniMap();
    
    window.display();
}




int main(int arg, char ** argv)
{
    Jeu jeu;
    jeu.run();
    return 0;
}
