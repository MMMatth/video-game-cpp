#ifndef ITEM_HPP
#define ITEM_HPP

#include "coord.hpp"
#include "sprites.hpp"
#include <string>
#include <vector>
using namespace std;

class Item {
private:
  string m_id;
  bool m_is_stackable;
  int m_amout; // -1 if not stackable

public:
  /* constructeur */
  Item(string id, bool is_stackable, int amout = 1)
      : m_amout(amout), m_id(id), m_is_stackable(is_stackable) {}

  Item() : m_amout(1), m_id(""), m_is_stackable(false){};

  /* destructeur */
  // ~Item(){};

  /* setters */
  void setId(std::string name) { m_id = name; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  void setAmount(int amount) { m_amout = amount; }

  /* getters */
  string getId() { return m_id; }
  int getAmount() { return m_amout; }
  bool isStackable() { return m_is_stackable; }
  /*others*/
  string toString() {
    string s = "";
    s += " id : " + m_id;
    s += " is_stackable : " + std::to_string(m_is_stackable);
    s += " amount : " + std::to_string(m_amout);
    return s;
  }
};
#endif /* ITEM_HPP */