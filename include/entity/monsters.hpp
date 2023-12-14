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

struct MonsterWithRender {
  Monster *monster;
  MonsterRender *monsterRender;
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

  void addRandomMonster(Monster *monster, Map &map);

  void collide(Map *map);

  void render(RenderWindow &window, unordered_map<string, Sprite> sprites,
              int nbFrame);

  void update(bool isDay);

  /** @brief function who save monsters in csv file
   * @param path the path of the file
   * @return true if the file is save
   */
  bool save(string path);

  /** @brief function who reset monsters */
  void reset(bool save);

  void renderLifes(RenderWindow &window, unordered_map<string, Sprite> sprites);

  bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2,
                      int width2, int height2) const;

  bool checkPlayerMonsterCollision(const Character &m_char,
                                   Monster *m_monster) const;

  void setKillAmonster(bool m_choice) { this->m_killAMonster = m_choice; }
};

#endif