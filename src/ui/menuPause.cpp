#include "../../include/ui/menuPause.hpp"

const int RESUME_BUTTON_X = 100;
const int RESUME_BUTTON_Y = 210;
const int RESUME_BUTTON_WIDTH = 184;
const int RESUME_BUTTON_HEIGHT = 50;

const int QUIT_BUTTON_X = 100;
const int QUIT_BUTTON_Y = 314;
const int QUIT_BUTTON_WIDTH = 320;
const int QUIT_BUTTON_HEIGHT = 50;

MenuPause::MenuPause(RenderWindow &window, Sound &sound,
                     unordered_map<string, SoundBuffer> &buffers,
                     SoundSettings &soundSettings, bool ispause)
    : m_pause(ispause), m_window(window), m_sound(sound),
      m_soundSettings(soundSettings) {
  m_buffers = buffers;
  m_menuButtonColor["resume"] = Color::White;
  m_menuButtonColor["quit"] = Color::White;
}

void MenuPause::handle() {
  if (m_pause) {
    m_pause = false;
  } else {
    m_pause = true;
  }
}

void MenuPause::updateButtonColor(string buttonName, Color colorOf,
                                  Color colorTo, int mouseX, int mouseY, int x,
                                  int y, int width, int height) {
  if (isInside(mouseX, mouseY, x, y, width, height)) {
    m_menuButtonColor[buttonName] = colorOf;
  } else {
    m_menuButtonColor[buttonName] = colorTo;
  }
}
void MenuPause::updateButtonColors() {
  int mouseX = Mouse::getPosition(m_window).x;
  int mouseY = Mouse::getPosition(m_window).y;
  /* button resume */
  updateButtonColor("resume", Color::Yellow, Color::White, mouseX, mouseY,
                    RESUME_BUTTON_X, RESUME_BUTTON_Y, RESUME_BUTTON_WIDTH,
                    RESUME_BUTTON_HEIGHT);

  /* button quit */
  updateButtonColor("quit", Color::Yellow, Color::White, mouseX, mouseY,
                    QUIT_BUTTON_X, QUIT_BUTTON_Y, QUIT_BUTTON_WIDTH,
                    QUIT_BUTTON_HEIGHT);
}

void MenuPause::update() { updateButtonColors(); }

void MenuPause::handleEvent(Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      int mouseX = Mouse::getPosition(m_window).x;
      int mouseY = Mouse::getPosition(m_window).y;
      if (isInside(mouseX, mouseY, RESUME_BUTTON_X, RESUME_BUTTON_Y,
                   RESUME_BUTTON_WIDTH,
                   RESUME_BUTTON_HEIGHT)) { // resume button
        play_sound(&m_buffers["PLAY"], &m_sound);
        handle();
      } else if (isInside(mouseX, mouseY, QUIT_BUTTON_X, QUIT_BUTTON_Y,
                          QUIT_BUTTON_WIDTH,
                          QUIT_BUTTON_HEIGHT)) { // quit button
        play_sound(&m_buffers["PLAY"], &m_sound);
        m_window.close();
      }
    }
  }
  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::P) {
      handle();
    }
  }
}

void MenuPause::renderButton(int x, int y, Color edgeColor, string text,
                             string key) {
  drawTextWithEdge(x + 5, y + 5, text, &m_window, 50, sf::Color::Black,
                   sf::Color::Black, MINECRAFT_FONT_PATH);
  drawTextWithEdge(x, y, text, &m_window, 50, m_menuButtonColor[key],
                   sf::Color::Black, MINECRAFT_FONT_PATH);
}

void MenuPause::renderButtons(int XtopLeftCorner, int YtopLeftCorner) {
  /* button resume */

  renderButton(XtopLeftCorner + RESUME_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
               YtopLeftCorner + RESUME_BUTTON_Y * WINDOW_HEIGHT / CAM_HEIGHT,
               Color::Black, "Resume", "resume");

  /* button quit */
  renderButton(XtopLeftCorner + QUIT_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
               YtopLeftCorner + QUIT_BUTTON_Y * WINDOW_HEIGHT / CAM_HEIGHT,
               Color::Black, "Quit", "quit");
}

void MenuPause::render(Cam &cam) {
  int XtopLeftCorner = cam.getTopLeftX();
  int YtopLeftCorner = cam.getTopLeftY();
  if (m_pause) {
    /* buttons */
    renderButtons(XtopLeftCorner, YtopLeftCorner);
  }
}

bool MenuPause::isPause() const { return m_pause; }
