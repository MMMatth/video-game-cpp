#include "../../include/entity/monsters.hpp"

Monsters::Monsters(const Map &map, const Character& m_char) : m_map(map), m_char(m_char){

  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT, FLYING_MONSTERS_SPEED, MAX_LIFE), map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT, WALKING_MONSTERS_SPEED, MAX_LIFE, JUMP_HEIGHT, map), map);
  }
}

void Monsters::addRandomMonster(Monster *monster, Map map) {
  

  do {
    int x = rand() % (MAP_WIDTH * TILE_SIZE);
    int y = rand() % (MAP_WIDTH * 2);
    monster->setX(x);
    monster->setY(y);
  } while (map.collidesWithSolidBlock(monster));
  if(monster->getSpeed() == 3){
    m_flyingMonsters = addLink<Monster *>(monster, m_flyingMonsters);
    m_flyingMonsterRenderers = addLink(new EntityRender(*monster), m_flyingMonsterRenderers);
  }
  if (monster->getSpeed() == 2) {
    m_walkingMonsters = addLink<Monster *>(monster, m_walkingMonsters);
    m_walkingMonsterRenderers = addLink(new EntityRender(*monster), m_walkingMonsterRenderers);
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

void Monsters::render(RenderWindow &window, unordered_map<string, Sprite> sprites, string key, int nbFrame) {
  if (key == "FLYING_MONSTER") {
    LinkedList<EntityRender *> *tempRenderer = m_flyingMonsterRenderers;
    while (!isEmpty<EntityRender *>(tempRenderer)) {
      head<EntityRender *>(tempRenderer)->render(window, sprites, key, nbFrame);
      tempRenderer = rest<EntityRender *>(tempRenderer);
    }
    renderMonstersHealthBars(window, m_flyingMonsters);
  }
  
  if (key == "WALKING_MONSTER") {
    LinkedList<EntityRender *> *tempRenderer = m_walkingMonsterRenderers;
    while (!isEmpty<EntityRender *>(tempRenderer)) {
      head<EntityRender *>(tempRenderer)->render(window, sprites, key, nbFrame);
      tempRenderer = rest<EntityRender *>(tempRenderer);
    }
    renderMonstersHealthBars(window, m_walkingMonsters);
  }
}

void Monsters::update() {
  LinkedList<Monster *> *temp = m_flyingMonsters;
  LinkedList<EntityRender *> *tempRenderer = m_flyingMonsterRenderers;
  while (!isEmpty<Monster *>(temp)) {
    // Check if there is a collision between monster and player and decrease the health of the monster
    if(checkPlayerMonsterCollision(m_char, head<Monster *>(temp))){
      head<Monster *>(temp)->reduceLife(1);
    }
    if (head<Monster *>(temp)->getLife() <= 0) {
      // Remove the dead monster from the list
      m_flyingMonsters = removeLink(head<Monster *>(temp), m_flyingMonsters);
      m_flyingMonsterRenderers = removeLink(head<EntityRender *>(tempRenderer), m_flyingMonsterRenderers);
      
      delete head<EntityRender *>(tempRenderer);  // free the memory
    } else {
      tempRenderer = rest<EntityRender *>(tempRenderer);
    }

    head<Monster *>(temp)->update();
    temp = rest<Monster *>(temp);
  }

  LinkedList<Monster *> *temp1 = m_walkingMonsters;
  LinkedList<EntityRender *> *tempRendere1 = m_walkingMonsterRenderers;
  while (!isEmpty<Monster *>(temp1)) {
    // Check if there is a collision between monster and player and decrease the health of the monster
    if(checkPlayerMonsterCollision(m_char, head<Monster *>(temp1))){
      head<Monster *>(temp1)->reduceLife(1);
    }
    if (head<Monster *>(temp1)->getLife() <= 0) {
      // Remove the dead monster from the list
      m_walkingMonsters = removeLink(head<Monster *>(temp1), m_walkingMonsters);
      m_walkingMonsterRenderers = removeLink(head<EntityRender *>(tempRendere1), m_walkingMonsterRenderers);
      
      delete head<EntityRender *>(tempRendere1);  // free the memory
    } else {
      tempRendere1 = rest<EntityRender *>(tempRendere1);
    }

    head<Monster *>(temp1)->update();
    temp1 = rest<Monster *>(temp1);
  }
}

void Monsters::renderMonstersHealthBars(RenderWindow &window, LinkedList<Monster *> *monsters) {
  LinkedList<Monster *> *temp = monsters;
  int i = 0;
  while (!isEmpty<Monster *>(temp)) {
    Monster *currentMonster = head<Monster *>(temp);
    renderHealthBar(window, currentMonster->getLife(), MAX_LIFE, currentMonster->getX(), currentMonster->getY());
    temp = rest<Monster *>(temp);
  }
}

bool Monsters::checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) const {
  return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

bool Monsters::checkPlayerMonsterCollision(const Character& m_char, Monster *m_monster) const {
  if (checkCollision(m_char.getX(), m_char.getY(), m_char.getWidth(), m_char.getHeight(), m_monster->getX(), m_monster->getY(), m_monster->getWidth(), m_monster->getHeight())) {
    return true; // Collision detected
  }
  return false; 
}

