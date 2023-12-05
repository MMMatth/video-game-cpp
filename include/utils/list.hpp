#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

using namespace std;

template <typename T> struct LinkedList {
  T data;
  LinkedList *suivant;
};

// Linked List
/**
 * @brief Creates an empty linked list.
 *
 * @return An empty linked list.
 */
template <typename T> LinkedList<T> *cons_empty() { return nullptr; }

/**
 * @brief Adds a link to the linked list.
 *
 * @param data to add to the linked list.
 * @param L The linked list.
 */
template <typename T> LinkedList<T> *addLink(T data, LinkedList<T> *L) {
  LinkedList<T> *newLink = new LinkedList<T>;
  newLink->data = data;
  newLink->suivant = L;
  return newLink;
}

/**
 * @brief Checks if the linked list is empty.
 *
 * @param L The linked list to check.
 * @return True if the list is empty, false otherwise.
 */
template <typename T> bool isEmpty(LinkedList<T> *L) { return L == nullptr; }

/**
 * @brief Retrieves the first link in the list.
 *
 * @param L The linked list.
 * @return The first link in the list.
 */
template <typename T> T head(LinkedList<T> *L) {
  if (isEmpty(L)) {
    cerr << "The list is empty: head" << endl;
    exit(0);
  }
  return L->data;
}

/**
 * @brief Retrieves the rest of the linked list excluding the first element.
 *
 * @param L The linked list.
 * @return The linked list excluding the first element.
 */
template <typename T> LinkedList<T> *rest(LinkedList<T> *L) {
  return L->suivant;
}

/**
 * @brief Frees the memory allocated for the linked list.
 *
 * @param L The linked list to be freed.
 */
template <typename T> void freeLinkedList(LinkedList<T> *L) {
  if (!isEmpty(L)) {
    freeLinkedList(rest(L));
    delete L;
  }
}

/**
 * @brief Removes a specific element from the linked list.
 *
 * @param data The element to be removed.
 * @param L The linked list.
 * @return The updated linked list after removing the element.
 */
template <typename T> LinkedList<T> *removeLink(T data, LinkedList<T> *L) {
  // Base case: empty list
  if (isEmpty(L)) {
    cerr << "Cannot remove element from an empty list" << endl;
    return nullptr;
  }else if (head(L) == data) { // Base case: element found at the beginning of the list
    return removeLink(data, rest(L));
  }else{ // Recursive case: search for the element in the rest of the list
    return addLink(head(L), removeLink(data, rest(L)));
  }

}

#endif