#ifndef JSON_HPP
#define JSON_HPP

#include "item.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

Texture texture; // Déplacez la texture ici

unordered_map<string, Sprite> getSpriteMap() {
  unordered_map<string, Sprite> sprites;
  nlohmann::json j;
  ifstream file("../assets/csv/ressource.json");

  if (file.is_open()) {
    file >> j;
  } else {
    cerr << "Unable to open file ../assets/csv/ressource.json\n";
    exit(EXIT_FAILURE);
  }

  texture.loadFromFile("../assets/img/spritesheet.png");

  for (auto &[mainKey, mainValue] : j.items()) {
    if (mainValue.contains("spritesheet") &&
        mainValue["spritesheet"]["x"] != -1 &&
        mainValue["spritesheet"]["y"] != -1) {
      Sprite sprite;
      sprite.setTexture(texture);
      sprite.setTextureRect(IntRect(mainValue["spritesheet"]["x"],
                                    mainValue["spritesheet"]["y"],
                                    mainValue["spritesheet"]["width"],
                                    mainValue["spritesheet"]["height"]));
      sprites[mainKey] = sprite;
    }
  }

  return sprites;
}

#endif /* JSON_HPP */