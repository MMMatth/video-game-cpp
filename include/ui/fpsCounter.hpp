#ifndef FPS_COUNTER
#define FPS_COUNTER

#include "../utils/cam.hpp"
#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/**
 * @class FpsCounter
 * @brief Measures and displays frames per second (FPS).
 *
 * This class is responsible for measuring and displaying the frames per second
 * on the game window using SFML.
 */
class FpsCounter {
private:
  Clock m_clock; /**< SFML clock to measure time. */
  Coord m_coord; /**< Coordinates to display the FPS on the window. */
  int m_frameCount; /**< Counter for frames rendered. */
  int m_fps; /**< Calculated frames per second. */

public:
  /**
   * Parameterized constructor for FpsCounter.
   * @param x X-coordinate for displaying FPS on the window.
   * @param y Y-coordinate for displaying FPS on the window.
   */
  FpsCounter(int x, int y)
      : m_clock(), m_coord(x, y), m_frameCount(0), m_fps(0){};

  /**
   * Get the current frames per second.
   * @return Current frames per second.
   */
  int getFps() const { return m_fps; }

  /**
   * Update the frames per second count.
   */
  void update() {
    if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
      m_fps = m_frameCount;
      m_frameCount = 0;
      m_clock.restart();
    }
    m_frameCount++;
  }

  /**
   * Render the frames per second on the game window.
   * @param window Reference to the SFML RenderWindow.
   * @param cam Reference to the game camera.
   */
  void render(RenderWindow &window, Cam &cam) {
    int x = m_coord.getX() + cam.getX() - cam.getWidth() / 2;
    int y = m_coord.getY() + cam.getY() - cam.getHeight() / 2;
    drawTextWithEdge(x, y, "FPS:"+to_string(getFps()), &window, 20,
                     Color::White, Color::Black, FONT_PATH);
  }
};
#endif /* FPS_COUNTER */