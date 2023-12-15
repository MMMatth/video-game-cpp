#include "../../include/ui/menuEnd.hpp"

MenuEnd::MenuEnd(RenderWindow &window, SoundSettings &sound, bool isEnd,
                 function<void()> quit, function<void()> restart, Monsters &monsters)
    : m_isEnd(isEnd), m_soundSettings(&sound), m_quit(quit), m_restart(restart),
      Ui(window), m_monsters(monsters) {
  initButtons();
}

void MenuEnd::initButtons() {
  m_textBouttons["restart"] = TextButton(
      230, 130,
      [&]() {
        m_soundSettings->playSound("PLAY");
        m_restart();
      },
      Color::White, Color::Yellow, Color::Black, "Restart", true, 60);
  m_textBouttons["quit"] = TextButton(
      230, 230,
      [&]() {
        m_soundSettings->playSound("PLAY");
        m_quit();
      },
      Color::White, Color::Yellow, Color::Black, "Quit", true, 60);
}

void MenuEnd::handle() {
  if (m_isEnd) {
    m_isEnd = false;
  } else {
    m_isEnd = true;
  }
}

void MenuEnd::handleEvent(Event &event) {
  for (auto &button : m_textBouttons) {
    if (button.second.isInside(Mouse::getPosition(m_window).x,
                               Mouse::getPosition(m_window).y)) {
      button.second.isHover();
    } else {
      button.second.isNotHover();
    }
  }

  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      int mouseX = Mouse::getPosition(m_window).x;
      int mouseY = Mouse::getPosition(m_window).y;
      for (auto &button : m_textBouttons) {
        button.second.handle(mouseX, mouseY);
      }
      for (auto &button : m_OnOffButton) {
        button.second.handle(mouseX, mouseY);
        if (button.second.isInside(mouseX, mouseY)) {
          button.second.switchSprite();
        }
      }
    }
  }
}
void MenuEnd::renderButtons(int XtopLeftCorner, int YtopLeftCorner) {
  for (auto &button : m_textBouttons) {
    button.second.render(m_window, XtopLeftCorner, YtopLeftCorner);
  }
  for (auto &button : m_OnOffButton) {
    button.second.render(m_window, XtopLeftCorner, YtopLeftCorner);
  }
}

void MenuEnd::render(Cam &cam) {
  if (isEnd()) {
    renderButtons(cam.getTopLeftX(), cam.getTopLeftY());
  }
  drawTextWithEdge(cam.getTopLeftX() + 100, cam.getTopLeftY() + 400, "Flying Monsters Killed: " + to_string(m_monsters.getNumFlyingMonstersKilled()) + " / " + to_string(m_monsters.getNumFlyingMonsters()),
                     &m_window, 30, sf::Color::Red, sf::Color::Black,
                     MINECRAFT_FONT_PATH);
  drawTextWithEdge(cam.getTopLeftX() + 100, cam.getTopLeftY() + 350, "Walking Monsters Killed: " + to_string(m_monsters.getNumWalkingMonstersKilled()) + " / " + to_string(m_monsters.getNumWalkingMonsters()),
                     &m_window, 30, sf::Color::Red, sf::Color::Black,
                     MINECRAFT_FONT_PATH);
  drawTextWithEdge(cam.getTopLeftX() + 100, cam.getTopLeftY() + 10, "GAME OVER",
                   &m_window, 65, sf::Color::Black, sf::Color::Black,
                   MINECRAFT_FONT_PATH);
  drawTextWithEdge(cam.getTopLeftX() + 95, cam.getTopLeftY() + 10, "GAME OVER",
                   &m_window, 65, sf::Color::Red, sf::Color::Black,
                   MINECRAFT_FONT_PATH);
}

bool MenuEnd::isEnd() const { return m_isEnd; }
