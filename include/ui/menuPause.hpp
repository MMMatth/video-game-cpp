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

  SoundSettings *m_soundSettings; /**< The sound settings. */

  function<void()> m_quit; /**< The function to call when the player quits. */

public:
  /** @brief function who init every button */
  void initButtons();

  /** @brief constructor for the menu pause */
  MenuPause(RenderWindow &window, SoundSettings &soundSettings, bool ispause,
            function<void()> quit);

  /** @brief a function who handle the menu pause */
  void handle();

  /** @brief a function who update the menu pause */
  void update();

  /** @brief a function who handle event of the menu pause */
  void handleEvent(Event &event);

  /** @brief a function who render the buttons */
  void renderButtons(int XtopLeftCorner, int YtopLeftCorner);

  /** @brief a function who render the menu pause */
  void render(Cam &cam);

  /** @brief a function who return true if the game is pause */
  bool isPause() const;
};

#endif /* MENUPAUSE_HPP */