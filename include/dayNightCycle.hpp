#ifndef DAY_NIGHT_CYCLE_HPP
#define DAY_NIGHT_CYCLE_HPP

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
  vector<Color> m_color;
  int m_time_day_in_sec;

public:
  /* constructor */
  DayNightCycle(int time_day_in_sec);
  void loadColorsFromImage(string img_path);
  /* getter */
  Color getColor(int clock_in_sec);
  bool isDay(int clock_in_sec);
  string getHour(int clock_in_sec);
  /* other */
  void clear();
  string toString();
};

#endif /* DAY_NIGHT_CYCLE_HPP */