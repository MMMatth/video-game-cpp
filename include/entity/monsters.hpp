#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../item/block.hpp"
#include "../map/map.hpp"
#include "../rendering/entityRender.hpp"
#include "../rendering/monsterRender.hpp"
#include "../utils/list.hpp"
#include "character.hpp"
#include "flying_monster.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>

class Monsters {
private:
  vector<Monster *> m_monsters;               // Collection of monsters
  vector<MonsterRender *> m_monsterRenderers; // Renderers for the monsters
  Map m_map;                                  // Reference to the game map
  Character &m_char;                          // Character
  bool m_killAMonster = false;
  Clock m_clock;
  int m_numFlyingMonstersKilled, m_numWalkingMonstersKilled;

public:
  Monsters(Map &map, Character &m_char);

  ~Monsters();

  const vector<Monster *> &getMonsters() const { return m_monsters; }

  void addRandomMonster(Monster *monster, Map &map);

  void collide(Map *map, int camX, int camY);

  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              int nbFrame);

  void update();

  void renderLifes(RenderWindow &window, unordered_map<string, Sprite> sprites);

  bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
                      int width2, int height2) const;

  bool checkPlayerMonsterCollision(const Character &m_char,
                                   Monster *m_monster) const;

  void setKillAmonster(bool m_choice) { this->m_killAMonster = m_choice; }

  int getNumFlyingMonstersKilled() const { return m_numFlyingMonstersKilled; }

  int getNumWalkingMonstersKilled() const { return m_numWalkingMonstersKilled; }

  void setNumFlyingMonstersKilled(int number) {
    m_numFlyingMonstersKilled += number;
  }

  void setNumWalkingMonstersKilled(int number) {
    m_numWalkingMonstersKilled += number;
  }

  void createMonsters(Map &map, Character &m_char);

  bool lineOfSight(const Character &m_char, Monster *m_monster, float minDistance) const;

  bool checkCollisionWithDistance(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2, float minDistance) const; 
  
  void setLifeMonsters();
};

#endif