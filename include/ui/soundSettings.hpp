#ifndef SOUNDSETTINGS_HPP
#define SOUNDSETTINGS_HPP

#include "../utils/otherFunctions.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/**
 * @class SoundSettings
 * @brief Represents sound settings in the game.
 *
 * The SoundSettings class manages the volume setting for the game's sound.
 */
class SoundSettings {
private:
  float m_volume; /**< The volume level for the game's sound. */

public:
  /**
   * Parameterized constructor for SoundSettings.
   * @param volume The initial volume level.
   */
  SoundSettings(int volume);

  /**
   * Get the current volume level.
   * @return The volume level.
   */
  int getVolume();
  /**
   * Set the volume level.
   * @param volume The new volume level.
   */
  void setVolume(int volume);
};

#endif /* SOUNDSETTINGS_HPP */