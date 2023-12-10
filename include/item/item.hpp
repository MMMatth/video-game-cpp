#ifndef ITEM_HPP
#define ITEM_HPP

#include "../utils/coord.hpp"
#include <string>
#include <vector>
using namespace std;

/**
 * @class Item
 * @brief Represents an item in the game.
 *
 * This class encapsulates the properties of an item, such as its name,
 * stackability, amount, and type.
 */
class Item {
private:
  string m_name;       /** The name of the item. */
  bool m_is_stackable; /** Whether the item is stackable. */
  int m_amout;         /** The amount of the item. -1 if not stackable. */
  string m_type;       /** The type of the item. */

public:
  /* constructeur */

  /**
   * Parameterized constructor for Item.
   * @param name The name of the item.
   * @param is_stackable Whether the item is stackable.
   * @param type The type of the item.
   * @param amount The amount of the item (default is 1).
   */
  Item(string name, bool is_stackable, string type, int amout = 1)
      : m_amout(amout), m_name(name), m_is_stackable(is_stackable),
        m_type(type) {}

  /** Default constructor for Item. */
  Item() : m_amout(1), m_name(""), m_is_stackable(false), m_type("UNDEFINED"){};

  /* destructeur */
  // ~Item(){};

  /* setters */

  /** Set the ID of the item. */
  void setId(std::string name) { m_name = name; }

  /** Set whether the item is stackable. */
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }

  /** Set the amount of the item. */
  void setAmount(int amount) { m_amout = amount; }

  /* getters */

  /** Get the name of the item. */
  string getName() { return m_name; }

  /** Get the type of the item. */
  string getType() { return m_type; }

  /** Get the amount of the item. */
  int getAmount() { return m_amout; }

  /** Check if the item is stackable. */
  bool isStackable() { return m_is_stackable; }
  /*others*/

  /** Convert the item to a string representation. */
  string toString() {
    string s = "";
    s += " id : " + m_name;
    s += " is_stackable : " + std::to_string(m_is_stackable);
    s += " amount : " + std::to_string(m_amout);
    return s;
  }
};
#endif /* ITEM_HPP */