#ifndef MENUEND_HPP
#define MENUEND_HPP

#include "../utils/cam.hpp"
#include "../utils/draw.hpp"
#include "../utils/otherFunctions.hpp"
#include "ui.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class MenuEnd : public Ui {
private:
  bool m_isEnd; /**< Flag indicating whether to show the end menu. */

  unordered_map<string, SoundBuffer> m_buffers;
  Sound m_sound;
  function<void()> m_quit;
  function<void()> m_restart;
public:
  void initButtons();

  MenuEnd(RenderWindow &window, Sound &sound,
          unordered_map<string, SoundBuffer> &buffers, bool isEnd,
          function<void()> quit, function<void()> restart);

  void handle();

  void handleEvent(Event &event);

  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  void render(Cam &cam);

  bool isEnd() const;

  void setIsEnd(){m_isEnd = false;}
};

#endif /* MENUEND_HPP */
