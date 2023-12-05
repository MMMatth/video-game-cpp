#include "../../include/utils/draw.hpp"

using namespace std;
using namespace sf;

/* graphics */

Texture texture;

void parseLine(const string &line, string &type, int &x, int &y, int &width,
               int &height) {
  stringstream ss(line);
  string cell;
  int column = 0;
  while (getline(ss, cell, ';')) {
    switch (column) {
    case 0:
      type = cell;
      break;
    case 1:
      x = stoi(cell);
      break;
    case 2:
      y = stoi(cell);
      break;
    case 3:
      width = stoi(cell);
      break;
    case 4:
      height = stoi(cell);
      break;
    default:
      cerr << "Invalid csv file : " << SPRITESHEET_CSV_PATH << "\n";
      exit(EXIT_FAILURE);
    }
    column++;
  }
}

void checkData(int x, int y, int width, int height) {
  if (x < 0 || y < 0)
    cerr << "Spritesheet invalid position : " << x << " " << y;
  if (width < 0 || height < 0)
    cerr << "Spritesheet invalid size : " << width << " " << height;
}

unordered_map<string, Sprite> initSprites() {
  unordered_map<string, Sprite> sprites;
  Error(!texture.loadFromFile(SPRITESHEET_IMG_PATH),
        "Unable to load spritesheet image.");

  ifstream file(SPRITESHEET_CSV_PATH);
  if (!file.is_open())
    handleFileError(SPRITESHEET_CSV_PATH);

  string line;
  int row = 0;
  while (getline(file, line)) {
    if (row != 0) {
      string type;
      int x, y, width, height;
      parseLine(line, type, x, y, width, height);
      checkData(x, y, width, height);
      sprites[type] = Sprite(texture, IntRect(x, y, width, height));
    }
    row++;
  }

  return sprites;
}

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height) {
  sprite.setPosition(x, y);
  sprite.setScale(width / sprite.getLocalBounds().width,
                  height / sprite.getLocalBounds().height);
  window->draw(sprite);
}

void drawSpritesWithShader(int x, int y, Sprite sprite, RenderWindow *window,
                           int width, int height, Shader *shader) {
  sprite.setPosition(x, y);
  sprite.setScale(width / sprite.getLocalBounds().width,
                  height / sprite.getLocalBounds().height);
  window->draw(sprite, shader);
}

void drawText(int x, int y, string text, RenderWindow *window, int size,
              Color color, string fontPath) {
  Font font;
  Error(!font.loadFromFile("../" + fontPath), "Error : font load fail");

  Text textObj;
  textObj.setFont(font);
  textObj.setString(text);
  textObj.setCharacterSize(size);
  textObj.setFillColor(color);
  textObj.setPosition(x, y);
  window->draw(textObj);
}

void drawTextWithEdge(int x, int y, string text, RenderWindow *window, int size,
                      Color color, Color edgeColor, string fontPath) {
  Font font;
  Error(!font.loadFromFile("../" + fontPath), "Error : font load fail");

  Text textObj;
  textObj.setFont(font);
  textObj.setString(text);
  textObj.setCharacterSize(size);
  textObj.setFillColor(color);
  textObj.setOutlineColor(edgeColor);
  textObj.setOutlineThickness(1);
  textObj.setPosition(x, y);
  window->draw(textObj);
}

void drawRectangle(int x, int y, int width, int height, RenderWindow *window,
                   Color color, int alpha) {
  RectangleShape rectangle;
  rectangle.setSize(Vector2f(width, height));
  rectangle.setPosition(x, y);
  rectangle.setFillColor(Color(color.r, color.g, color.b, alpha));
  window->draw(rectangle);
}

/* audio */
unordered_map<string, SoundBuffer> initBuffers() {
  unordered_map<string, SoundBuffer> soundBuffers;
  SoundBuffer buffer;

  Error(!buffer.loadFromFile(SOUND_BREAK_A_BLOCK),
        "Error loading sound break a block");
  soundBuffers["BREAK"] = buffer;

  Error(!buffer.loadFromFile(SOUND_PUT_A_BLOCK),
        "Error loading sound put a block");
  soundBuffers["PUT_BLOCK"] = buffer;

  Error(!buffer.loadFromFile(SOUND_PLAY), "Error loading sound play");
  soundBuffers["PLAY"] = buffer;

  Error(!buffer.loadFromFile(SOUND_JUMP), "Error loading sound jump");
  soundBuffers["JUMP"] = buffer;

  return soundBuffers;
}

void play_sound(SoundBuffer *buffer, Sound *sound) {
  sound->setBuffer(*buffer);
  sound->play();
}

void renderHealthBar(RenderWindow &window, int currentLife, int maxLife, int x, int y) {
  // Position of the health bar
  float healthBarX = x;
  float healthBarY = y;

  // Draw the black background of the health bar
  RectangleShape backgroundBar(Vector2f(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT));
  backgroundBar.setPosition(healthBarX, healthBarY);
  backgroundBar.setFillColor(Color::Black);

  window.draw(backgroundBar);

  // Check if currentLife is positive before drawing the red health bar
  if (currentLife > 0) {
    // Calculate the length of the red health bar based on current and maximum life
    float healthBarLength = static_cast<float>(currentLife) / maxLife * HEALTH_BAR_WIDTH;

    // Draw the red health bar
    RectangleShape healthBar(Vector2f(healthBarLength, HEALTH_BAR_HEIGHT));
    healthBar.setPosition(healthBarX, healthBarY);
    healthBar.setFillColor(Color::Red);

    window.draw(healthBar);
  }
}