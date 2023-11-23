#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../map/map.hpp"
#include "../rendering/entityRender.hpp"
#include "flying_monster.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>

class Monsters {
private:
  vector<Monster *> m_monsters;
  vector<EntityRender *> m_monsterRenderers;

public:
  Monsters() : m_monsters() {
    addMonster(new FlyingMonster(100, 100, 50, 50, 5, 5));
    addMonster(new WalkingMonster(200, 200, 50, 50, 5, 5, 10));
  }

  /* Getters */
  vector<Monster *> getMonsters() const { return m_monsters; }

  /* Setters */
  void addMonster(Monster *monster) {
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