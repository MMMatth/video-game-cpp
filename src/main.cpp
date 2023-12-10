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
  SoundSettings soundSettings(VOLUME);
  Sound sound;
  sound.setVolume(soundSettings.getVolume());
  /* game phase */
  bool isMenu = true;
  bool isGame = false;
  cout << isGame << endl;
  /* init the menu */
  Menu menu = Menu(window, sound, sprites, buffers, soundSettings);
  menu.setIsNewGame(false);
  menu.setIsPlayInput(false);
  menu.setIsPlaySave(false);
  /* init the game */

  Game *game = nullptr;

  window.setFramerateLimit(FPS_MAX);
  while (window.isOpen()) {
    Event event;
    if (isMenu) {
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
          window.close();
        }
        menu.handleEvent(event);
      }
      menu.run();
      if (menu.isNewGame()) {
        isGame = true;
        isMenu = false;
        game = new Game(window, sound, sprites, buffers, soundSettings, true,
                        false);
        game->reset(true);
        menu.setIsNewGame(false);
      } else if (menu.isPlayInput()) {
        isGame = true;
        isMenu = false;
        game = new Game(window, sound, sprites, buffers, soundSettings, false,
                        true);
        menu.setIsPlayInput(false);
      } else if (menu.isPlaySave()) {
        isGame = true;
        isMenu = false;
        game = new Game(window, sound, sprites, buffers, soundSettings, true,
                        false);
        menu.setIsPlaySave(false);
      }
    } else if (isGame && game != nullptr) {
      while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
          window.close();
        }
        game->handleEvent(event);
      }
      game->run();
    }
  }
  delete game;
  return EXIT_SUCCESS;
}