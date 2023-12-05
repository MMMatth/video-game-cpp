#ifndef DAY_NIGHT_CYCLE_HPP
#define DAY_NIGHT_CYCLE_HPP

#include "../utils/const.hpp"
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
  /**
   * @brief Default constructor for DayNightCycle.
   */
  DayNightCycle();
  /**
   * @brief Parameterized constructor for DayNightCycle.
   * @param time_day_in_sec Duration of a day in seconds.
   * @param imgPath Path to an image representing the sky colors.
   */
  DayNightCycle(int time_day_in_sec, string imgPath);
  /**
   * @brief Constructor for DayNightCycle loading data from a CSV file.
   * @param csvPath Path to a CSV file containing cycle information.
   * @param imgPath Path to an image representing the sky colors.
   */
  DayNightCycle(string csvPath, string imgPath);

  /* update */
  /* Update */
  /**
   * @brief Updates the day-night cycle's state and behavior.
   */
  void update();

  // void load
  /**
   * @brief Loads cycle information from a CSV file.
   * @param csvPath Path to the CSV file containing cycle information.
   * @return True if loading is successful, false otherwise.
   */
  bool loadFromCSV(string csvPath);
  /**
   * @brief Loads sky colors from an image file.
   * @param img_path Path to the image file representing sky colors.
   * @return True if loading is successful, false otherwise.
   */
  bool loadColorsFromImage(string img_path);

  /* getter */
  /**
   * @brief Gets the current sky color.
   * @return The Color representing the current sky color.
   */
  Color getColor();
  /**
   * @brief Checks if it's currently daytime.
   * @return True if it's daytime, false if it's nighttime.
   */
  bool isDay();
  /**
   * @brief Gets the current hour as a formatted string.
   * @return The current hour in the format "HH:MM".
   */
  string getHour();

  /* Other */
  void reset(bool save, int time_day_in_sec,
             string imgPath = string(DAY_NIGHT_CYCLE_IMG_PATH));

  void save(string csvPath);
  /**
   * @brief Clears the day-night cycle data.
   */
  void clear();
  /**
   * @brief Converts the day-night cycle data to a string representation.
   * @return A string representing the day-night cycle data.
   */
  string toString();
};

#endif /* DAY_NIGHT_CYCLE_HPP */