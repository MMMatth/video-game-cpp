#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T> struct Node {
  T data;
  Node *next;
};

using namespace std;

template <typename T> class LinkedList {
private:
  Node<T> *head;

  void freeLinkedList() {
    Node<T> *start = head;
    Node<T> *current = start;
    do {
      Node<T> *nextNode = current->next;
      delete current;
      current = nextNode;
    } while (current != start && current != nullptr);
  }

public:
  LinkedList() : head(nullptr) {}
  LinkedList(T data) {
    head = new Node<T>;
    head->data = data;
    head->next = nullptr;
  }

  ~LinkedList() { freeLinkedList(); }

  bool isEmpty() { return head == nullptr; }

  bool isLinked() { return head->next != nullptr; }

  bool isCircular() {
    if (isEmpty()) {
      cerr << "The list is empty: isCircular" << endl;
      return false;
    }
    Node<T> *current = head;
    while (current->next != nullptr) {
      if (current->next == head) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void addLink(T data) {
    Node<T> *newLink = new Node<T>;
    newLink->data = data;
    newLink->next = nullptr;

    if (isEmpty()) {
      head = newLink;
    } else {
      Node<T> *current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newLink;
    }
  }

  void makeCircular() {
    if (isEmpty()) {
      cerr << "The list is empty: makeCircular" << endl;
      return;
    }
    Node<T> *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = head;
  }

  T *getHead() {
    if (isEmpty()) {
      cerr << "The list is empty: getHead" << endl;
      exit(0);
    }
    return &head->data;
  }

  Node<T> *getHeadNode() {
    if (isEmpty()) {
      cerr << "The list is empty: getHeadNode" << endl;
      exit(0);
    }
    return head;
  }

  Node<T> *getNextNode() {
    if (isEmpty()) {
      cerr << "The list is empty: getNextNode" << endl;
      exit(0);
    }
    return head->next;
  }

  void removeLink(T data) {
    if (isEmpty()) {
      cerr << "The list is empty: removeLink" << endl;
      return;
    }
  }

private:
  // void freeLinkedList() {
  //   Node *current = head;
  //   while (current != nullptr) {
  //     Node *nextNode = current->next;
  //     delete current;
  //     current = nextNode;
  //   }
  //   head = nullptr;
  // }
};

#endif