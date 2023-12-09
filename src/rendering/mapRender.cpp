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
  int miniMapScale = 6; // Change this to control the size of the mini-map
  int offsetX = camX + CAM_WIDTH / 2 -
                (m_map.get_cam_width() - m_map.get_working_area().getX()) *
                    TILE_SIZE / miniMapScale -
                10;
  int offsetY = camY - CAM_HEIGHT / 2 + 10;
  int width = (m_map.get_cam_width() - m_map.get_working_area().getX()) *
              TILE_SIZE / miniMapScale;
  int height = (m_map.get_cam_height() - m_map.get_working_area().getY()) *
               TILE_SIZE / miniMapScale;

  drawRectangle(offsetX, offsetY, width, height, &window, Color(0, 0, 0), 100);

  for (int y = m_map.get_working_area().getY(); y < m_map.get_cam_height();
       y++) {
    for (int x = m_map.get_working_area().getX(); x < m_map.get_cam_width();
         x++) {
      Tile tile = m_map.get_tile(y, x);
      int xtemp = x - m_map.get_working_area().getX();
      int ytemp = y - m_map.get_working_area().getY();
      drawSprites(offsetX + xtemp * (TILE_SIZE / miniMapScale),
                  offsetY + ytemp * (TILE_SIZE / miniMapScale),
                  sprites[tile.getBlock()->getName()], &window,
                  TILE_SIZE / miniMapScale, TILE_SIZE / miniMapScale);
    }
  }
}