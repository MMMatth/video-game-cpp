#ifndef SOUND_HPP
#define SOUND_HPP

#include "../utils/otherFunctions.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class SoundSettings {
private:
  float m_volume = 5;

public:
  SoundSettings(int volume);
  int getVolume();
  void setVolume(int volume);
};

#endif /*SOUND_HPP*/
