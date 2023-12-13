#ifndef ITEM_HPP
#define ITEM_HPP

#include "../utils/coord.hpp"
#include <string>
#include <vector>
using namespace std;

/** @brief Represents an item in the game. */
class Item {
private:
  string m_name;       /** The name of the item. */
  bool m_is_stackable; /** Whether the item is stackable. */
  int m_amout;         /** The amount of the item. -1 if not stackable. */
  string m_type;       /** The type of the item. */

public:
  /** @brief Parameterized constructor for Item.
   * @param name The name of the item.
   * @param is_stackable Whether the item is stackable.
   * @param type The type of the item.
   * @param amount The amount of the item (default is 1).
   */
  Item(string name, bool is_stackable, string type, int amout = 1)
      : m_amout(amout), m_name(name), m_is_stackable(is_stackable),
        m_type(type) {}

  /** @brief the default constructor*/
  Item() : m_amout(1), m_name(""), m_is_stackable(false), m_type("UNDEFINED"){};

  /** @brief the destructor*/
  ~Item(){};

  /** @brief Set the ID of the item. */
  void setId(std::string name) { m_name = name; }

  /** @brief Set whether the item is stackable. */
  void setIsStackable(bool is_stackable) { m_is_stackable = is_stackable; }

  /** @brief Set the amount of the item. */
  void setAmount(int amount) { m_amout = amount; }

  /** @brief  Get the name of the item. */
  string getName() { return m_name; }

  /** @brief Get the type of the item. */
  string getType() { return m_type; }

  /** @brief Get the amount of the item. */
  int getAmount() { return m_amout; }

  /** @brief Check if the item is stackable. */
  bool isStackable() { return m_is_stackable; }
};
#endif /* ITEM_HPP */