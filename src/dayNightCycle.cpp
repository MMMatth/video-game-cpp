#include "../include/dayNightCycle.hpp"

/* constructor */

DayNightCycle::DayNightCycle(int time_day_in_sec) {
  m_time_day_in_sec = time_day_in_sec;
  loadColorsFromImage("../assets/img/day_night_cycle.png");
}

void DayNightCycle::loadColorsFromImage(string img_path) {
  Image img;
  if (!img.loadFromFile(img_path)) {
    cerr << "Failed to load image from " << img_path << endl;
    m_color.push_back(Color::Magenta); // error color
    return;
  }
  m_color.reserve(img.getSize().x);
  // we browse the first line of the image to get the colors
  for (unsigned int i = 0; i < img.getSize().x; i++) {
    m_color.emplace_back(img.getPixel(i, 0));
  }
}
/* getters */

Color DayNightCycle::getColor(int clock_in_sec) {
  int clock = clock_in_sec % m_time_day_in_sec;
  int index = (clock * m_color.size()) / m_time_day_in_sec;
  return m_color[index];
}

bool DayNightCycle::isDay(int clock_in_sec) {
  int clock = clock_in_sec % m_time_day_in_sec;
  return !(clock > m_time_day_in_sec * 0.25 &&
           clock < m_time_day_in_sec * 0.75);
}

string DayNightCycle::getHour(int clock_in_sec) {
  int clock = clock_in_sec % m_time_day_in_sec;
  int second_in_normal_day = 24 * 60 * 60;
  float one_hour_time = m_time_day_in_sec / 24.0;
  float one_min_time = one_hour_time / 60.0;
  float one_sec_time = one_min_time / 60.0;

  int hours = fmod((clock / one_hour_time + 12), 24);
  int minutes = fmod(clock, one_hour_time) / one_min_time;

  ostringstream timeStream;
  timeStream << setw(2) << setfill('0') << hours << ":" << setw(2)
             << setfill('0') << minutes;

  return timeStream.str();
}
/* other */

void DayNightCycle::clear() { m_color.clear(); }

string DayNightCycle::toString() {
  stringstream ss;
  for (const auto &color : m_color) {
    ss << color.r << " " << color.g << " " << color.b << "\n";
  }
  return ss.str();
}
