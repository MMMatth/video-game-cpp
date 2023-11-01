#include "../include/item.hpp"

Item::Item(string name, int id) : m_name(name), m_id(id) {}

Item::Item() : m_name(""), m_id(-1) {}