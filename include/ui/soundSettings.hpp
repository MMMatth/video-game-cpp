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

/** @brief a class who represent the sound in the game */
class SoundSettings {
private:
  float m_currentVolume; /**< The volume level for the game's sound. */
  float m_soundVolume;   /**< The volume level for the game's sound. */

  unordered_map<string, SoundBuffer> m_buffers; /**< The sound buffers. */
  Sound m_sound;                                /**< The SFML sound. */
  Music m_music;                                /**< The SFML music. */

public:
  /** @brief constructor for the sound settings */
  SoundSettings(int volume, Sound &sound,
                unordered_map<string, SoundBuffer> &buffers);

  /** @brief destructor for the sound settings */
  ~SoundSettings();

  /** @brief a function who get the current volume */
  int getVolume();

  /** @brief a function who set the current volume */
  void setVolume(int volume);

  /** @brief a function who mute the sound */
  void handleMute();

  /** @brief a function who return true if the sound is mute */
  bool isMute();

  /** @brief a function who play a sound
   * @param soundName the name of the sound
   */
  void playSound(string soundName);

  /** @brief a function who play a music
   * @param musicName the name of the music
   * @param loop true if the music must be loop
   */
  bool playMusic(string musicName, bool loop);
};

#endif /* SOUNDSETTINGS_HPP */