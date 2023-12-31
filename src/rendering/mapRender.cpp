#include "../../include/rendering/mapRender.hpp"

void MapRender::render(RenderWindow &window,
                       unordered_map<string, Sprite> sprites) {
  for (int y = m_map.getCoordWorkingArea().getY();
       y < m_map.getWorkingAreaHeight(); y++) {
    for (int x = m_map.getCoordWorkingArea().getX();
         x < m_map.getWorkingAreaWidth(); x++) {
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
  int offsetX =
      camX + CAM_WIDTH / 2 - NB_BLOCK_MINIMAP * TILE_SIZE / MINIMAP_SCALE - 10;
  int offsetY = camY - CAM_HEIGHT / 2 + 10;
  int width = NB_BLOCK_MINIMAP * TILE_SIZE / MINIMAP_SCALE;
  int height = NB_BLOCK_MINIMAP * TILE_SIZE / MINIMAP_SCALE;

  int mini_map_areaX = (camX / TILE_SIZE) - NB_BLOCK_MINIMAP / 2;
  int mini_map_areaY = (camY / TILE_SIZE) - NB_BLOCK_MINIMAP / 2;
  int mini_map_areaWidth = (camX / TILE_SIZE) + NB_BLOCK_MINIMAP / 2;
  int mini_map_areaHeight = (camY / TILE_SIZE) + NB_BLOCK_MINIMAP / 2;

  if (mini_map_areaX < 0) {
    mini_map_areaX = 0;
    mini_map_areaWidth = NB_BLOCK_MINIMAP;
  }
  if (mini_map_areaY < 0) {
    mini_map_areaY = 0;
    mini_map_areaHeight = NB_BLOCK_MINIMAP;
  }

  if (mini_map_areaWidth > m_map.getWidth()) {
    mini_map_areaX = m_map.getWidth() - NB_BLOCK_MINIMAP;
    mini_map_areaWidth = m_map.getWidth();
  }

  if (mini_map_areaHeight > m_map.getHeight()) {
    mini_map_areaY = m_map.getHeight() - NB_BLOCK_MINIMAP;
    mini_map_areaHeight = m_map.getHeight();
  }

  drawRectangle(offsetX, offsetY, width, height, &window, Color(0, 0, 0),
                100); // draw the background

  // draw the map
  for (int y = mini_map_areaY; y < mini_map_areaHeight; y++) {
    for (int x = mini_map_areaX; x < mini_map_areaWidth; x++) {
      Tile tile = m_map.get_tile(y, x);
      int xtemp = x - mini_map_areaX;
      int ytemp = y - mini_map_areaY;
      drawSprites(offsetX + xtemp * (TILE_SIZE / MINIMAP_SCALE),
                  offsetY + ytemp * (TILE_SIZE / MINIMAP_SCALE),
                  sprites[tile.getBlock()->getName()], &window,
                  TILE_SIZE / MINIMAP_SCALE, TILE_SIZE / MINIMAP_SCALE);
    }
  }

  // draw the border
  drawEdge(offsetX, offsetY, width, height, &window, Color(255, 255, 255), 255);
}