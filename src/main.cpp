#include "../include/gameplay/game.hpp"
#include "../include/ui/menu.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
  /* init windows*/
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  /* init sprites and sounds */
  unordered_map<string, Sprite> sprites = initSprites();
  unordered_map<string, SoundBuffer> buffers = initBuffers();
  SoundSettings soundSettings(5);
  Sound sound;
  sound.setVolume(soundSettings.getVolume());
  /* init the game and the menu */
  Game game(window, sound, sprites, buffers, soundSettings);
  Menu menu(window);

  window.setFramerateLimit(FPS_MAX);
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
      if (menu.isActive()) {
        menu.handleEvent(event);
      } else {
        game.handleEvent(event);
      }
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

  return EXIT_SUCCESS;
}