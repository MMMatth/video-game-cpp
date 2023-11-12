#include "../include/menu.hpp"

void Error(bool condition, const std::string &message) {
  if (condition) {
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
  }
}
void Error(const std::string &message) {
  std::cerr << message << std::endl;
  exit(EXIT_FAILURE);
}

bool isInside(int mouseX, int mouseY, int x, int y, int width, int height) {
  return mouseX >= x && mouseX <= x + width && mouseY >= y &&
         mouseY <= y + height;
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
    if (isInside(mouseX, mouseY, 32, 131, 230, 83)) {
      m_menu = false;
      quit();
    }
    /* play button */
    if (isInside(mouseX, mouseY, 32, 131, 230, 83)) {
      Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound");
      sound.setBuffer(buffer);
      sound.play();
      m_menu = false;
    }
    /* help button */
    if (isInside(mouseX, mouseY, 32, 131, 230, 83)) {
      Error("Not implemented yet");
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
