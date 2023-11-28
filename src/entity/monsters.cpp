#include "../../include/entity/monsters.hpp"

Monsters::Monsters(const Map &map) : m_monsters(), m_map(map) {

  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, 30, 50, 3, 5), map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, 30, 50, 2, 5, 18), map);
  }
}

void Monsters::addRandomMonster(Monster *monster, Map map) {
  int monsterWidth = monster->getWidth();
  int monsterHeight = monster->getHeight();

  do {
    int x = rand() % WINDOW_WIDTH;
    int y = rand() % WINDOW_HEIGHT;
    monster->setX(x);
    monster->setY(y);
  } while (map.collidesWithSolidBlock(monster));

  m_monsters = addLink<Monster *>(monster, m_monsters);
  m_monsterRenderers.push_back(new EntityRender(*monster));
}

void Monsters::collide(Map *map, int camX, int camY) {
  LinkedList<Monster *> *temp = m_monsters;
  while (!isEmpty<Monster *>(temp)) {
    map->collide(head<Monster *>(temp), camX, camY);
    map->collide(head<Monster *>(temp));
    temp = rest<Monster *>(temp);
  }
}

void Monsters::render(RenderWindow &window,
                      unordered_map<string, Sprite> sprites, string key,
                      int nbFrame) {
  for (auto &monsterRender : m_monsterRenderers) {
    monsterRender->render(window, sprites, key, nbFrame);
  }
}

void Monsters::update() {
  LinkedList<Monster *> *temp = m_monsters;
  while (!isEmpty<Monster *>(temp)) {
    head<Monster *>(temp)->update();
    temp = rest<Monster *>(temp);
  }
}