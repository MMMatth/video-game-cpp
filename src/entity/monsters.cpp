#include "../../include/entity/monsters.hpp"

Monsters::Monsters(Map &map, const Character& m_char) : m_map(map), m_char(m_char){

  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT, FLYING_MONSTERS_SPEED, MAX_LIFE), map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT, WALKING_MONSTERS_SPEED, MAX_LIFE, JUMP_HEIGHT, map), map);
  }
}

void Monsters::addRandomMonster(Monster *monster, Map &map) {
  do {
    int x = rand() % (MAP_WIDTH * TILE_SIZE);
    int y = rand() % (MAP_WIDTH * 2);
    monster->setX(x);
    monster->setY(y);
  } while (map.collidesWithSolidBlock(monster));
  m_monsters.push_back(monster);
  m_monsterRenderers.push_back(new EntityRender(*monster));
}

void Monsters::collide(Map *map, int camX, int camY) {
  for (Monster *monster : m_monsters) {
    map->collide(monster, camX, camY);
    map->collide(monster);
  }
}

void Monsters::render(RenderWindow &window, std::unordered_map<std::string, Sprite> sprites, int nbFrame) {
  for (EntityRender *renderer : m_monsterRenderers) {
    if(renderer->getEntity().getSpeed() == FLYING_MONSTERS_SPEED){renderer->render(window, sprites, "FLYING_MONSTER", nbFrame);}
    if(renderer->getEntity().getSpeed() == WALKING_MONSTERS_SPEED){renderer->render(window, sprites, "WALKING_MONSTER", nbFrame);}
  }
  renderMonstersHealthBars(window);
}

void Monsters::update() {
  auto itMonster = m_monsters.begin();
  auto itRenderer = m_monsterRenderers.begin();

  while (itMonster != m_monsters.end()) {
    // Check if there is a collision between monster and player
    if (checkPlayerMonsterCollision(m_char, *itMonster)) {
      (*itMonster)->reduceLife(1);
    }

    if ((*itMonster)->getLife() <= 0) {
      // Remove the dead monster from the list
      itMonster = m_monsters.erase(itMonster);
      delete *itRenderer;  // free the memory
      itRenderer = m_monsterRenderers.erase(itRenderer);
    } else {
      (*itMonster)->update(m_char);
      ++itMonster;
      ++itRenderer;
    }
  }
}

void Monsters::renderMonstersHealthBars(RenderWindow &window) {
  for (Monster *monster : m_monsters) {
    renderHealthBar(window, monster->getLife(), MAX_LIFE, monster->getX(), monster->getY());
  }
}

bool Monsters::checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) const {
  return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

bool Monsters::checkPlayerMonsterCollision(const Character& m_char, Monster *m_monster) const {
  return (checkCollision(m_char.getX(), m_char.getY(), m_char.getWidth(), m_char.getHeight(), m_monster->getX(), m_monster->getY(), m_monster->getWidth(), m_monster->getHeight()));

}