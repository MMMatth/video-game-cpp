#include "../../include/ui/menu.hpp"

Menu::Menu(RenderWindow &window)
    : m_menu(true), m_window(window), m_sound(), m_newGame(false),
      m_soundSettings(5), m_clickOnOff(2), m_map("../assets/menu_map.csv"),
      m_mapRenderer(m_map), m_cam(CAM_WIDTH, 850),
      m_dayNightCycle(30, DAY_NIGHT_CYCLE_IMG_PATH) {
  m_sprites = initSprites();
  // we charge the sound
  Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound");
  m_sound.setVolume(m_soundSettings.getVolume());

  phase = 1;

  m_menuButtonsPressed["play"] = Color::White;
  m_menuButtonsPressed["newGame"] = Color::White;
  m_menuButtonsPressed["quit"] = Color::White;
}
void Menu::handleEvent(sf::Event &event) {
  int mouseX = event.mouseButton.x;
  int mouseY = event.mouseButton.y;
  if (event.type == Event::Closed) {
    quit();
  }
  if (event.type == Event::MouseButtonPressed) {
    printf("mouseX : %d, mouseY : %d\n", mouseX, mouseY);

    if (isInside(mouseX, mouseY, 100, 413, 170, 50)) { // quit button
      play_sound(&buffer, &m_sound);
      quit();
    }
    if (phase == 1) {
      if (isInside(mouseX, mouseY, 100, 210, 184, 50)) { // play button
        play_sound(&buffer, &m_sound);
        phase = 2;
      } else if (isInside(mouseX, mouseY, 100, 314, 320,
                          50)) { // new game button
        play_sound(&buffer, &m_sound);
        m_menu = false;
        m_newGame = true;
      }
    } else if (phase == 2) {
      if (isInside(mouseX, mouseY, 100, 210, 411, 50)) { // play save button
        play_sound(&buffer, &m_sound);
        m_menu = false;
      } else if (isInside(mouseX, mouseY, 100, 314, 411,
                          50)) { // play input button
        play_sound(&buffer, &m_sound);
        m_menu = false;
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
    m_menuButtonsPressed[buttonName] = colorOf;
  } else {
    m_menuButtonsPressed[buttonName] = colorTo;
  }
}

void Menu::updateButtonColors() {
  int mouseX = Mouse::getPosition(m_window).x;
  int mouseY = Mouse::getPosition(m_window).y;
  if (phase == 1) {
    /* button play */
    updateButtonColor("play", Color::Yellow, Color::White, mouseX, mouseY, 100,
                      210, 184, 50);
    /* button newGame */
    updateButtonColor("newGame", Color::Yellow, Color::White, mouseX, mouseY,
                      100, 314, 320, 50);
  } else if (phase == 2) {
    /* button play save*/
    updateButtonColor("play_save", Color::Yellow, Color::White, mouseX, mouseY,
                      100, 210, 411, 50);
    /* button play input*/
    updateButtonColor("play_input", Color::Yellow, Color::White, mouseX, mouseY,
                      100, 314, 411, 50);
  }
  /* button quit */
  updateButtonColor("quit", Color::Yellow, Color::White, mouseX, mouseY, 100,
                    413, 170, 50);
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
  drawTextWithEdge(x, y, text, &m_window, 50, m_menuButtonsPressed[key],
                   sf::Color::Black, MINECRAFT_FONT_PATH);
}

void Menu::renderButtons() {

  int top_left_hands_x =
      m_cam.getTopLeftX() + m_cam.getWidth() / 2 - CAM_HEIGHT / 2;

  if (phase == 1) {

    renderButton(top_left_hands_x, m_cam.getTopLeftY() + 150, Color::Black,
                 "PLAY", "play");

    renderButton(top_left_hands_x, m_cam.getTopLeftY() + 225, Color::Black,
                 "NEW GAME", "newGame");

  } else if (phase == 2) {

    renderButton(top_left_hands_x, m_cam.getTopLeftY() + 150, Color::Black,
                 "PLAY SAVE", "play_save");

    renderButton(top_left_hands_x, m_cam.getTopLeftY() + 225, Color::Black,
                 "PLAY INPUT", "play_input");
  }

  renderButton(top_left_hands_x, m_cam.getTopLeftY() + 300, Color::Black,
               "QUIT", "quit");
}

void Menu::render() {
  m_window.clear(m_dayNightCycle.getColor());

  m_mapRenderer.render(m_window, m_sprites);

  drawTextWithEdge(m_cam.getTopLeftX() + m_cam.getWidth() / 2 - CAM_HEIGHT / 2,
                   m_cam.getTopLeftY() + 50, "MINECRAFT 2D", &m_window, 65,
                   sf::Color::White, sf::Color::Black, MINECRAFT_FONT_PATH);

  renderButtons();

  m_window.display();
}

bool Menu::isActive() const { return m_menu; }

bool Menu::isNewGame() const { return m_newGame; }

void Menu::setIsNewGame(bool newGame) { m_newGame = newGame; }

bool Menu::volumeOff() const { return m_sound.getVolume() == 0; }

void Menu::resetClickOnOff() { m_clickOnOff = 2; }
