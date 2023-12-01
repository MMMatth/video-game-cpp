#include "../../include/entity/monsters.hpp"

Monsters::Monsters(const Map &map) : m_map(map) {

  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, 30, 50, 3, 100), map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, 30, 50, 2, 100, 18, map), map);
  }
}

void Monsters::addRandomMonster(Monster *monster, Map map) {
  int monsterWidth = monster->getWidth();
  int monsterHeight = monster->getHeight();

  do {
    int x = rand() % (MAP_WIDTH * TILE_SIZE);
    int y = rand() % (MAP_WIDTH * 2);
    monster->setX(x);
    monster->setY(y);
  } while (map.collidesWithSolidBlock(monster));
  if(monster->getSpeed() == 3){
    m_flyingMonsters = addLink<Monster *>(monster, m_flyingMonsters);
    m_flyingMonsterRenderers.push_back(new EntityRender(*monster));
  }
  if(monster->getSpeed() == 2){
    m_walkingMonsters = addLink<Monster *>(monster, m_walkingMonsters);
    m_walkingMonsterRenderers.push_back(new EntityRender(*monster));
  }
  
  
}

void Monsters::collide(Map *map, int camX, int camY) {
  LinkedList<Monster *> *temp = m_flyingMonsters;
  while (!isEmpty<Monster *>(temp)) {
    map->collide(head<Monster *>(temp), camX, camY);
    map->collide(head<Monster *>(temp));
    temp = rest<Monster *>(temp);
  }
  LinkedList<Monster *> *temp1 = m_walkingMonsters;
  while (!isEmpty<Monster *>(temp1)) {
    map->collide(head<Monster *>(temp1), camX, camY);
    map->collide(head<Monster *>(temp1));
    temp1 = rest<Monster *>(temp1);
  }
}

void Monsters::render(RenderWindow &window,
                      unordered_map<string, Sprite> sprites, string key,
                      int nbFrame) {
  if (key == "FLYING_MONSTER") {
    for (auto &monsterRender : m_flyingMonsterRenderers) {
      monsterRender->render(window, sprites, key, nbFrame);
    }
     renderMonstersHealthBars(window, m_flyingMonsters);
  }
 
  if (key == "WALKING_MONSTER") {
    for (auto &monsterRender : m_walkingMonsterRenderers) {
      monsterRender->render(window, sprites, key, nbFrame);
    }
    renderMonstersHealthBars(window, m_walkingMonsters);
  }
}


void Monsters::update() {
  LinkedList<Monster *> *temp = m_flyingMonsters;
  while (!isEmpty<Monster *>(temp)) {
    head<Monster *>(temp)->update();
    temp = rest<Monster *>(temp);
  }

  LinkedList<Monster *> *temp1 = m_walkingMonsters;
  while (!isEmpty<Monster *>(temp1)) {
    head<Monster *>(temp1)->update();
    temp1 = rest<Monster *>(temp1);
  }
}

void Monsters::renderMonstersHealthBars(RenderWindow &window, LinkedList<Monster *> *monsters) {
    LinkedList<Monster *> *temp = monsters;
    int i = 0;
    while (!isEmpty<Monster *>(temp)) {
        Monster *currentMonster = head<Monster *>(temp);
        renderHealthBar(window, currentMonster->getLife(), 100, currentMonster->getX(), currentMonster->getY());
        temp = rest<Monster *>(temp);
    }
}