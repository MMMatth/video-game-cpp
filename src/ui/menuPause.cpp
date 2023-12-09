#include "../../include/ui/menuPause.hpp"

void quit() { exit(0); }

void MenuPause::initButtons() {
  m_textBouttons["resume"] = TextButton(
      100, 200, [&]() { handle(); }, Color::White, Color::Yellow, Color::Black,
      "Resume", true, 50);
  m_textBouttons["quit"] =
      TextButton(100, 300, m_quit, Color::White, Color::Yellow, Color::Black,
                 "Quit", true, 50);
}

MenuPause::MenuPause(RenderWindow &window, Sound &sound,
                     unordered_map<string, SoundBuffer> &buffers,
                     SoundSettings &soundSettings, bool ispause,
                     function<void()> quit)
    : m_pause(ispause), m_sound(sound), m_soundSettings(soundSettings),
      Ui(window), m_quit(quit) {
  m_buffers = buffers;
  initButtons();
}

void MenuPause::handle() {
  if (m_pause) {
    m_pause = false;
  } else {
    m_pause = true;
  }
}

void MenuPause::update() {}

void MenuPause::handleEvent(Event &event) {
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
    }
  }
  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::P) {
      handle();
    }
  }
}

void MenuPause::renderButtons(int XtopLeftCorner, int YtopLeftCorner) {
  for (auto &button : m_textBouttons) {
    button.second.render(m_window, XtopLeftCorner, YtopLeftCorner);
  }
}

void MenuPause::render(Cam &cam) {
  if (m_pause) {
    renderButtons(cam.getTopLeftX(), cam.getTopLeftY());
  }
}

bool MenuPause::isPause() const { return m_pause; }
