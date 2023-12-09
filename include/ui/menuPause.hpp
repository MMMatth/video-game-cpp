#ifndef MENUPAUSE_HPP
#define MENUPAUSE_HPP

#include "../utils/cam.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "soundSettings.hpp"
#include "ui.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class MenuPause : public Ui {
private:
  bool m_pause; /**< Flag indicating whether the game is paused. */

  // RenderWindow &m_window;
  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;
  SoundSettings &m_soundSettings;

  // function quit of the game
  function<void()> m_quit;

public:
  void initButtons();

  MenuPause(RenderWindow &window, Sound &sound,
            unordered_map<string, SoundBuffer> &buffers,
            SoundSettings &soundSettings, bool ispause, function<void()> quit);

  void handle();

  void update();

  void handleEvent(Event &event);

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  void render(Cam &cam);

  bool isPause() const;
};

#endif /* MENUPAUSE_HPP */