#include "../../include/map/tile.hpp"

Tile::Tile(Block block, int x, int y, bool isBackground)
    : m_coord(Coord(x * TILE_SIZE, y * TILE_SIZE)), m_block(block),
      m_isBackground(isBackground), m_isBreaking(false) {}

Tile::Tile(int x, int y, bool isBackground)
    : m_coord(Coord(x * TILE_SIZE, y * TILE_SIZE)), m_block(Block()),
      m_isBackground(isBackground), m_isBreaking(false) {}

bool Tile::estDansCam(int posCamX, int posCamY, int largeur, int hauteur) {
  if (m_coord.getX() >= posCamX - largeur &&
      m_coord.getX() <= posCamX + largeur &&
      m_coord.getY() >= posCamY - hauteur &&
      m_coord.getY() <= posCamY + hauteur) {
    return true;
  }
  return false;
}

bool isColliding(int entity_x, int entity_y, int entity_width,
                 int entity_height, int entity_speed, int tile_x, int tile_y) {
  return tile_x + TILE_SIZE > entity_x && tile_x < entity_x + entity_width &&
         tile_y + TILE_SIZE > entity_y &&
         tile_y < entity_y + entity_height + entity_speed;
}

void Tile::collide(Entity *entity) {
  int entity_x = entity->getX() + entity->getWidth() / 2;
  int entity_y = entity->getY();
  int entity_width = entity->getWidth();
  int entity_height = entity->getHeight();
  int entity_speed = entity->getSpeed();

  int tile_x = m_coord.getX();
  int tile_y = m_coord.getY();

  if (!m_block.isSolid() || m_isBackground)
    return;
  if (isColliding(entity_x, entity_y, entity_width, entity_height, entity_speed,
                  tile_x, tile_y)) {
    entity->setCollision("down", true);
  }
  if (isColliding(entity_x + entity_speed, entity_y, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    entity->setCollision("right", true);
  }
  if (isColliding(entity_x - entity_speed, entity_y, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    entity->setCollision("left", true);
  }
  if (isColliding(entity_x, entity_y - entity_speed, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    entity->setCollision("up", true);
  }
}

bool Tile::isCollidingEntity(Entity *entity) {
  int entity_x = entity->getX() + entity->getWidth() / 2;
  int entity_y = entity->getY();
  int entity_width = entity->getWidth();
  int entity_height = entity->getHeight();
  int entity_speed = entity->getSpeed();

  int tile_x = m_coord.getX();
  int tile_y = m_coord.getY();

  if (!m_block.isSolid() || m_isBackground)
    return false;
  if (isColliding(entity_x, entity_y, entity_width, entity_height, entity_speed,
                  tile_x, tile_y)) {
    return true;
  }
  if (isColliding(entity_x + entity_speed, entity_y, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    return true;
  }
  if (isColliding(entity_x - entity_speed, entity_y, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    return true;
  }
  if (isColliding(entity_x, entity_y - entity_speed, entity_width,
                  entity_height, 0, tile_x, tile_y)) {
    return true;
  }
  return false;
}
