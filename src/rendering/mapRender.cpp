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
      if (tile.isBackground()) {
        drawRectangle(tile.getX(), tile.getY(), TILE_SIZE, TILE_SIZE, &window,
                      Color(0, 0, 0), 100);
      }
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
void MapRender::renderMiniMap(RenderWindow &window,
                              unordered_map<string, Sprite> sprites, int camX,
                              int camY) {
  int miniMapScale = 4; // Change this to control the size of the mini-map
  int miniMapX = 0;
  int miniMapY = 0;

  for (int y = m_map.get_working_area().getY(); y < m_map.get_cam_height();
       y++) {
    for (int x = m_map.get_working_area().getX(); x < m_map.get_cam_width();
         x++) {
      Tile tile = m_map.get_tile(y, x);
      drawSprites(miniMapX + tile.getX() / miniMapScale,
                  miniMapY + tile.getY() / miniMapScale,
                  sprites[tile.getBlock()->getName()], &window,
                  TILE_SIZE / miniMapScale, TILE_SIZE / miniMapScale);
    }
  }
}