#include "../../include/ui/menu.hpp"

const int PLAY_BUTTON_X = 100;
const int PLAY_BUTTON_Y = 210;
const int PLAY_BUTTON_WIDTH = 184;
const int PLAY_BUTTON_HEIGHT = 50;

const int NEW_GAME_BUTTON_X = 100;
const int NEW_GAME_BUTTON_Y = 314;
const int NEW_GAME_BUTTON_WIDTH = 320;
const int NEW_GAME_BUTTON_HEIGHT = 50;

const int QUIT_BUTTON_X = 100;
const int QUIT_BUTTON_Y = 413;
const int QUIT_BUTTON_WIDTH = 170;
const int QUIT_BUTTON_HEIGHT = 50;

const int PLAY_SAVE_BUTTON_X = 100;
const int PLAY_SAVE_BUTTON_Y = 210;
const int PLAY_SAVE_BUTTON_WIDTH = 411;
const int PLAY_SAVE_BUTTON_HEIGHT = 50;

const int PLAY_INPUT_BUTTON_X = 100;
const int PLAY_INPUT_BUTTON_Y = 314;
const int PLAY_INPUT_BUTTON_WIDTH = 411;
const int PLAY_INPUT_BUTTON_HEIGHT = 50;

Menu::Menu(RenderWindow &window, Sound &sound,
           unordered_map<string, Sprite> &sprites,
           unordered_map<string, SoundBuffer> &buffers,
           SoundSettings &soundSettings)
    : m_window(window), m_sound(sound), m_soundSettings(soundSettings),
      m_clickOnOff(2), m_map("../assets/menu_map.csv", false),
      m_mapRenderer(m_map), m_cam(CAM_WIDTH, 850, false),
      m_dayNightCycle(30, DAY_NIGHT_CYCLE_IMG_PATH) {
  m_sprites = sprites;
  // we charge the sound
  m_buffers = buffers;

  phase = 1;

  // what we do
  bool menu = true;
  bool play_save = false;
  bool play_input = false;
  bool new_game = false;

  // we init the buttons colors
  m_menuButtonColor["play"] = Color::White;
  m_menuButtonColor["newGame"] = Color::White;
  m_menuButtonColor["quit"] = Color::White;
}
void Menu::handleEvent(sf::Event &event) {
  int mouseX = Mouse::getPosition(m_window).x;
  int mouseY = Mouse::getPosition(m_window).y;
  if (event.type == Event::Closed) {
    quit();
  }
  if (event.type == Event::MouseButtonPressed) {
    if (isInside(mouseX, mouseY, QUIT_BUTTON_X, QUIT_BUTTON_Y,
                 QUIT_BUTTON_WIDTH,
                 QUIT_BUTTON_HEIGHT)) { // quit button
      play_sound(&m_buffers["PLAY"], &m_sound);
      quit();
    }
    if (phase == 1) {
      if (isInside(mouseX, mouseY, PLAY_BUTTON_X, PLAY_BUTTON_Y,
                   PLAY_BUTTON_WIDTH,
                   PLAY_BUTTON_HEIGHT)) { // PLAY button
        play_sound(&m_buffers["PLAY"], &m_sound);
        phase = 2;
      } else if (isInside(mouseX, mouseY, NEW_GAME_BUTTON_X, NEW_GAME_BUTTON_Y,
                          NEW_GAME_BUTTON_WIDTH,
                          NEW_GAME_BUTTON_HEIGHT)) { // new game button
        play_sound(&m_buffers["PLAY"], &m_sound);
        menu = false;
        new_game = true;
      }
    } else if (phase == 2) {
      if (isInside(mouseX, mouseY, PLAY_SAVE_BUTTON_X, PLAY_SAVE_BUTTON_Y,
                   PLAY_SAVE_BUTTON_WIDTH,
                   PLAY_SAVE_BUTTON_HEIGHT)) { // PLAY save button
        play_sound(&m_buffers["PLAY"], &m_sound);
        menu = false;
        play_save = true;
      } else if (isInside(mouseX, mouseY, PLAY_INPUT_BUTTON_X,
                          PLAY_INPUT_BUTTON_Y, PLAY_INPUT_BUTTON_WIDTH,
                          PLAY_INPUT_BUTTON_HEIGHT)) { // PLAY input button
        play_sound(&m_buffers["PLAY"], &m_sound);
        menu = false;
        play_input = true;
      }
    }
  }
}

void Menu::quit() { m_window.close(); }

void Menu::run() {
  render();
  update();
}

void Menu::updateButtonColor(string buttonName, Color colorOf, Color colorTo,
                             int mouseX, int mouseY, int x, int y, int width,
                             int height) {
  if (isInside(mouseX, mouseY, x, y, width, height)) {
    m_menuButtonColor[buttonName] = colorOf;
  } else {
    m_menuButtonColor[buttonName] = colorTo;
  }
}

