#ifndef JSON_HPP
#define JSON_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
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

  texture.loadFromFile(
      "../assets/img/spritesheet.png"); // Utilisez la texture globale ici

  for (auto &[mainKey, mainValue] : j.items()) {
    for (auto &[key, value] : mainValue.items()) {
      if (value.contains("spritesheet") && value["spritesheet"]["x"] != -1 &&
          value["spritesheet"]["y"] != -1) {
        Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(
            value["spritesheet"]["x"], value["spritesheet"]["y"],
            value["spritesheet"]["width"], value["spritesheet"]["height"]));
        sprites[key] = sprite;
      }
    }
  }

  return sprites;
}

#endif /* JSON_HPP */