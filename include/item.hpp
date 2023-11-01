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

public:
  Item(string name, int id, bool is_stackable)
      : m_name(name), m_id(id), m_is_stackable(is_stackable){};
  Item() : m_name(""), m_id(0), m_is_stackable(false){};

  void setName(std::string name) { m_name = name; }
  void setId(int id) { m_id = id; }
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }
  string getName() { return m_name; }
  int getId() { return m_id; }
  bool isStackable() { return m_is_stackable; }
};

#endif /* ITEM_HPP */