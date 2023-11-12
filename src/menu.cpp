#include "../include/menu.hpp"

Menu::Menu() : m_menu(true) {
  if (!menuTexture.loadFromFile(IMG_MENU)) {
    std::cout << "Erreur de chargement de la texture du menu." << std::endl;
  }
  menuSprite.setTexture(menuTexture);
  menuSprite.setPosition(0, 0);
}

void Menu::handleEvent(sf::Event &event) {
  if (event.type == sf::Event::MouseButtonPressed && m_menu) {
    int mouseX = event.mouseButton.x;
    int mouseY = event.mouseButton.y;
    if (mouseX >= 630 && mouseX <= 787 && mouseY >= 216 && mouseY <= 295) {
      m_menu = false;
    }
    if (mouseX >= 32 && mouseX <= 230 && mouseY >= 214 && mouseY <= 297) {
      if (!buffer.loadFromFile(SOUND_PLAY)) {
        std::cerr << "Error loading sound" << std::endl;
      }
      sound.setBuffer(buffer);
      sound.play();
      m_menu = false;
    }
    if (mouseX >= 318 && mouseX <= 508 && mouseY >= 131 && mouseY <= 210) {
      std::cout << "Nothing at the moment " << std::endl;
    }
  }
}

void Menu::draw(sf::RenderWindow &window) {
  if (m_menu) {
    window.clear();
    window.draw(menuSprite);
    window.display();
  }
}

bool Menu::isActive() const { return m_menu; }

void Menu::setActive(bool active) { m_menu = active; }