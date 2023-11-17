#include "../include/menu.hpp"



Menu::Menu(RenderWindow &window)
    : m_menu(true), m_window(window), m_sound(), m_newGame(false), m_soundSettings(5), m_clickOnOff(2) {
  Error(!menuTexture.loadFromFile(IMG_MENU_ON), "Error loading menu texture");
  menuSprite.setTexture(menuTexture);
  menuSprite.setPosition(0, 0);
  Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound");
  m_sound.setVolume(m_soundSettings.getVolume());
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
    if (isInside(mouseX, mouseY, 624, 166, 752, 218)) {
      cout << "Not implemented yet" << endl;
    }
    /*change sound volume*/
    if(isInside(mouseX, mouseY, 37, 35, 65, 63)){
     if(m_clickOnOff == 2){
      Error(!menuTexture.loadFromFile(IMG_MENU_OFF), "Error loading menuOff texture");
      m_soundSettings.setVolume(0);
      m_sound.setVolume(m_soundSettings.getVolume());
      m_clickOnOff--;
     }else{
      Error(!menuTexture.loadFromFile(IMG_MENU_ON), "Error loading menuOn texture");
      m_soundSettings.setVolume(5);
      m_sound.setVolume(m_soundSettings.getVolume());
      m_clickOnOff++;
     }
      
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

bool Menu::volumeOff() const{ return m_sound.getVolume() == 0; } 

void Menu::resetClickOnOff(){ m_clickOnOff = 2; }





