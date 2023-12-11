#include "../../include/ui/soundSettings.hpp"

SoundSettings::SoundSettings(int volume, Sound &sound,
                             unordered_map<string, SoundBuffer> &buffers)
    : m_currentVolume(volume), m_volume(volume), m_sound(sound),
      m_buffers(buffers) {}

int SoundSettings::getVolume() { return m_currentVolume; }

void SoundSettings::setVolume(int volume) { m_currentVolume = volume; }

bool SoundSettings::isMute() { return m_currentVolume == 0; }

void SoundSettings::playSound(string soundName) {
  m_sound.setBuffer(m_buffers[soundName]);
  m_sound.play();
}

void SoundSettings::handleMute() {
  if (isMute()) {
    m_currentVolume = m_volume;
  } else {
    m_currentVolume = 0;
  }
  m_sound.setVolume(m_currentVolume);
}
