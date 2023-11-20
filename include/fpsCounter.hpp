#ifndef FPS_COUNTER
#define FPS_COUNTER

#include "cam.hpp"
#include "coord.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class FpsCounter

{
private:
  Clock m_clock;
  Coord m_coord;

public:
  FpsCounter(int x, int y) : m_clock(), m_coord(x, y){};

  /* getters */
  int getFps() {
    if (m_clock.getElapsedTime().asMilliseconds() == 0) {
      return 0;
    }
    return 1000 / m_clock.getElapsedTime().asMilliseconds();
  }

  void render(RenderWindow &window, Cam &cam) {
    int x = m_coord.getX() + cam.getX() - cam.getWidth() / 2;
    int y = m_coord.getY() + cam.getY() - cam.getHeight() / 2;
    drawTextWithEdge(x, y, "FPS : " + to_string(getFps()), &window, 20,
                     Color::White, Color::Black, FONT_PATH);
  }
  void update() { m_clock.restart(); }
};

#endif /* FPS_COUNTER */