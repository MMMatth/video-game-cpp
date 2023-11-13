#include "../include/menu.hpp"

bool isInside(int mouseX, int mouseY, int x, int y, int width, int height) {
  return mouseX >= x && mouseX <= width && mouseY >= y && mouseY <= height;
}

Menu::Menu(RenderWindow &window)
    : m_menu(true), m_window(window), m_sound(), m_newGame(false) {
  Error(!menuTexture.loadFromFile(IMG_MENU), "Error loading menu texture");
  menuSprite.setTexture(menuTexture);
  menuSprite.setPosition(0, 0);
  Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound");
  m_sound.setVolume(VOLUME);
}
void Menu::handleEvent(sf::Event &event) {
  if (event.type == sf::Event::MouseButtonPressed && m_menu) {
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    /* quit button */
    if (isInside(mouseX, mouseY, 629, 256, 737, 303)) {
      m_menu = false;
      quit();
    }
    /* play button */
    if (isInside(mouseX, mouseY, 75, 166, 324, 219)) {
      play_sound(&buffer, &m_sound);
      m_menu = false;
    }
    /* new game button */
    if (isInside(mouseX, mouseY, 73, 255, 354, 307)) {
      play_sound(&buffer, &m_sound);
      m_menu = false;
      m_newGame = true;
    }
    /* help button */
    if (mouseX, mouseY, 624, 166, 752, 218) {
      cout << "Not implemented yet" << endl;
    }
  }
}

void Menu::quit() { m_window.close(); }

void Menu::run() { render(); }

void Menu::render() {
  m_window.clear();
  m_window.draw(menuSprite);
  m_window.display();
}

bool Menu::isActive() const { return m_menu; }

bool Menu::isNewGame() const { return m_newGame; }

void Menu::setIsNewGame(bool newGame) { m_newGame = newGame; }
