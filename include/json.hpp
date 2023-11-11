#ifndef JSON_HPP
#define JSON_HPP

#include "item.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

using namespace std;
using namespace sf;

Texture texture;

unordered_map<string, Sprite> getSpriteMap() {
  unordered_map<string, Sprite> sprites;
  if (!texture.loadFromFile(SPRITESHEET_IMG_PATH))
    cerr << "Unable to load spritesheet image " << SPRITESHEET_IMG_PATH << "\n";

  ifstream file(SPRITESHEET_CSV_PATH);

  if (file.is_open()) {
    string line;
    int row = 0;
    int column = 0;
    while (getline(file, line)) {
      if (row != 0) {
        stringstream ss(line);
        string cell, type;
        int x, y, width, height;
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
            break;
          }
          column++;
        }
        column = 0;

        /* we check the data */
        if (x < 0 || y < 0) {
          std::cerr << "Spritesheet invalid position : " << x << " " << y;
        }
        if (width < 0 || height < 0) {
          std::cerr << "Spritesheet invalid size : " << width << " " << height;
        }
        cout << type << " " << x << " " << y << " " << width << " " << height
             << "\n";
        sprites[type] = Sprite(texture, IntRect(x, y, width, height));
      }
      row++;
    }
  } else {
    cerr << "Unable to open file " << SPRITESHEET_CSV_PATH << "\n";
    exit(EXIT_FAILURE);
  }

  return sprites;
}

#endif /* JSON_HPP */