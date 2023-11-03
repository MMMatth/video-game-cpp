#ifndef ITEM_HPP
#define ITEM_HPP

#include "point.hpp"
#include "sprites.hpp"
#include <string>
#include <vector>
using namespace std;

class Item {
private:
  int m_id;
  string m_name;
  bool m_is_stackable;
  int m_amout; // -1 if not stackable
  Sprites m_spriteSheet;

public:
  /* constructeur */
  Item(int id, string name, int spriteX, int spriteY, int spriteW, int spriteH,
       bool is_stackable, int amout = 1)
      : m_spriteSheet(spriteX, spriteY, spriteW, spriteH), m_amout(amout),
        m_id(id), m_name(name), m_is_stackable(is_stackable) {}

  Item()
      : m_spriteSheet(), m_amout(1), m_id(-1), m_name(""),
        m_is_stackable(false){};

  /* destructeur */
  // ~Item(){};

  /* setters */
  void setName(std::string name) { m_name = name; }
  void setId(int id) { m_id = id; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  void setAmount(int amount) { m_amout = amount; }
  void setSpriteSheet(Sprites spriteSheet) { m_spriteSheet = spriteSheet; }
  void setSpriteSheetHeight(int spriteSheetHeight) {
    m_spriteSheet.setHeight(spriteSheetHeight);
  }
  void setSpriteSheetWidth(int spriteSheetWidth) {
    m_spriteSheet.setWidth(spriteSheetWidth);
  }
  void setSpriteSheetX(int spriteSheetX) { m_spriteSheet.setX(spriteSheetX); }
  void setSpriteSheetY(int spriteSheetY) { m_spriteSheet.setY(spriteSheetY); }
  /* getters */
  string getName() { return m_name; }
  int getId() { return m_id; }
  int getAmount() { return m_amout; }
  bool isStackable() { return m_is_stackable; }
  Sprites getSpriteSheet() { return m_spriteSheet; }
  /*others*/
  string toString() {
    string s = "";
    s += "id : " + std::to_string(m_id);
    s += " name : " + m_name;
    s += " is_stackable : " + std::to_string(m_is_stackable);
    s += " amount : " + std::to_string(m_amout);
    s += " spriteSheet : " + m_spriteSheet.toString();
    return s;
  }
};
#endif /* ITEM_HPP */