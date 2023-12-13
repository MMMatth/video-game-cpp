#include "../../include/entity/monsters.hpp"
#include <chrono>
#include <thread>

Monsters::Monsters(Map &map, Character &m_char) : m_map(map), m_char(m_char) {

  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                       FLYING_MONSTERS_SPEED, MAX_LIFE,
                                       MAX_LIFE),
                     map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                        WALKING_MONSTERS_SPEED, MAX_LIFE,
                                        MAX_LIFE, JUMP_HEIGHT),
                     map);
  }
}

Monsters::~Monsters() {
  for (MonsterRender *renderer : m_monsterRenderers) {
    delete renderer;
  }
  for (Monster *monster : m_monsters) {
    delete monster;
  }
}

void Monsters::addRandomMonster(Monster *monster, Map &map) {
  do {
    int x = rand() % (MAP_WIDTH * TILE_SIZE);
    int y = rand() % (MAP_WIDTH * 2);
    monster->setX(x);
    monster->setY(y);
  } while (map.isCollide(monster));
  m_monsters.push_back(monster);
  m_monsterRenderers.push_back(new MonsterRender(*monster));
}

void Monsters::collide(Map *map) {
  for (Monster *monster : m_monsters) {
    map->collide(monster);
  }
}

void Monsters::render(RenderWindow &window,
                      std::unordered_map<std::string, Sprite> sprites,
                      int nbFrame) {
  for (EntityRender *renderer : m_monsterRenderers) {
    if (renderer->getEntity().getSpeed() == FLYING_MONSTERS_SPEED) {
      renderer->render(window, sprites, "FLYING_MONSTER", nbFrame);
    }
    if (renderer->getEntity().getSpeed() == WALKING_MONSTERS_SPEED) {
      renderer->render(window, sprites, "WALKING_MONSTER", nbFrame);
    }
  }
  renderLifes(window, sprites);
}

void Monsters::update() {

  for (auto &monster : m_monsters) {
    monster->update(m_char);
  }
  if (m_clock.getElapsedTime().asSeconds() > 1) {
    m_clock.restart();
    for (auto &monster : m_monsters)
      if (checkPlayerMonsterCollision(m_char, monster)) {
        if (m_killAMonster) {
          monster->reduceLife(1);
        }
        m_char.hit(1);
      }
  }

  // Remove dead monsters
  m_monsters.erase(std::remove_if(m_monsters.begin(), m_monsters.end(),
                                  [](const auto &monster) {
                                    return monster->getLife() <= 0;
                                  }),
                   m_monsters.end());

  // Remove corresponding renderers
  m_monsterRenderers.erase(
      std::remove_if(m_monsterRenderers.begin(), m_monsterRenderers.end(),
                     [](const auto &renderer) {
                       return renderer->getEntity().getLife() <= 0;
                     }),
      m_monsterRenderers.end());
}

void Monsters::renderLifes(RenderWindow &window,
                           unordered_map<string, Sprite> sprites) {
  for (MonsterRender *m_monsterRenderers : m_monsterRenderers) {
    m_monsterRenderers->renderLife(window, sprites);
  }
}

bool Monsters::checkCollision(int x1, int y1, int width1, int height1, int x2,
                              int y2, int width2, int height2) const {
  return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 &&
          y1 + height1 > y2);
}

bool Monsters::checkPlayerMonsterCollision(const Character &m_char,
                                           Monster *m_monster) const {
  return (checkCollision(m_char.getX(), m_char.getY(), m_char.getWidth(),
                         m_char.getHeight(), m_monster->getX(),
                         m_monster->getY(), m_monster->getWidth(),
                         m_monster->getHeight()));
}