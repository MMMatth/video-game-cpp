#include "../include/tile.hpp"

Tile::Tile(Block block, int x, int y)
    : m_position(Coord(x * TILE_SIZE, y * TILE_SIZE)), m_block(block) {}

Tile::Tile(int x, int y)
    : m_position(Coord(x * TILE_SIZE, y * TILE_SIZE)), m_block(Block()) {}

bool Tile::estDansCam(int posCamX, int posCamY, int largeur, int hauteur) {
  if (m_position.getX() >= posCamX - largeur &&
      m_position.getX() <= posCamX + largeur &&
      m_position.getY() >= posCamY - hauteur &&
      m_position.getY() <= posCamY + hauteur) {
    return true;
  }
  return false;
}

void Tile::collide(Character *perso) {
  int persoX = perso->getX();
  int persoY = perso->getY();
  int persoLargeur = perso->getWidth();
  int persoHauteur = perso->getWidth();
  int persoVitesse = perso->getVitesse();

  int blockX = m_position.getX();
  int blockY = m_position.getY();

  if (m_block.isSolid() && blockX + TILE_SIZE > persoX &&
      blockX < persoX + persoLargeur && blockY + TILE_SIZE > persoY &&
      blockY < persoY + persoHauteur + persoVitesse) {
    perso->setCollision("down", true);
  }
  if (m_block.isSolid() && blockX + TILE_SIZE > persoX && // left
      blockX < persoX + persoLargeur + persoVitesse &&
      blockY + TILE_SIZE > persoY && blockY < persoY + persoHauteur // down
  ) {
    perso->setCollision("right", true);
  }
  if (m_block.isSolid() && blockX + TILE_SIZE > persoX - persoVitesse &&
      blockX < persoX + persoLargeur && blockY + TILE_SIZE > persoY &&
      blockY < persoY + persoHauteur) {
    perso->setCollision("left", true);
  }
  if (m_block.isSolid() && blockX + TILE_SIZE > persoX - persoVitesse &&
      blockX < persoX + persoLargeur && blockY + TILE_SIZE > persoY &&
      blockY < persoY + persoHauteur) {
    perso->setCollision("left", true);
  }
  if (m_block.isSolid() && blockX + TILE_SIZE > persoX &&
      blockX < persoX + persoLargeur &&
      blockY + TILE_SIZE > persoY - persoVitesse &&
      blockY < persoY + persoHauteur) {
    perso->setCollision("up", true);
  }
}