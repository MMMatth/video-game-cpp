#include "../include/otherFunctions.hpp"

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