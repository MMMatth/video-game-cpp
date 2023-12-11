#ifndef MENUEND_HPP
#define MENUEND_HPP

#include "../utils/cam.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "ui.hpp"
#include "../entity/monsters.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class MenuEnd : public Ui {
private:
  bool m_isEnd; /**< Flag indicating whether to show the end menu. */
  SoundSettings *m_soundSettings;
  function<void()> m_quit;
  function<void()> m_restart;
  Monsters &m_monsters;
public:
  void initButtons();

  MenuEnd(RenderWindow &window, SoundSettings &sound, bool isEnd,
          function<void()> quit, function<void()> restart, Monsters &monsters );

  void handle();

  void handleEvent(Event &event);

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  void render(Cam &cam);

  bool isEnd() const;

  void setIsEnd() { m_isEnd = false; }
};

#endif /* MENUEND_HPP */
