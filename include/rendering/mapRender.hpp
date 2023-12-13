#ifndef MAPRENDER_HPP
#define MAPRENDER_HPP

#define NB_BLOCK_MINIMAP 38 // he must be pair
#define MINIMAP_SCALE 8

#include "../map/map.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MapRender {
private:
  Map &m_map;

public:
  /** @brief constructor for the map render*/
  MapRender(Map &map) : m_map(map) {}

  /** @brief Render a single block. */
  void renderBlock(Tile &tile, RenderWindow &window,
                   unordered_map<string, Sprite> sprites);

  /** @brief Render the shade for a single block (if is background) */
  void renderShade(Tile &tile, RenderWindow &window);

  /** @brief Render the breaking phase for a single block. */
  void renderBreakPhase(Tile &tile, RenderWindow &window,
                        unordered_map<string, Sprite> sprites);

  /** @brief Render the entire map. */
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites);

  /** @brief Render the minimap. */
  void renderMiniMap(RenderWindow &window,
                     unordered_map<string, Sprite> sprites, int camX, int camY);
};

#endif // MAPRENDER_HPP