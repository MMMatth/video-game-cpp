#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

/** @brief stucture who represente a node of a linked list*/
template <typename T> struct Node {
  T data;     /**< data of the node*/
  Node *next; /**< pointer to the next node nullptr if the node is the last*/
};

using namespace std;

/** @brief class who represente a linked list */
template <typename T> class LinkedList {
private:
  Node<T> *head; /**< pointer to the first node of the list*/

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
  /** @brief default constructor */
  LinkedList() : head(nullptr) {}

  /** @brief constructor with a data
   * @param data the data of the first node
   */
  LinkedList(T data) {
    head = new Node<T>;
    head->data = data;
    head->next = nullptr;
  }

  /** @brief default destructor */
  ~LinkedList() { freeLinkedList(); }

  /** @brief function to know if the list is empty */
  bool isEmpty() { return head == nullptr; }

  /** @brief function to know if head of list is linked */
  bool isLinked() { return head->next != nullptr; }

  /** @brief function to know if the list is circular (the last link to the
   * first) */
  bool isCircular() {
    if (isEmpty()) {
      cerr << "The list is empty: isCircular" << endl;
      return false;
    }
    Node<T> *current = head;           // start from the first link
    while (current->next != nullptr) { // navigate to the end of the list
      if (current->next == head) {     // if the link reference to the first
                                       // link, then it is circular
        return true;
      }
      current = current->next; // move to next link
    }
    return false;
  }

  /** @brief function to add a link at the end of the list
   * @param data the data of the new link
   */
  void addLink(T data) {
    Node<T> *newLink = new Node<T>; // create a new link
    newLink->data = data;           // give it data
    newLink->next = nullptr;        // make it point to nothing because it will
                                    // be the last element
    if (isEmpty()) {                // if the list is empty
      head = newLink;               // the new link is the head
    } else {
      Node<T> *current = head;           // start from the first link
      while (current->next != nullptr) { // navigate to the end of the list
        current = current->next;
      }
      current->next = newLink; // assign newLink in the last link
    }
  }

  /** @brief function to add a link at the end of the list
   * @param data the data of the new link
   */
  void makeCircular() {
    if (isEmpty()) {
      cerr << "The list is empty: makeCircular" << endl;
      return;
    }
    Node<T> *current = head;           // start from the first link
    while (current->next != nullptr) { // navigate to the end of the list
      current = current->next;
    }
    current->next = head; // assign head in the last link
  }

  /** @brief function to get the data of the head
   * @return the data of the head
   */
  T *getHead() {
    if (isEmpty()) { // if list is empty, return nullptr
      cerr << "The list is empty: getHead" << endl;
      return nullptr;
    }
    return &head->data; // return the data of the head
  }

  /** @brief function to get the head
   * @return the head node
   */
  Node<T> *getHeadNode() {
    if (isEmpty()) {
      cerr << "The list is empty: getHeadNode" << endl;
      exit(0);
    }
    return head;
  }

  /** @brief function to get the next node of the head
   * @return the next node of the head
   */
  Node<T> *getNextNode() {
    if (isEmpty()) {
      cerr << "The list is empty: getNextNode" << endl;
      exit(0);
    }
    return head->next;
  }

  /** @brief function to remove the head
   * @return the data of the node to remove
   */
  void removeLink(T data) {
    if (isEmpty()) {
      cerr << "The list is empty: removeLink" << endl;
      return;
    }
  }
};

#endif