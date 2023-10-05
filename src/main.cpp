#include <SFML/Graphics.hpp>
#include "../include/cartes.hpp"
#include "../include/const.hpp"
#include "../include/personnage.hpp"

using namespace std;
using namespace sf;

void drawMap(int x, int y, Color color, RenderWindow* window, int largeur, int hauteur){
    RectangleShape rectangle(Vector2f(largeur, hauteur));
    rectangle.setFillColor(color);
    rectangle.setPosition(x*largeur, y*hauteur);
    window->draw(rectangle);
}

void drawRectangle(int x, int y, Color color, RenderWindow* window, int largeur, int hauteur){
    RectangleShape rectangle(Vector2f(largeur, hauteur));
    rectangle.setFillColor(color);
    rectangle.setPosition(x, y);
    window->draw(rectangle);
}

int main()
{
    Carte carte;
    Personnage perso(0, 0, TAILLE_PERSONNAGE);
    RenderWindow window(VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), "jeu");
    

    while (window.isOpen())
    {
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
                default:
                    break;
                }
            }
        }

        perso.printPersonnage();

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

    return 0;
}