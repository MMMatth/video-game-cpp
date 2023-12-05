#include "../../include/utils/otherFunctions.hpp"

void Error(bool condition, const string &message) {
  if (condition) {
    cerr << message << endl;
    exit(EXIT_FAILURE);
  }
}
void Error(const string &message) {
  cerr << message << endl;
  exit(EXIT_FAILURE);
}
void handleFileError(const string &filePath) {
  cerr << "Unable to open file " << filePath << "\n";
  exit(EXIT_FAILURE);
}

bool isInside(int mouseX, int mouseY, int x, int y, int width, int height) {
  return mouseX >= x && mouseX <= x + width && mouseY >= y &&
         mouseY <= y + height;
}
