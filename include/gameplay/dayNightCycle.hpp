#ifndef DAY_NIGHT_CYCLE_HPP
#define DAY_NIGHT_CYCLE_HPP

#include "../utils/const.hpp"
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

/** @brief class of the day night cycle */
class DayNightCycle {
private:
  bool m_save;           /** true -> save the data in a csv file*/
  vector<Color> m_color; /** vector of color*/
  int m_time_day_in_sec; /** time of a day in sec */
  Clock m_clock;         /**  clock*/
  int m_clock_in_sec;    /** time in sec */
  int m_clock_offset;    /** time already pass */

public:
  /** @brief Default constructor for DayNightCycle. */
  DayNightCycle();

  /** @brief Constructor with param
   * @param imgPath Path to an image representing the sky colors.
   */
  DayNightCycle(int time_day_in_sec, string imgPath);

  /** @brief Constructor for DayNightCycle loading data from a CSV file.
   * @param csvPath Path to a CSV file containing cycle information.
   * @param imgPath Path to an image representing the sky colors.
   */
  DayNightCycle(string csvPath, string imgPath);

  /** @brief destructor */
  ~DayNightCycle();

  /** @brief Loads cycle information from a CSV file.
   * @param csvPath Path to the CSV file containing cycle information.
   * @return True if loading is successful, false otherwise.
   */
  bool loadFromCSV(string csvPath);

  /** @brief Loads sky colors from an image.
   * @param imgPath an image representing the sky colors (1 * width)
   */
  bool loadColorsFromImage(string img_path);

  /** @brief update function */
  void update();

  /* getter */
  Color getCurrentColor();
  bool isDay();
  string getHour();

  /** function who reset the day night cycle*/
  void reset(bool save, string imgPath = string(DAY_NIGHT_CYCLE_IMG_PATH));

  /** @brief function who save the time in a day and the actual time passed*/
  void save(string csvPath);
};

#endif /* DAY_NIGHT_CYCLE_HPP */