#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Node {
public:
  T value;           /** the value of the Node*/
  Node<T> *neighbor; /** each node can have only one neighbor*/

  bool hasNeighbor() { return neighbor != nullptr; }
  Node(T val) : value(val), neighbor(nullptr) {}
};

/** implementation of directed graph each node can have only one neighbors*/
template <typename T> class DirectedGraph {
private:
  vector<Node<T> *> nodes;

public:
  void addNode(T value) {
    Node<T> *newNode = new Node<T>(value);
    nodes.push_back(newNode);
  }
  void addNode(Node<T> *node) { nodes.push_back(node); }

  void addEdge(Node<T> *from, Node<T> *to) { from->neighbor = to; }

  void addEdges(std::vector<Node<T> *> nodes) {
    for (size_t i = 0; i < nodes.size() - 1; ++i) {
      addEdge(nodes[i], nodes[i + 1]);
    }
  }

  bool hasCycle() {
    for (auto node : nodes) {
      if (hasCycle(node)) {
        return true;
      }
    }
    return false;
  }

  bool hasNeighbor(Node<T> *node) { return node->hasNeighbor(); }

  Node<T> *getNeighbor(Node<T> *node) { return node->neighbor; }
};