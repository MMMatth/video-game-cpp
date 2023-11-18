#ifndef DAY_NIGHT_CYCLE_HPP
#define DAY_NIGHT_CYCLE_HPP

#include "const.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

/** class who work with a image 1 * width and in this image every pyxel is a sky
 * color*/
class DayNightCycle {
private:
  bool m_save;
  vector<Color> m_color; /** vector of color*/
  int m_time_day_in_sec; /** time of a day in sec */
  Clock m_clock;         /** sfml clock*/
  int m_clock_in_sec;    /** time in sec */
  int m_clock_offset;    /** time already pass */

public:
  /* constructor */
  DayNightCycle();
  DayNightCycle(int time_day_in_sec, string imgPath);
  DayNightCycle(string csvPath, string imgPath);
  /* update */
  void update();
  // void load
  bool loadFromCSV(string csvPath);
  bool loadColorsFromImage(string img_path);
  /* getter */
  Color getColor();
  bool isDay();
  string getHour();
  /* other */
  void save(string csvPath);
  void clear();
  string toString();
};

#endif /* DAY_NIGHT_CYCLE_HPP */