#include "../include/draw.hpp"
#include "../include/otherFunctions.hpp"

using namespace std;
using namespace sf;

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

unordered_map<string, Sprite> getSpriteMap() {
  unordered_map<string, Sprite> sprites;
  Error(!texture.loadFromFile(SPRITESHEET_IMG_PATH), "Unable to load spritesheet image.");

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