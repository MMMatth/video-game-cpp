  #ifndef LIST_HPP
  #define LIST_HPP

  #include <iostream>

  using namespace std;

  template <typename T> class LinkedList {
  private:
    struct Node {
      T data;
      Node *next;
    };
    Node *head;

  public:
    LinkedList() : head(nullptr) {}

    // ~LinkedList() { freeLinkedList(); }

    bool isEmpty() { return head == nullptr; }

    void addLink(T data) {
      Node *newLink = new Node;
      newLink->data = data;
      newLink->next = head;
      head = newLink;
    }

    T getHead() {
      if (isEmpty()) {
        cerr << "The list is empty: getHead" << endl;
        exit(0);
      }
      return head->data;
    }

    void removeLink(T data) {
      if (isEmpty()) {
        cerr << "The list is empty: removeLink" << endl;
        return;
      }
      Node **indirect = &head;
      while (*indirect != nullptr) {
        if ((*indirect)->data == data) {
          Node *oldNode = *indirect;
          *indirect = (*indirect)->next;
          delete oldNode;
          return;
        }
        indirect = &(*indirect)->next;
      }
    }

    string toString() {
      string str = "";
      Node *current = head;
      while (current != nullptr) {
        str += to_string(current->data) + " ";
        current = current->next;
      }
      return str;
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