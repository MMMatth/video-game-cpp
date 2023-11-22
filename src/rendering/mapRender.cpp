#include "../../include/rendering/mapRender.hpp"

void MapRender::render(RenderWindow &window,
                       unordered_map<string, Sprite> sprites) {
  for (int y = m_map.get_working_area().getY(); y < m_map.get_cam_height();
       y++) {
    for (int x = m_map.get_working_area().getX(); x < m_map.get_cam_width();
         x++) {
      Tile tile = m_map.get_tile(y, x);
      drawSprites(tile.getX(), tile.getY(), sprites[tile.getBlock()->getName()],
                  &window, TILE_SIZE, TILE_SIZE);
      if (tile.isBreaking() && tile.getBlock()->getName() != "AIR") {
        int palier = tile.getBlock()->getTimeToBreak() / 10;
        int frame =
            tile.getBreakingClock().getElapsedTime().asMilliseconds() / palier;
        Sprite sprite = sprites["DESTROY_STAGE"];
        sprite.setTextureRect(
            IntRect(sprites["DESTROY_STAGE"].getTextureRect().left + frame * 16,
                    sprites["DESTROY_STAGE"].getTextureRect().top, 16, 16));
        drawSprites(tile.getX(), tile.getY(), sprite, &window, TILE_SIZE,
                    TILE_SIZE);
      }
    }
  }
}