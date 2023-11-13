#include "../include/game.hpp"
#include "../include/menu.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  Game game(window);
  Menu menu(window);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
      game.handleEvent(event);
      menu.handleEvent(event);
    }
    // no window.clear() because it's done in game.clean() or menu.clean()
  
    if (menu.isActive()) {
      menu.run();
    } else if (menu.isNewGame()){
      game.reset();
      menu.setIsNewGame(false);
    }else {
      game.run();
    }
    // no window.display() because it's done in game.run() or menu.run()
  }
  return EXIT_SUCCESS;
}