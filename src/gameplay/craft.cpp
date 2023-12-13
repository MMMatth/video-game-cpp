#include "../../include/gameplay/craft.hpp"

Craft::Craft() {
  /* we add the stones crafts */
  m_crafts.push_back(new LinkedList<Block>(blockMap["STONE"]));
  m_crafts.back()->addLink(blockMap["COBBLESTONE"]);
  m_crafts.back()->addLink(blockMap["BRICK"]);
  m_crafts.back()->makeCircular();

  /* we add the wood crafts */
  m_crafts.push_back(new LinkedList<Block>(blockMap["WOOD"]));
  m_crafts.back()->addLink(blockMap["WOOD_PLANK"]);
  m_crafts.back()->addLink(blockMap["LIBRARY"]);

  /* we add the Dirt crafts */
  m_crafts.push_back(new LinkedList<Block>(blockMap["DIRT"]));
  m_crafts.back()->addLink(blockMap["GRASS"]);
  m_crafts.back()->makeCircular();

  /* we add the FLOWER crafts */
  m_crafts.push_back(new LinkedList<Block>(blockMap["YELLOW_FLOWER"]));
  m_crafts.back()->addLink(blockMap["RED_FLOWER"]);

  m_isDay = true;
}

Craft::~Craft() {
  for (auto craft : m_crafts) {
    delete craft;
  }
}

void Craft::update(bool day) {
  if (day != m_isDay) {
    m_isDay = day;
    if (!day) {
      // if is night, add the craft "TORCH"
      for (auto craft : m_crafts) {
        Node<Block> *start = craft->getHeadNode();
        Node<Block> *current = start;
        do {
          if (current->data.getName() == "RED_FLOWER") {
            craft->addLink(blockMap["TORCH"]);
            break;
          }
          current = current->next;
        } while (current != start && current != nullptr);
      }
    } else {
      // if is day, remove the craft "TORCH"
      for (auto craft : m_crafts) {
        Node<Block> *start = craft->getHeadNode();
        Node<Block> *current = start;
        do {
          if (current->next != nullptr &&
              current->next->data.getName() == "TORCH") {
            Node<Block> *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            break;
          }
          current = current->next;
        } while (current != start && current != nullptr);
      }
    }
  }
}

bool Craft::hasCraft(string id) {
  for (auto craft : m_crafts) {
    Node<Block> *start = craft->getHeadNode(); // we get the head node
    Node<Block> *current = start;              // we set the current node
    do {
      if (current->data.getName() == id && current->next != nullptr) {
        return true;
      }
      current = current->next;
    }
    /* we compare the first and the last for the case of a cycle */
    while (current != start && current != nullptr);
  }
  return false;
}

Block *Craft::getCraft(string id) {
  if (!hasCraft(id)) {
    cerr << "No craft for " << id << endl;
    return nullptr;
  }
  for (auto craft : m_crafts) {
    Node<Block> *start = craft->getHeadNode();
    Node<Block> *current = start;
    do {
      if (current->data.getName() == id && current->next != nullptr) {
        return &current->next->data;
      }
      current = current->next;
    }
    /* we compare the first and the last for the case of a cycle */
    while (current != start && current != nullptr);
  }
  return nullptr;
}
