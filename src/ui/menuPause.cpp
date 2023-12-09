#include "../../include/ui/menuPause.hpp"

void MenuPause::initButtons() {
  m_textBouttons["resume"] = TextButton(
      100, 200,
      [&]() {
        play_sound(&m_buffers["PLAY"], &m_sound);
        handle();
      },
      Color::White, Color::Yellow, Color::Black, "Resume", true, 50);
  m_textBouttons["quit"] = TextButton(
      100, 300,
      [&]() {
        play_sound(&m_buffers["PLAY"], &m_sound);
        m_quit();
      },
      Color::White, Color::Yellow, Color::Black, "Quit", true, 50);

  Sprite spriteVolumeOn = createSprite("1", "../assets/img/volume_on.png");
  Sprite spriteVolumeOff = createSprite("2", "../assets/img/volume_off.png");

  m_spriteButton["volume"] = OnOffButton(
      100, 400, 50, 50,
      [&]() {
        play_sound(&m_buffers["PLAY"], &m_sound);
        if (m_soundSettings->getVolume() == 0) {
          m_soundSettings->setVolume(VOLUME);
        } else {
          m_soundSettings->setVolume(0);
        }
        m_sound.setVolume(m_soundSettings->getVolume());
      },
      spriteVolumeOn, spriteVolumeOff, m_soundSettings->getVolume() != 0);
}

MenuPause::MenuPause(RenderWindow &window, Sound &sound,
                     unordered_map<string, SoundBuffer> &buffers,
                     SoundSettings &soundSettings, bool ispause,
                     function<void()> quit)
    : m_pause(ispause), m_sound(sound), m_soundSettings(&soundSettings),
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
      for (auto &button : m_spriteButton) {
        button.second.handle(mouseX, mouseY);
        if (button.second.isInside(mouseX, mouseY)) {
          button.second.switchSprite();
        }
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
  for (auto &button : m_spriteButton) {
    button.second.render(m_window, XtopLeftCorner, YtopLeftCorner);
  }
}

void MenuPause::render(Cam &cam) {
  if (m_pause) {
    renderButtons(cam.getTopLeftX(), cam.getTopLeftY());
  }
}

bool MenuPause::isPause() const { return m_pause; }
