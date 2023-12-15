#include "../../include/ui/menu.hpp"

void Menu::initButtons() {
  m_textBouttons["play"] = TextButton(
      100, 210,
      [&]() {
        m_soundSettings->playSound("PLAY");
        m_phase = 2;
      },
      Color::White, Color::Yellow, Color::Black, "PLAY", true, 50);
  m_textBouttons["newGame"] = TextButton(
      100, 314,
      [&]() {
        m_soundSettings->playSound("PLAY");
        menu = false;
        new_game = true;
      },
      Color::White, Color::Yellow, Color::Black, "NEW GAME", true, 50);
  m_textBouttons["play_save"] = TextButton(
      100, 210,
      [&]() {
        m_soundSettings->playSound("PLAY");
        menu = false;
        play_save = true;
      },
      Color::White, Color::Yellow, Color::Black, "PLAY SAVE", true, 50);
  m_textBouttons["play_input"] = TextButton(
      100, 314,
      [&]() {
        m_soundSettings->playSound("PLAY");
        menu = false;
        play_input = true;
      },
      Color::White, Color::Yellow, Color::Black, "PLAY INPUT", true, 50);
  m_textBouttons["quit"] = TextButton(
      100, 413,
      [&]() {
        m_soundSettings->playSound("PLAY");
        quit();
      },
      Color::White, Color::Yellow, Color::Black, "QUIT", true, 50);

  Sprite spriteVolumeOn = createSprite("1", "../assets/img/volume_on.png");
  Sprite spriteVolumeOff = createSprite("2", "../assets/img/volume_off.png");

  m_OnOffButton["volume"] = OnOffButton(
      WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 50, 50,
      [&]() {
        m_soundSettings->playSound("PLAY");
        m_soundSettings->handleMute();
      },
      spriteVolumeOn, spriteVolumeOff);
}

Menu::Menu(RenderWindow &window, unordered_map<string, Sprite> &sprites,
           SoundSettings &soundSettings)
    : Ui(window), m_soundSettings(&soundSettings),
      m_map("../assets/menu_map.csv", false), m_mapRenderer(m_map),
      m_cam(CAM_WIDTH, 850, false),
      m_dayNightCycle(30, DAY_NIGHT_CYCLE_IMG_PATH) {
  m_sprites = sprites;
  // m_buffers = buffers;

  m_phase = 1; // phase of menu with play newGame and quit

  // what we do
  bool menu = true;
  bool play_save = false;
  bool play_input = false;
  bool new_game = false;

  initButtons();
}

void Menu::handleEvent(sf::Event &event) {
  int mouseX = Mouse::getPosition(m_window).x;
  int mouseY = Mouse::getPosition(m_window).y;

  for (auto &button : m_textBouttons) {
    if (button.second.isInside(mouseX, mouseY)) {
      button.second.isHover();
    } else {
      button.second.isNotHover();
    }
  }
  if (event.type == Event::Closed) {
    quit();
  }
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (m_phase == 1) {
        m_textBouttons["play"].handle(mouseX, mouseY);
        m_textBouttons["newGame"].handle(mouseX, mouseY);
      } else if (m_phase == 2) {
        m_textBouttons["play_save"].handle(mouseX, mouseY);
        m_textBouttons["play_input"].handle(mouseX, mouseY);
      }
      m_textBouttons["quit"].handle(mouseX, mouseY);

      if (m_OnOffButton["volume"].isInside(mouseX, mouseY))
        m_OnOffButton["volume"].switchSprite();

      m_OnOffButton["volume"].handle(mouseX, mouseY);
    }
  }
}

void Menu::quit() { m_window.close(); }

void Menu::run() {
  render();
  update();
}

void Menu::update() {
  m_map.update(m_cam.getX(), m_cam.getY());

  m_cam.update(m_cam.getX(), m_cam.getY(), 0, 0, m_map.getWidth(),
               m_map.getHeight(), m_window);

  m_cam.setX(m_cam.getX() + 2);

  m_dayNightCycle.update();

  if (m_cam.getX() > m_map.getWidth() * TILE_SIZE) {
    m_cam.setX(0);
  }
}

void Menu::renderButtons() {
  int x = m_cam.getTopLeftX();
  int y = m_cam.getTopLeftY();
  if (m_phase == 1) {
    m_textBouttons["play"].render(m_window, x, y);
    m_textBouttons["newGame"].render(m_window, x, y);
  } else if (m_phase == 2) {
    m_textBouttons["play_save"].render(m_window, x, y);
    m_textBouttons["play_input"].render(m_window, x, y);
  }
  m_OnOffButton["volume"].render(m_window, x, y);
  m_textBouttons["quit"].render(m_window, x, y);
}

void Menu::render() {
  m_window.clear(m_dayNightCycle.getCurrentColor());

  m_mapRenderer.render(m_window, m_sprites);

  drawTextWithEdge(m_cam.getTopLeftX() + 80, m_cam.getTopLeftY() + 55,
                   "MINECRAFT 2D", &m_window, 65, sf::Color::Black,
                   sf::Color::Black, MINECRAFT_FONT_PATH);
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

bool Menu::volumeOff() const { return m_soundSettings->isMute(); }
