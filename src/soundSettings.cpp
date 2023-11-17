#include "../include/soundSettings.hpp"

SoundSettings::SoundSettings(int volume) : m_volume(volume){};

int SoundSettings::getVolume() { return m_volume; }

void SoundSettings::setVolume(int volume) { m_volume = volume; }
