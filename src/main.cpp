#include <SFML/Graphics.hpp>
#include "../include/cartes.hpp"
#include "../include/const.hpp"

using namespace std;
using namespace sf;

void drawRectangle(int x, int y, Color color, RenderWindow* window){
    RectangleShape rectangle(Vector2f(TAILLE_CASE, TAILLE_CASE));
    rectangle.setFillColor(color);
    rectangle.setPosition(x*TAILLE_CASE, y*TAILLE_CASE);
    window->draw(rectangle);
}

int main()
{
    Carte carte;

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
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }



        window.clear(COULEUR_CIEL);

        for (int x = 0; x < carte.getCarte().size() ; x++){
            for (int y = 0; y < carte.getCarte()[x].size(); y++){
                if (carte.getCarte()[x][y] == '1'){
                    drawRectangle(y, x, Color::Green, &window);
                }
                if (carte.getCarte()[x][y] == '2'){
                    drawRectangle(y, x, Color::Red, &window);
                }
            }
        }
        window.display();
    }

    return 0;
}