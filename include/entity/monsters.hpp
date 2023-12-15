#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "../item/block.hpp"
#include "../item/weapon.hpp"
#include "../map/map.hpp"
#include "../rendering/entityRender.hpp"
#include "../rendering/monsterRender.hpp"
#include "../utils/list.hpp"

#include "character.hpp"
#include "flying_monster.hpp"
#include "monster.hpp"
#include "walking_monster.hpp"
#include <vector>

struct MonsterWithRender {
  Monster *entity;
  MonsterRender *render;
};

class Monsters {
private:
  vector<MonsterWithRender>
      m_monstersWithRender; /**< vector with monster and the render monster */
  Map m_map;                /**< map */
  Character &m_char;        // Character
  bool m_killAMonster = false;
  Clock m_clock;
  bool m_save;
  bool m_isDay;

  int m_numFlyingMonsters, m_numWalkingMonsters;
  int m_numFlyingMonstersKilled, m_numWalkingMonstersKilled;

public:
  /** @brief function who add other monster*/
  void NewWave();

  Monsters(Map &map, Character &m_char);

  /** @brief constructor who use csvFile */
  Monsters(string path, Map &map, Character &chara, bool save);

  /** @brief destructor */
  ~Monsters();

  /** @brief function who init monsters from file
   * @param path the path of the file
   * @return true if the file is open
   */
  bool initFromFile(string path);

  const vector<MonsterWithRender> &getMonsters() const {
    return m_monstersWithRender;
  }

  int getNumFlyingMonstersKilled() const { return m_numFlyingMonstersKilled; }

  int getNumWalkingMonstersKilled() const { return m_numWalkingMonstersKilled; }

  int getNumFlyingMonsters() const { return m_numFlyingMonsters; }

  int getNumWalkingMonsters() const { return m_numWalkingMonsters; }

  /*Setters*/
  void setKillAmonster(bool m_choice) { this->m_killAMonster = m_choice; }

  void setNumFlyingMonstersKilled(int number) {
    m_numFlyingMonstersKilled += number;
  }
  void setNumWalkingMonstersKilled(int number) {
    m_numWalkingMonstersKilled += number;
  }
  void setNumFlyingMonsters(int number) { m_numFlyingMonsters += number; }

  void setNumWalkingMonsters(int number) { m_numWalkingMonsters += number; }

  void setLifeMonsters();

  /*others*/
  void addRandomMonster(Monster *monster, Map &map);

  void collide(Map *map);

  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              int nbFrame);

  void handleEvent(Event &event, Weapon item, int xOffset, int yOffset);

  void update(bool isDay);

  /** @brief function who save monsters in csv file
   * @param path the path of the file
   * @return true if the file is save
   */
  bool save(string path);

  /** @brief function who reset monsters */
  void reset(bool save);

  void createMonsters(Map &map, Character &m_char);

  void renderLifes(RenderWindow &window, unordered_map<string, Sprite> sprites);

  bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
                      int width2, int height2) const;

  bool checkPlayerMonsterCollision(const Character &m_char,
                                   Monster *m_monster) const;

  bool isWithinDistanceChar(const Character &m_char, Monster *m_monster,
                            float minDistance) const;

  bool isWithinDistance(int x1, int y1, int width1, int height1, int x2, int y2,
                        int width2, int height2, float minDistance) const;
};

#endif