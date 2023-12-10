#ifndef SOUNDSETTINGS_HPP
#define SOUNDSETTINGS_HPP

#include "../utils/otherFunctions.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std;
using namespace sf;

class SoundSettings {
private:
  float m_currentVolume; /**< The volume level for the game's sound. */
  float m_volume;

  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;

public:
  SoundSettings(int volume, Sound &sound,
                unordered_map<string, SoundBuffer> &buffers);

  int getVolume();

  void setVolume(int volume);

  void handleMute();

  bool isMute();

  void playSound(string soundName);
};

#endif /* SOUNDSETTINGS_HPP */