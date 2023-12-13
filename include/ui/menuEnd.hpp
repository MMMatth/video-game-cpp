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
  SoundSettings *m_soundSettings; /**< The sound settings. */
  function<void()> m_quit; /**< The function to call when the player quits. */
  function<void()>
      m_restart; /**< The function to call when the player restart. */

public:
  /** @brief function who init every button */
  void initButtons();

  /** @brief constructor for the menu end */
  MenuEnd(RenderWindow &window, SoundSettings &sound, bool isEnd,
          function<void()> quit, function<void()> restart);

  /** @brief a function who handle the menu end */
  void handle();

  /** @brief a function who update the menu end */
  void handleEvent(Event &event);

  /** @brief a function who render the buttons */
  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  /** @brief a function who render the menu end */
  void render(Cam &cam);

  /** @brief a function who return true if the game is end */
  bool isEnd() const;

  /** @brief a function who set the isEnd to false */
  void setIsEnd() { m_isEnd = false; }
};

#endif /* MENUEND_HPP */
