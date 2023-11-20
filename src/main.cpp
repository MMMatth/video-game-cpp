#include "../include/game.hpp"
#include "../include/menu.hpp"
#include "../include/monster.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  Game game(window);
  Menu menu(window);
  window.setFramerateLimit(144);

  const Time TimePerFrame =
      seconds(1.f / TICKS_PER_FRAME); // 60 updates per second
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  while (window.isOpen()) {
    Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      Event event;
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
          window.close();
        }
        game.handleEvent(event);
        menu.handleEvent(event);
      }

      if (menu.isActive()) {
        menu.run();
      } else if (menu.isNewGame()) {
        game.reset();
        menu.setIsNewGame(false);
      } else if (game.isPause()) {
        game.render();
      } else {
        if (menu.volumeOff()) {
          game.setGameVolume(0);
        }
        game.run();
      }
    }
  }
  return EXIT_SUCCESS;
}