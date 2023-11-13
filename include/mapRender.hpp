#ifndef MAPRENDER_HPP
#define MAPRENDER_HPP

#include "map.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MapRender {
private:
  Map &m_map;

public:
  MapRender(Map &map) : m_map(map) {}
  void render(RenderWindow &window, unordered_map<string, Sprite> sprites) {
    for (int y = m_map.get_cam().getY(); y < m_map.get_cam_height(); y++) {
      for (int x = m_map.get_cam().getX(); x < m_map.get_cam_width(); x++) {
        Tile tile = m_map.get_tile(y, x);
        drawSprites(tile.getX(), tile.getY(),
                    sprites[tile.getBlock().getName()], &window, TILE_SIZE,
                    TILE_SIZE);
      }
    }
  }
};

#endif // MAPRENDER_HPP