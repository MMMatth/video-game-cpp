#include "../../include/entity/monsters.hpp"
#include <chrono>
#include <thread>

void Monsters::NewWave() {
  srand(time(NULL));

  for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
    addRandomMonster(new FlyingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                       FLYING_MONSTERS_SPEED, MAX_LIFE,
                                       MAX_LIFE),
                     m_map);
  }

  for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
    addRandomMonster(new WalkingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                        WALKING_MONSTERS_SPEED, MAX_LIFE,
                                        MAX_LIFE, JUMP_HEIGHT),
                     m_map);
  }
}

Monsters::Monsters(Map &map, Character &m_char)
    : m_map(map), m_char(m_char), m_save(false) {
  NewWave();
}

Monsters::Monsters(string path, Map &map, Character &chara, bool save)
    : m_map(map), m_char(chara), m_save(save) {
  if (!initFromFile(path)) {
    cerr << "Error while loading monsters from file" << endl;
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

bool Monsters::initFromFile(string path) {
  ifstream file(path);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << path << "\n";
    return false;
  }
  string line;
  int row = 0;
  while (getline(file, line)) {
    if (row != 0) { // Skip header row
      istringstream ss(line);
      string cell, type;
      int x, y, speed, life;
      int column = 0;
      while (getline(ss, cell, ';')) {
        switch (column) {
        case 0:
          x = stoi(cell); // Convert string to int
          break;
        case 1:
          y = stoi(cell);
          break;
        case 2:
          speed = stoi(cell);
          break;
        case 3:
          life = stoi(cell);
          break;
        case 4:
          type = cell;
          break;
        default: // Invalid csv file
          cerr << "Monsters: invalide csv file\n";
          return false;
          break;
        }
        column++;
      }
      if (type == "FLYING_MONSTER") {
        addRandomMonster(new FlyingMonster(x, y, MONSTERS_WIDTH,
                                           MONSTERS_HEIGHT, speed, life, life),
                         m_map);
      } else if (type == "WALKING_MONSTER") {
        addRandomMonster(new WalkingMonster(x, y, MONSTERS_WIDTH,
                                            MONSTERS_HEIGHT, speed, life, life,
                                            JUMP_HEIGHT),
                         m_map);
      } else {
        cerr << "Monsters: invalide type\n";
        return false;
      }
    }
    row++;
  }
  file.close();
  return true;
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
  m_monsters.erase(
      remove_if(m_monsters.begin(), m_monsters.end(),
                [](const auto &monster) { return monster->getLife() <= 0; }),
      m_monsters.end());

  // Remove corresponding renderers
  m_monsterRenderers.erase(
      remove_if(m_monsterRenderers.begin(), m_monsterRenderers.end(),
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

bool Monsters::save(string path) {
  if (m_save) {
    ofstream file(path);
    if (!file.is_open()) {
      cerr << "Unable to open file: " << path << "\n";
      return false;
    }
    file << "x;y;speed;life;type\n";
    for (Monster *monster : m_monsters) {
      file << monster->getX() << ";" << monster->getY() << ";"
           << monster->getSpeed() << ";" << monster->getLife() << ";"
           << monster->getType() << "\n";
    }
    file.close();
    return true;
  }
  return false;
}

void Monsters::reset(bool save) {
  m_monsters.clear();
  m_monsterRenderers.clear();
  m_save = save;
  NewWave();
}