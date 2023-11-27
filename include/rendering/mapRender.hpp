#ifndef MAPRENDER_HPP
#define MAPRENDER_HPP

#include "../map/map.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/**
 * @class MapRender
 * @brief Responsible for rendering the game map.
 *
 * This class handles the rendering of the game map using SFML.
 */
class MapRender {
private:
  Map &m_map; /**< Reference to the game map. */

public:
  /**
   * Parameterized constructor for MapRender.
   * @param map Reference to the game map.
   */
  MapRender(Map &map) : m_map(map) {}

  /**
   * Render the entire game map on the window.
   * @param window Reference to the SFML RenderWindow.
   * @param sprites Map of sprites containing the block images.
   */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites);
};

#endif // MAPRENDER_HPP