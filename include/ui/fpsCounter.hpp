#ifndef FPS_COUNTER
#define FPS_COUNTER

#include "../utils/cam.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class FpsCounter {
private:
  Clock m_clock;
  Coord m_coord;
  int m_frameCount;
  int m_fps;

public:
  FpsCounter(int x, int y)
      : m_clock(), m_coord(x, y), m_frameCount(0), m_fps(0){};

  /* getters */
  int getFps() const { return m_fps; }

  void update() {
    if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
      m_fps = m_frameCount;
      m_frameCount = 0;
      m_clock.restart();
    }
    m_frameCount++;
  }

  void render(RenderWindow &window, Cam &cam) {
    int x = m_coord.getX() + cam.getX() - cam.getWidth() / 2;
    int y = m_coord.getY() + cam.getY() - cam.getHeight() / 2;
    drawTextWithEdge(x, y, "FPS : " + to_string(getFps()), &window, 20,
                     Color::White, Color::Black, FONT_PATH);
  }
};
#endif /* FPS_COUNTER */