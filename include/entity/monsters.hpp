#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../map/map.hpp"
#include "../item/block.hpp"
#include "../rendering/entityRender.hpp"
#include "flying_monster.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>

class Monsters {
private:
  vector<Monster *> m_monsters;
  vector<EntityRender *> m_monsterRenderers;
  const Map m_map;

public:
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

  /* Getters */
  vector<Monster *> getMonsters() const { return m_monsters; }

  /* Setters */
  void addMonster(Monster *monster) {
    m_monsters.push_back(monster);
    m_monsterRenderers.push_back(new EntityRender(*monster));
  }

void addRandomMonster(Monster *monster, Map map) {
  int monsterWidth = monster->getWidth();
  int monsterHeight = monster->getHeight();

  do {
    int x = rand() % WINDOW_WIDTH;
    int y = rand() % WINDOW_HEIGHT;
    monster->setX(x);
    monster->setY(y);
  } while (map.collidesWithSolidBlock(monster));

  m_monsters.push_back(monster);
  m_monsterRenderers.push_back(new EntityRender(*monster));
}

void collide(Map *map, int camX, int camY) {
  for (auto &monster : m_monsters) {
    map->collide(monster, camX, camY);
     map->collide(monster);
  }
}

  /* Other */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              string key, int nbFrame) {
    for (auto &monsterRender : m_monsterRenderers) {
      monsterRender->render(window, sprites, key, nbFrame);
    }
  }

  void update() {
    for (auto &monster : m_monsters) {
      monster->update();
    }
  }
};

#endif