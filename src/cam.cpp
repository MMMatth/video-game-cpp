#include "../include/cam.hpp"

Cam::Cam() : m_save(false), m_pos() {}
Cam::Cam(int x, int y) : m_save(false), m_pos(x, y) {}
Cam::Cam(string csvPath) : m_save(true), m_pos() {
  if (!loadFromCSV(csvPath)) {
    cerr << "Failed to load csv from " << csvPath << "so cam is empty" << endl;
  };
}

bool Cam::loadFromCSV(string csvPath) {
  ifstream file(csvPath);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << csvPath << "\n";
    return false;
  }
  string line;
  int row = 0;
  while (getline(file, line)) {
    if (row != 0) { // Skip header row
      istringstream ss(line);
      string cell;
      int x, y;
      int column = 0;
      while (getline(ss, cell, ';')) {
        switch (column) {
        case 0:
          x = stoi(cell);
          break;
        case 1:
          y = stoi(cell);
          break;
        default:
          cerr << "Cam: invalide csv file\n";
          return false;
          break;
        }
        column++;
      }
      m_pos.setX(x);
      m_pos.setY(y);
    }
    row++;
  }
  file.close();
  return true;
}

void Cam::reset(int x, int y) {
  m_pos.setX(x);
  m_pos.setY(y);
}

void Cam::save(string csvPath) {
  if (m_save) {
    ofstream file(csvPath);
    if (!file.is_open()) {
      cerr << "Unable to open file: " << csvPath << "\n";
      return;
    }
    file << "x;y\n";
    file << m_pos.getX() << ";" << m_pos.getY() << "\n";
    file.close();
  }
}