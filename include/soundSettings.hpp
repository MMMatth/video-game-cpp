#ifndef SOUND_HPP
#define SOUND_HPP

#include "../include/otherFunctions.hpp"
#include <iostream>
using namespace std;

class SoundSettings {
private:
  float m_volume = 5;

public:
  SoundSettings(int volume);
  int getVolume();
  void setVolume(int volume);
};

#endif /*SOUND_HPP*/
