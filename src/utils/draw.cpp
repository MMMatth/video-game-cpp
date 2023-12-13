#include "../../include/utils/draw.hpp"

using namespace std;
using namespace sf;

/* we init a map for many texture*/
unordered_map<string, Texture> textures;

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
      cerr << "Invalid csv file : " << SPRITESHEET_INPUT_PATH << "\n";
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

void initSprite(string path, string type) {
  textures[type] = Texture(); // Initialiser la texture pour ce type
  if (!textures[type].loadFromFile(path))
    handleFileError(path);
}

unordered_map<string, Sprite> initSprites() {
  unordered_map<string, Sprite> sprites;
  initSprite(SPRITESHEET_IMG_PATH,
             "spritesheet"); // Initialiser la texture pour ce type
  ifstream file(SPRITESHEET_INPUT_PATH);
  if (!file.is_open())
    handleFileError(SPRITESHEET_INPUT_PATH);

  string line;
  int row = 0;
  while (getline(file, line)) {
    if (row != 0) {
      string type;
      int x, y, width, height;
      parseLine(line, type, x, y, width, height);
      checkData(x, y, width, height);

      sprites[type] = Sprite(
          textures["spritesheet"],
          IntRect(x, y, width, height)); // Utiliser la texture pour ce type
    }
    row++;
  }
  return sprites;
}

Sprite createSprite(string type, string path) {
  textures[type] = Texture(); // Initialiser la texture pour ce type
  initSprite(path, type);
  return Sprite(textures[type]);
}

void drawSprites(int x, int y, Sprite sprite, RenderWindow *window, int width,
                 int height) {
  sprite.setPosition(x, y);
  sprite.setScale(width / sprite.getLocalBounds().width,
                  height / sprite.getLocalBounds().height);
  window->draw(sprite);
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

int getTextWidth(string text, int size, string fontPath) {
  Font font;
  Error(!font.loadFromFile("../" + fontPath), "Error : font load fail");
  Text textObj;
  textObj.setFont(font);
  textObj.setString(text);
  textObj.setCharacterSize(size);
  return textObj.getLocalBounds().width;
}

int getTextHeight(string text, int size, string fontPath) {
  Font font;
  Error(!font.loadFromFile("../" + fontPath), "Error : font load fail");
  Text textObj;
  textObj.setFont(font);
  textObj.setString(text);
  textObj.setCharacterSize(size);
  return textObj.getLocalBounds().height;
}

void drawRectangle(int x, int y, int width, int height, RenderWindow *window,
                   Color color, int alpha) {
  RectangleShape rectangle;
  rectangle.setSize(Vector2f(width, height));
  rectangle.setPosition(x, y);
  rectangle.setFillColor(Color(color.r, color.g, color.b, alpha));
  window->draw(rectangle);
}
void drawEdge(int x, int y, int width, int height, RenderWindow *window,
              Color color, int alpha) {
  drawRectangle(x, y, width, 1, window, color, alpha);
  drawRectangle(x, y, 1, height, window, color, alpha);
  drawRectangle(x + width, y, 1, height, window, color, alpha);
  drawRectangle(x, y + height, width, 1, window, color, alpha);
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

  Error(!buffer.loadFromFile(SOUND_CLICK), "Error loading sound play");
  soundBuffers["PLAY"] = buffer;

  Error(!buffer.loadFromFile(SOUND_JUMP), "Error loading sound jump");
  soundBuffers["JUMP"] = buffer;

  return soundBuffers;
}

void play_sound(SoundBuffer *buffer, Sound *sound) {
  sound->setBuffer(*buffer);
  sound->play();
}