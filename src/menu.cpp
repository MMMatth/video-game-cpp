#include "../include/menu.hpp"
#include "../include/otherFunctions.hpp"

bool isInside(int mouseX, int mouseY, int x, int y, int width, int height) {
  return mouseX >= x && mouseX <= width && mouseY >= y &&
         mouseY <= height;
}

Menu::Menu(RenderWindow &window) : m_menu(true), m_window(window) {
  Error(!menuTexture.loadFromFile(IMG_MENU), "Error loading menu texture");
  menuSprite.setTexture(menuTexture);
  menuSprite.setPosition(0, 0);
}

void Menu::handleEvent(sf::Event &event) {
  if (event.type == sf::Event::MouseButtonPressed && m_menu) {
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    /* quit button */
    if (isInside(mouseX, mouseY, 630, 216, 787, 295)) {
      m_menu = false;
      quit();
    }
    /* play button */
    if (isInside(mouseX, mouseY, 32, 214, 230, 297)) {
      Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound");
      sound.setBuffer(buffer);
      sound.play();
      m_menu = false;
    }
    /* help button */
    if (isInside(mouseX, mouseY, 318, 131, 508, 210)) {
      cout <<"Not implemented yet"<<endl;
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
