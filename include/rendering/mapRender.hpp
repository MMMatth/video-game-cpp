#ifndef MAPRENDER_HPP
#define MAPRENDER_HPP

#include "../map/map.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MapRender {
private:
  Map &m_map;

public:
  MapRender(Map &map) : m_map(map) {}

  void render(RenderWindow &window, unordered_map<string, Sprite> sprites);

  void renderMiniMap(RenderWindow &window,
                     unordered_map<string, Sprite> sprites, int camX, int camY);
};

#endif // MAPRENDER_HPP