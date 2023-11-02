#ifndef ITEM_HPP
#define ITEM_HPP

#include "point.hpp"
#include <string>
#include <vector>
using namespace std;

class Item {
private:
  int m_id;
  string m_name;
  bool m_is_stackable;
  int m_amout; // -1 if not stackable
  Point m_spriteSheet;

public:
  /* constructeur */
  Item(string name, int id, bool is_stackable, int spriteSheetX,
       int spriteSheetY, int amout = 1)
      : m_spriteSheet(spriteSheetX, spriteSheetY), m_amout(amout), m_id(id),
        m_name(name), m_is_stackable(is_stackable) {}

  Item()
      : m_spriteSheet(), m_amout(1), m_id(0), m_name(""),
        m_is_stackable(false){};

  /* destructeur */
  // ~Item(){};

  /* setters */
  void setName(std::string name) { m_name = name; }
  void setId(int id) { m_id = id; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  void setAmount(int amount) { m_amout = amount; }
  void setSpriteSheetX(int spriteSheetX) { m_spriteSheet.setX(spriteSheetX); }
  void setSpriteSheetY(int spriteSheetY) { m_spriteSheet.setY(spriteSheetY); }
  /* getters */
  string getName() { return m_name; }
  int getId() { return m_id; }
  int getAmount() { return m_amout; }
  bool isStackable() { return m_is_stackable; }
  Point getSpriteSheet() { return m_spriteSheet; }
};
#endif /* ITEM_HPP */