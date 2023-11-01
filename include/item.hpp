#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
using namespace std;

class Item {
private:
  int m_id;
  string m_name;

public:
  Item(string name, int id);
  Item();

  void setName(std::string name) { m_name = name; }
  void setId(int id) { m_id = id; }
  string getName() { return m_name; }
  int getId() { return m_id; }
};

#endif /* ITEM_HPP */