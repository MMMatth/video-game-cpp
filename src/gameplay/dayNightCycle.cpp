#include "../../include/gameplay/dayNightCycle.hpp"

/* constructor */

DayNightCycle::DayNightCycle()
    : m_time_day_in_sec(240), m_color(), m_clock(), m_clock_in_sec(0),
      m_clock_offset(0), m_save(false) {
  m_color.push_back(DEFAULT_SKY_COLOR);
}

DayNightCycle::DayNightCycle(int time_day_in_sec, string imgPath)
    : m_color(), m_clock(), m_clock_in_sec(0), m_clock_offset(0),
      m_time_day_in_sec(time_day_in_sec), m_save(false) {
  if (!loadColorsFromImage(imgPath)) {
    cerr << "Failed to load image from " << imgPath << endl;
    m_color.push_back(DEFAULT_SKY_COLOR);
  }
}

DayNightCycle::DayNightCycle(string csvPath, string imgPath)
    : m_color(), m_clock(), m_clock_in_sec(0), m_clock_offset(0), m_save(true) {
  if (!loadFromCSV(csvPath)) {
    cerr << "Failed to load csv from " << csvPath << endl;
    m_time_day_in_sec = 240;
    m_clock_offset = 0;
  };
  if (!loadColorsFromImage(imgPath)) {
    cerr << "Failed to load image from " << imgPath << endl;
    m_color.push_back(DEFAULT_SKY_COLOR);
  };
}

bool DayNightCycle::loadFromCSV(string csvPath) {
  ifstream file;
  file.open(csvPath);
  if (file.is_open()) {
    string line;
    getline(file, line); /* header */
    while (getline(file, line)) {
      istringstream iss(line);
      string time_in_day, clock_offset;
      getline(iss, time_in_day, ';');
      getline(iss, clock_offset, ';');
      m_time_day_in_sec = stoi(time_in_day);
      m_clock_offset = stoi(clock_offset);
    }
  } else {
    cerr << "Load Character unable to open file " << csvPath << "\n";
    return false;
  }
  file.close();
  return true;
}

bool DayNightCycle::loadColorsFromImage(string img_path) {
  Image img;
  if (!img.loadFromFile(img_path)) {
    cerr << "Failed to load image from " << img_path << endl;
    m_color.push_back(DEFAULT_SKY_COLOR); // error color
    return false;
  }
  m_color.reserve(img.getSize().x);
  // we browse the first line of the image to get the colors
  for (unsigned int i = 0; i < img.getSize().x; i++) {
    m_color.emplace_back(img.getPixel(i, 0));
  }
  return true;
}

/* update */
void DayNightCycle::update() {
  m_clock_in_sec = m_clock.getElapsedTime().asSeconds() + m_clock_offset;
}

/* getters */

Color DayNightCycle::getColor() {
  /* we use fmod because m_clock in sec is a float */
  int clock = fmod(m_clock_in_sec, m_time_day_in_sec);
  int index = (clock * m_color.size()) / m_time_day_in_sec;
  return m_color[index];
}

bool DayNightCycle::isDay() {
  /* we supose the night is in the midle of the img */
  int clock = fmod(m_clock_in_sec, m_time_day_in_sec);
  return !(clock > m_time_day_in_sec * 0.25 &&
           clock < m_time_day_in_sec * 0.75);
}

string DayNightCycle::getHour() {
  /* we use fmod because m_clock in sec is a float */
  int clock = fmod(m_clock_in_sec, m_time_day_in_sec);
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

void DayNightCycle::reset(bool save, int time_day_in_sec, string imgPath) {
  m_save = save;
  m_time_day_in_sec = time_day_in_sec;
  m_clock.restart();
  m_clock_offset = 0;
  m_color.clear();
  if (!loadColorsFromImage(imgPath)) {
    cerr << "Failed to load image from " << imgPath << endl;
    m_color.push_back(DEFAULT_SKY_COLOR);
  }
}

void DayNightCycle::save(string csvPath) {
  if (m_save) {
    ofstream file;
    file.open(csvPath);
    if (file.is_open()) {
      file << "time_day_in_sec;clock_offset\n"; /* header */
      file << m_time_day_in_sec << ";" << m_clock_in_sec << "\n";
    } else {
      cerr << "Save Character unable to open file " << csvPath << "\n";
    }
    file.close();
  }
}

string DayNightCycle::toString() {
  stringstream ss;
  for (const auto &color : m_color) {
    ss << color.r << " " << color.g << " " << color.b << "\n";
  }
  return ss.str();
}
