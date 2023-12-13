#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"

#include "../utils/list.hpp"
#include <array>
#include <vector>

using namespace std;

class Craft {
private:
  vector<LinkedList<Block> *> m_crafts;
  bool isday;
  bool m_craftChange;

public:
  Craft() {
    m_crafts.push_back(new LinkedList<Block>(blockMap["STONE"]));
    m_crafts.back()->addLink(blockMap["COBBLESTONE"]);
    m_crafts.back()->addLink(blockMap["BRICK"]);
    m_crafts.back()->makeCircular();

    m_crafts.push_back(new LinkedList<Block>(blockMap["WOOD"]));
    m_crafts.back()->addLink(blockMap["WOOD_PLANK"]);
    m_crafts.back()->addLink(blockMap["LIBRARY"]);

    m_crafts.push_back(new LinkedList<Block>(blockMap["DIRT"]));
    m_crafts.back()->addLink(blockMap["GRASS"]);
    m_crafts.back()->makeCircular();

    m_crafts.push_back(new LinkedList<Block>(blockMap["YELLOW_FLOWER"]));
    m_crafts.back()->addLink(blockMap["RED_FLOWER"]);

    isday = true;
  }

  ~Craft() {
    for (auto craft : m_crafts) {
      delete craft;
    }
  }

  void update(bool day) {
    if (day != isday) {
      isday = day;
      if (!day) {
        // Si c'est la nuit, ajoutez un craft à la "RED_FLOWER"
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
        // Si c'est le jour, supprimez le craft "TORCH"
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

  bool hasCraft(string id) {
    for (auto craft : m_crafts) {
      Node<Block> *start = craft->getHeadNode();
      Node<Block> *current = start;
      do {
        if (current->data.getName() == id && current->next != nullptr) {
          return true;
        }
        current = current->next;
      } while (current != start && current != nullptr);
    }
    return false;
  }

  Block *getCraft(string id) {
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
      } while (current != start && current != nullptr);
    }
    return nullptr;
  }
  // void addCraft(string idIn, string idTo) {
  //   if (hasCraft(idIn)) {
  //     cerr << "Craft already exists for " << idIn << endl;
  //     return;
  //   }
  //   m_crafts[idIn].addLink(blockMap[idTo]);
  // }

  // void removeCraft(string id) {
  //   if (!hasCraft(id)) {
  //     cerr << "No craft for " << id << endl;
  //     return;
  //   }
  //   m_crafts[id].removeLink(blockMap[id]);
  // }
};

#endif /* CRAFT_HPP */