#ifndef LIST_HPP
#define LIST_HPP

#include "monster.hpp"
#include <iostream>
#include <cstdbool>

using namespace std;

typedef struct MonsterList *monsterList ; 
struct MonsterList {
  Monster *m; 
  monsterList suivant ;
};

// Linked List
  /**
   * @brief Creates an empty monster list.
   *
   * @return An empty monster list.
   */
  monsterList cons_empty();

  /**
   * @brief Adds a monster to the monster list.
   *
   * @param m Pointer to the monster to be added.
   * @param M The existing monster list.
   * @return Updated monster list with the new monster.
   */
  monsterList addMonster(Monster *m, monsterList M);

  /**
   * @brief Checks if the monster list is empty.
   *
   * @param M The monster list to check.
   * @return True if the list is empty, false otherwise.
   */
  bool isEmpty(monsterList M);

  /**
   * @brief Retrieves the first monster in the list.
   *
   * @param M The monster list.
   * @return The first monster in the list.
   */
  Monster* head(monsterList M);

  /**
   * @brief Retrieves the rest of the monster list excluding the first element.
   *
   * @param M The monster list.
   * @return The monster list excluding the first element.
   */
  monsterList rest(monsterList M);

  /**
   * @brief Frees the memory allocated for the monster list.
   *
   * @param M The monster list to be freed.
   */
  void free_monsterList (monsterList M);

#endif