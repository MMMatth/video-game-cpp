#include "../../include/ui/soundSettings.hpp"

SoundSettings::SoundSettings(int volume, Sound &sound,
                             unordered_map<string, SoundBuffer> &buffers)
    : m_currentVolume(volume), m_soundVolume(volume), m_sound(sound),
      m_buffers(buffers) {}

int SoundSettings::getVolume() { return m_currentVolume; }

void SoundSettings::setVolume(int volume) { m_currentVolume = volume; }

bool SoundSettings::isMute() { return m_currentVolume == 0; }

void SoundSettings::playSound(string soundName) {
  m_sound.setBuffer(m_buffers[soundName]);
  m_sound.play();
}

bool SoundSettings::playMusic(string musicName, bool loop) {
  if (!m_music.openFromFile(musicName)) {
    cerr << "Impossible to open music file ";
    return false;
  }
  m_music.setLoop(loop);
  m_music.setVolume(m_currentVolume);
  m_music.play();
  return true;
}

void SoundSettings::handleMute() {
  if (isMute()) {
    m_currentVolume = m_soundVolume;
  } else {
    m_currentVolume = 0;
  }
  m_music.setVolume(m_currentVolume);
  m_sound.setVolume(m_currentVolume);
}
