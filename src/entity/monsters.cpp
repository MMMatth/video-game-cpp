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
    : m_map(map), m_char(m_char), m_save(false), m_isDay(true) {
  m_monstersWithRender = vector<MonsterWithRender>();
  this->m_numFlyingMonstersKilled = this->m_numWalkingMonstersKilled = 0;
  this->m_numFlyingMonsters = this->m_numWalkingMonsters = 0;
}

Monsters::Monsters(string path, Map &map, Character &chara, bool save)
    : m_map(map), m_char(chara), m_save(save), m_isDay(true) {
  if (!initFromFile(path)) {
    cerr << "Error while loading monsters from file" << endl;
  }
}

Monsters::~Monsters() {
  for (MonsterWithRender monsterWithRender : m_monstersWithRender) {
    delete monsterWithRender.monster;
    delete monsterWithRender.monsterRender;
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
      if (type.compare("FLYING_MONSTER") == 0) {
        Monster *monster = new FlyingMonster(
            x, y, MONSTERS_WIDTH, MONSTERS_HEIGHT, speed, life, life);
        m_monstersWithRender.push_back({monster, new MonsterRender(*monster)});

      } else if (type.compare("WALKING_MONSTER") == 0) {
        Monster *monster =
            new WalkingMonster(x, y, MONSTERS_WIDTH, MONSTERS_HEIGHT, speed,
                               life, life, JUMP_HEIGHT);
        m_monstersWithRender.push_back({monster, new MonsterRender(*monster)});
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
  m_monstersWithRender.push_back({monster, new MonsterRender(*monster)});
}

void Monsters::collide(Map *map) {
  for (MonsterWithRender monsterWithRender : m_monstersWithRender) {
    map->collide(monsterWithRender.monster);
  }
}

void Monsters::render(RenderWindow &window,
                      std::unordered_map<std::string, Sprite> sprites,
                      int nbFrame) {
  for (MonsterWithRender monsterWithRender : m_monstersWithRender) {
    if (monsterWithRender.monster->getSpeed() == FLYING_MONSTERS_SPEED) {
      monsterWithRender.monsterRender->render(window, sprites, "FLYING_MONSTER",
                                              nbFrame);
    }
    if (monsterWithRender.monster->getSpeed() == WALKING_MONSTERS_SPEED) {
      monsterWithRender.monsterRender->render(window, sprites,
                                              "WALKING_MONSTER", nbFrame);
    }
  }
  renderLifes(window, sprites);
}

void Monsters::update(bool isDay) {

  if (!isDay && isDay != m_isDay) {
    m_isDay = isDay;
    NewWave();
  } else {
    m_isDay = isDay;
  }

  // if is day monsters dead
  if (isDay) {
    for (auto &monster : m_monstersWithRender) {
      monster.monster->reduceLife(1);
    }
  }

  for (auto &monster : m_monstersWithRender) {
    monster.monster->update(m_char);
  }

  // Check collision with player and monsters
  if (m_clock.getElapsedTime().asSeconds() > 1) {
    m_clock.restart();
    for (auto &monster : m_monstersWithRender)
      if (checkPlayerMonsterCollision(m_char, monster.monster)) {
        if (m_killAMonster) {
          monster.monster->reduceLife(1);
        }
        m_char.hit(1);
      }

    for (auto &monster : m_monsters) {
      map<string, bool> directionMonster = monster->getDirection();
      map<string, bool> directionChar = m_char.getDirection();
      if (checkPlayerMonsterCollision(m_char, monster)) {
        if (m_clock.getElapsedTime().asSeconds() > 1) {
          m_clock.restart();
          m_char.hit(1);
        }
      }
      if (lineOfSight(m_char, monster, LINEOFSIGHT)) {
        if (m_killAMonster &&
            (directionMonster["right"] && directionChar["left"] ||
             directionMonster["left"] && directionChar["right"])) {
          monster->reduceLife(1);
        }
      }
      if (monster->getLife() <= 0 &&
          monster->getSpeed() == FLYING_MONSTERS_SPEED) {
        setNumFlyingMonstersKilled(1);
      }
      if (monster->getLife() <= 0 &&
          monster->getSpeed() == WALKING_MONSTERS_SPEED) {
        setNumWalkingMonstersKilled(1);
      }
    }

    for (auto it = m_monstersWithRender.begin();
         it != m_monstersWithRender.end();) {
      if ((*it).monster->getLife() <= 0) {
        delete (*it).monster;
        delete (*it).monsterRender;
        it = m_monstersWithRender.erase(it);
      } else {
        ++it;
      }
    }
  }

  void Monsters::renderLifes(RenderWindow & window,
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
      for (MonsterWithRender monster : m_monstersWithRender) {
        file << monster.monster->getX() << ";" << monster.monster->getY() << ";"
             << monster.monster->getSpeed() << ";" << monster.monster->getLife()
             << ";" << monster.monster->getType() << "\n";
      }
      file.close();
      return true;
    }
    return false;
  }

  void Monsters::reset(bool save) {
    m_monstersWithRender.clear();
    m_save = save;
  }

  bool Monsters::checkCollisionWithDistance(
      int x1, int y1, int width1, int height1, int x2, int y2, int width2,
      int height2, float minDistance) const {
    // Calculate the center
    float centerX1 = x1 + width1 / 2;
    float centerY1 = y1 + height1 / 2;
    float centerX2 = x2 + width2 / 2;
    float centerY2 = y2 + height2 / 2;

    // Calculate the distance
    float deltaX = centerX2 - centerX1;
    float deltaY = centerY2 - centerY1;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    return distance < (width1 / 2 + width2 / 2 + minDistance);
  }

  bool Monsters::lineOfSight(const Character &m_char, Monster *m_monster,
                             float minDistance) const {
    return checkCollisionWithDistance(
        m_char.getX(), m_char.getY(), m_char.getWidth(), m_char.getHeight(),
        m_monster->getX(), m_monster->getY(), m_monster->getWidth(),
        m_monster->getHeight(), minDistance);
  }

  void Monsters::createMonsters(Map & map, Character & m_char) {
    for (int i = 0; i < NUM_MONSTERS_FLYING; i++) {
      setNumFlyingMonsters(1);
      addRandomMonster(new FlyingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                         FLYING_MONSTERS_SPEED, MAX_LIFE,
                                         MAX_LIFE),
                       map);
    }
    for (int i = 0; i < NUM_MONSTERS_WALKING; i++) {
      setNumWalkingMonsters(1);
      addRandomMonster(new WalkingMonster(0, 0, MONSTERS_WIDTH, MONSTERS_HEIGHT,
                                          WALKING_MONSTERS_SPEED, MAX_LIFE,
                                          MAX_LIFE, JUMP_HEIGHT),
                       map);
    }
  }

  void Monsters::setLifeMonsters() {
    for (auto &monster : m_monsters) {
      monster->setLife(0);
    }
  }