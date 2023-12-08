#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "../item/block.hpp"
#include "../item/item.hpp"

#include "../utils/graph.hpp"
#include <map>

using namespace std;

class Craft {
private:
  map<string, Node<Block> *> m_node;
  DirectedGraph<Block> m_graph;

public:
  Craft() {
    for (auto block : blockMap) {
      Node<Block> *node = new Node<Block>(block.second);
      m_node[block.first] = node;
    }
    for (auto nodeBlock : m_node) {
      m_graph.addNode(nodeBlock.second);
    }
    m_graph.addEdge(m_node["STONE"], m_node["COBBLESTONE"]);
    m_graph.addEdge(m_node["COBBLESTONE"], m_node["STONE"]);
    m_graph.addEdge(m_node["WOOD"], m_node["WOOD_PLANK"]);
    m_graph.addEdge(m_node["WOOD_PLANK"], m_node["LIBRARY"]);
  }

  bool hasCraft(string id) {
    return m_graph.hasNeighbor(m_node[id]) && m_node.find(id) != m_node.end();
  }

  Block *getCraft(string id) {
    if (!hasCraft(id)) {
      cerr << "No craft for " << id << endl;
      return nullptr;
    }
    return &m_graph.getNeighbor(m_node[id])->value;
  }
};

#endif /* CRAFT_HPP */