void Menu::updateButtonColors() {
  int mouseX = Mouse::getPosition(m_window).x;
  int mouseY = Mouse::getPosition(m_window).y;
  if (phase == 1) {
    /* button play */
    updateButtonColor("play", Color::Yellow, Color::White, mouseX, mouseY,
                      PLAY_BUTTON_X, PLAY_BUTTON_Y, PLAY_BUTTON_WIDTH,
                      PLAY_BUTTON_HEIGHT);
    /* button newGame */
    updateButtonColor("newGame", Color::Yellow, Color::White, mouseX, mouseY,
                      NEW_GAME_BUTTON_X, NEW_GAME_BUTTON_Y,
                      NEW_GAME_BUTTON_WIDTH, NEW_GAME_BUTTON_HEIGHT);
  } else if (phase == 2) {
    /* button play save*/
    updateButtonColor("play_save", Color::Yellow, Color::White, mouseX, mouseY,
                      PLAY_SAVE_BUTTON_X, PLAY_SAVE_BUTTON_Y,
                      PLAY_SAVE_BUTTON_WIDTH, PLAY_SAVE_BUTTON_HEIGHT);
    /* button play input*/
    updateButtonColor("play_input", Color::Yellow, Color::White, mouseX, mouseY,
                      PLAY_INPUT_BUTTON_X, PLAY_INPUT_BUTTON_Y,
                      PLAY_INPUT_BUTTON_WIDTH, PLAY_INPUT_BUTTON_HEIGHT);
  }
  /* button quit */
  updateButtonColor("quit", Color::Yellow, Color::White, mouseX, mouseY,
                    QUIT_BUTTON_X, QUIT_BUTTON_Y, QUIT_BUTTON_WIDTH,
                    QUIT_BUTTON_HEIGHT);
}

void Menu::update() {
  m_map.update(m_cam.getX(), m_cam.getY());

  m_cam.update(m_cam.getX(), m_cam.getY(), 0, 0, m_map.get_width(),
               m_map.get_height(), m_window);

  m_cam.setX(m_cam.getX() + 2);

  m_dayNightCycle.update();

  updateButtonColors();

  if (m_cam.getX() > m_map.get_width() * TILE_SIZE) {
    m_cam.setX(0);
  }
}

void Menu::renderButton(int x, int y, Color edgeColor, string text,
                        string key) {
  drawTextWithEdge(x + 5, y + 5, text, &m_window, 50, sf::Color::Black,
                   sf::Color::Black, MINECRAFT_FONT_PATH);
  drawTextWithEdge(x, y, text, &m_window, 50, m_menuButtonColor[key],
                   sf::Color::Black, MINECRAFT_FONT_PATH);
}

void Menu::renderButtons() {
  int x = m_cam.getX() - m_cam.getWidth() / 2;
  int y = m_cam.getY() - m_cam.getHeight() / 2;
  if (phase == 1) {
    int newX = x + PLAY_BUTTON_X;
    renderButton(x + PLAY_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
                 y + PLAY_BUTTON_Y * WINDOW_WIDTH / CAM_WIDTH, Color::Black,
                 "PLAY", "play");

    renderButton(
        m_cam.getTopLeftX() + NEW_GAME_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
        m_cam.getTopLeftY() + NEW_GAME_BUTTON_Y * WINDOW_WIDTH / CAM_WIDTH,
        Color::Black, "NEW GAME", "newGame");
  } else if (phase == 2) {

    renderButton(
        m_cam.getTopLeftX() + PLAY_SAVE_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
        m_cam.getTopLeftY() + PLAY_SAVE_BUTTON_Y * WINDOW_WIDTH / CAM_WIDTH,
        Color::Black, "PLAY SAVE", "play_save");

    renderButton(
        m_cam.getTopLeftX() + PLAY_INPUT_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
        m_cam.getTopLeftY() + PLAY_INPUT_BUTTON_Y * WINDOW_WIDTH / CAM_WIDTH,
        Color::Black, "PLAY INPUT", "play_input");
  }

  renderButton(m_cam.getTopLeftX() + QUIT_BUTTON_X * WINDOW_WIDTH / CAM_WIDTH,
               m_cam.getTopLeftY() + QUIT_BUTTON_Y * WINDOW_WIDTH / CAM_WIDTH,
               Color::Black, "QUIT", "quit");
}

void Menu::render() {
  m_window.clear(m_dayNightCycle.getColor());

  m_mapRenderer.render(m_window, m_sprites);

  drawTextWithEdge(m_cam.getTopLeftX() + 75, m_cam.getTopLeftY() + 50,
                   "MINECRAFT 2D", &m_window, 65, sf::Color::White,
                   sf::Color::Black, MINECRAFT_FONT_PATH);

  renderButtons();

  m_window.display();
}

bool Menu::isActive() const { return menu; }
bool Menu::isNewGame() const { return new_game; }
bool Menu::isPlaySave() const { return play_save; }
bool Menu::isPlayInput() const { return play_input; }

void Menu::setActive(bool active) { menu = active; }
void Menu::setIsNewGame(bool active) { new_game = active; }
void Menu::setIsPlaySave(bool active) { play_save = active; }
void Menu::setIsPlayInput(bool active) { play_input = active; }

bool Menu::volumeOff() const { return m_sound.getVolume() == 0; }

void Menu::resetClickOnOff() { m_clickOnOff = 2; }
