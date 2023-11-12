#ifndef ITEM_HPP
#define ITEM_HPP

#include "coord.hpp"
#include "sprites.hpp"
#include <string>
#include <vector>
using namespace std;

class Item {
private:
  string m_name;
  bool m_is_stackable;
  int m_amout; // -1 if not stackable
  string m_type;

public:
  /* constructeur */
  Item(string name, bool is_stackable, string type, int amout = 1)
      : m_amout(amout), m_name(name), m_is_stackable(is_stackable),
        m_type(type) {}

  Item() : m_amout(1), m_name(""), m_is_stackable(false), m_type("UNDEFINED"){};

  /* destructeur */
  // ~Item(){};

  /* setters */
  void setId(std::string name) { m_name = name; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  void setAmount(int amount) { m_amout = amount; }

  /* getters */
  string getName() { return m_name; }
  string getType() { return m_type; }
  int getAmount() { return m_amout; }
  bool isStackable() { return m_is_stackable; }
  /*others*/
  string toString() {
    string s = "";
    s += " id : " + m_name;
    s += " is_stackable : " + std::to_string(m_is_stackable);
    s += " amount : " + std::to_string(m_amout);
    return s;
  }
};
#endif /* ITEM_HPP */