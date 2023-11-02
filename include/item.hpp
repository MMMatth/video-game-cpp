#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
using namespace std;

class Item {
private:
  int m_id;
  string m_name;
  bool m_is_stackable;
  int m_amout; // -1 if not stackable

public:
  /* constructeur */
  Item(string name, int id, bool is_stackable, int amout = 1)
      : m_name(name), m_id(id), m_is_stackable(is_stackable), m_amout(amout){};
  Item() : m_name(""), m_id(0), m_is_stackable(false), m_amout(1){};
  /* destructeur */
  ~Item(){};

  /* setters */
  void setName(std::string name) { m_name = name; }
  void setId(int id) { m_id = id; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  void setAmount(int amount) { m_amout = amount; }
  /* getters */
  string getName() { return m_name; }
  int getId() { return m_id; }
  int getAmount() { return m_amout; }
  bool isStackable() { return m_is_stackable; }
};

#endif /* ITEM_HPP */