#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "../entity/entity.hpp"
#include "../map/map.hpp"
#include "../utils/const.hpp"
#include "../utils/coord.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;
using namespace std;

class Map;

/** @brief class of the character who herite from entity*/
class Character : public Entity {
public:
  /** @brief constructor whit the csv file
   * @param fileName the path of the csv file
   * @param save true -> the character is save in the csv file
   */
  Character(string fileName, bool save);
  /** @brief default constructor
   * @param save true -> the character is save in the csv file
   */
  Character(int x, int y, int life, int maxLife, int speed, int width,
            int height, int jumpHeight, int timeJump, bool save);

  /** @brief function who init the coord and the life with a csv File
   * @return true if the file is open
   */
  bool loadFromCSV(string csvPath);

  /** @brief function who init with default value*/
  void init();

  /** @brief update function (mainely movement) */
  void update();
  /** @brief colide with the map (in the map working area )*/
  void collide(Map *map);

  /* getters */
  int getTimeJump() const { return m_timeJump; }
  int getJumpHeight() const { return m_jumpHeight; }

  /* setters */
  void setTimeJump(int time) { m_timeJump = time; }

  /** @brief function who reset at default the character
   * @param save true -> the character is save in the csv file
   * @param path the path of the csv file
   */
  void reset(bool save,
             string path = string(SAVE_PATH) + string(CHAR_FILE_NAME));

  /** @brief function who save the character (csv format)*/
  void save(string path);

private:
  bool m_save;      /** if true the charcater is save in csv */
  int m_timeJump;   /** the time elapsed during the jump  */
  int m_jumpHeight; /** the limit of time jump */
};

#endif /* PERSONNAGE_HPP */
