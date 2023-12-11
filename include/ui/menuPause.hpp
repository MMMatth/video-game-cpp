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

  SoundSettings *m_soundSettings;

  function<void()> m_quit;

public:
  void initButtons();

  MenuPause(RenderWindow &window, SoundSettings &soundSettings, bool ispause,
            function<void()> quit);

  void handle();

  void update();

  void handleEvent(Event &event);

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  void render(Cam &cam);

  bool isPause() const;
};

#endif /* MENUPAUSE_HPP */