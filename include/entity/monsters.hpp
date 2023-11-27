#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../map/map.hpp"
#include "../item/block.hpp"
#include "../rendering/entityRender.hpp"
#include "flying_monster.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>


typedef struct MonsterList *monsterList ; 
struct MonsterList {
  Monster *m; 
  monsterList suivant ;
};

/**
 * @class Monsters
 * @brief Represents a collection of monsters in the game.
 *
 * This class manages a collection of different types of monsters and provides
 * functionality to add, update, and render them.
*/
class Monsters {
private:
  monsterList m_monsters = cons_empty();  // Collection of monsters
  vector<EntityRender *> m_monsterRenderers;  // Renderers for the monsters
  const Map m_map;  // Reference to the game map

public:
  /**
   * @brief Constructor for Monsters.
   * @param map Reference to the game map.
   * @details Initializes the Monsters collection and adds random flying and
   * walking monsters to it.
  */
  Monsters(const Map &map) : m_monsters(), m_map(map) {

    srand(time(NULL));

    for(int i = 0; i < NUM_MONSTERS_FLYING; i++) {
      addRandomMonster(new FlyingMonster(0, 0, 30, 50, 3, 5), map);
    }

    for(int i = 0; i < NUM_MONSTERS_WALKING; i++) {
      addRandomMonster(new WalkingMonster(0, 0, 30, 50, 2, 5, 18), map);
    }
    // addMonster(new FlyingMonster(100, 100, 32, 32, 5, 5));
    // addMonster(new WalkingMonster(200, 200, 32, 32, 5, 5, 10));
  }

 /**
   * @brief Getter for the collection of monsters.
   * @return Linked list containing pointers to monsters.
  */
  monsterList getMonsters() const { return m_monsters; }

  /**
   * @brief Adds a random monster to the collection at a valid position on the
   * map.
   * @param monster Pointer to the monster to be added.
   * @param map Reference to the game map.
  */
  void addRandomMonster(Monster *monster, Map map) {
    int monsterWidth = monster->getWidth();
    int monsterHeight = monster->getHeight();

    do {
      int x = rand() % WINDOW_WIDTH;
      int y = rand() % WINDOW_HEIGHT;
      monster->setX(x);
      monster->setY(y);
    } while (map.collidesWithSolidBlock(monster));

    m_monsters = addMonster(monster, m_monsters);
    m_monsterRenderers.push_back(new EntityRender(*monster));
  }

  /**
   * @brief Handles collisions between monsters and the map.
   * @param map Pointer to the game map.
   * @param camX Camera X position.
   * @param camY Camera Y position.
  */
  void collide(Map *map, int camX, int camY) {
    monsterList temp = m_monsters;
    while (!is_empty(temp)) {
      cout << "non vide " << endl;
      map->collide(head(temp), camX, camY);
      map->collide(head(temp));
      temp = rest(temp);
    }
  }

  /**
   * @brief Renders all monsters on the screen.
   * @param window Reference to the game window.
   * @param sprites Map of sprites for rendering.
   * @param key Key to select the appropriate sprite.
   * @param nbFrame Number of frames for animation.
  */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame) {
    for (auto &monsterRender : m_monsterRenderers) {
      monsterRender->render(window, sprites, key, nbFrame);
    }
  }

  /**
   * @brief Updates the state of all monsters.
  */
  void update() {
    monsterList temp = m_monsters;
    while (!is_empty(temp)) {
      head(temp)->update();
      temp = rest(temp);
    }
  }
  
  // Linked List
  /**
   * @brief Creates an empty monster list.
   *
   * @return An empty monster list.
   */
  monsterList cons_empty(){
    return nullptr;
  }

  /**
   * @brief Adds a monster to the monster list.
   *
   * @param m Pointer to the monster to be added.
   * @param M The existing monster list.
   * @return Updated monster list with the new monster.
   */
  monsterList addMonster(Monster *m, monsterList M){
    monsterList monster;

    monster = (monsterList)malloc(sizeof(Monster*));
    monster->m = m;
    monster->suivant = M;

    return monster;
  }

  /**
   * @brief Checks if the monster list is empty.
   *
   * @param M The monster list to check.
   * @return True if the list is empty, false otherwise.
   */
  bool is_empty (monsterList M){
    return M == nullptr;
  }

  /**
   * @brief Retrieves the first monster in the list.
   *
   * @param M The monster list.
   * @return The first monster in the list.
   */
  Monster* head(monsterList M){
    if(is_empty(M)){
      printf ("The list is empty: head\n");
      exit (0);
    }
    return M->m;
  }

  /**
   * @brief Retrieves the rest of the monster list excluding the first element.
   *
   * @param M The monster list.
   * @return The monster list excluding the first element.
   */
  monsterList rest(monsterList M){
    return M->suivant;
  }

  /**
   * @brief Frees the memory allocated for the monster list.
   *
   * @param M The monster list to be freed.
   */
  void free_monsterList (monsterList M){
    if (!is_empty(M)){
      free_monsterList(rest(M)) ;
      free (M);
    }
  }
};

#endif