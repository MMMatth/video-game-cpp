#include "../include/block.hpp"

// Constructeur par défaut
Block::Block() :
    m_spriteSheet(Point(0, 0)),
    m_number(0),
    m_name(""),
    m_position(Point(0, 0)),
    m_isSolid(false)
{}

// Constructeur avec initialisation des attributs
Block::Block(int spriteSheetX, int spriteSheetY, int number, std::string name, int blockX, int blockY, bool isSolid):
    m_spriteSheet(Point(spriteSheetX, spriteSheetY)),
    m_number(number),
    m_name(name),
    m_position(Point(blockX, blockY)),
    m_isSolid(isSolid)
{}

// Getters
Point Block::getSpriteSheet() const {
    return m_spriteSheet;
}

int Block::getNumber() const {
    return m_number;
}

std::string Block::getName() const {
    return m_name;
}

bool Block::estDansCam(Point posCam, int largeur, int hauteur){
    if (m_position.getX() >= posCam.getX() - largeur && m_position.getX() <= posCam.getX() + largeur && m_position.getY() >= posCam.getY() - hauteur && m_position.getY() <= posCam.getY() + hauteur){
        return true;
    }
    return false;
}

bool Block::collide(int persoX, int persoY, int persoLargeur, int persoHauteur) {
    int blockRight = m_position.getX() + TAILLE_CASE;
    int blockBottom = m_position.getY() + TAILLE_CASE;
    int persoRight = persoX + persoLargeur;
    int persoBottom = persoY + persoHauteur;

    if (m_isSolid && blockRight >= persoX && m_position.getX() <= persoRight && blockBottom >= persoY && m_position.getY() <= persoBottom) {
        return true;
    }
    return false;
}


int Block::getX() const {
    return m_position.getX();
}

int Block::getY() const {
    return m_position.getY();
}

bool Block::isSolid() const {
    return m_isSolid;
}

// Setters
void Block::setSpriteSheetX(int spriteSheetX) {
    m_spriteSheet.setX(spriteSheetX);
}

void Block::setSpriteSheetY(int spriteSheetY) {
    m_spriteSheet.setY(spriteSheetY);
}

void Block::setNumber(int number) {
    m_number = number;
}

void Block::setName(std::string name) {
    m_name = name;
}

void Block::setPosition(Point position) {
    m_position = position;
}

void Block::setSolid(bool isSolid) {
    m_isSolid = isSolid;
}

std::string Block::toString() const {
    std::string s = "Block {";
    s += "spriteSheet: (" + std::to_string(m_spriteSheet.getX()) + ", " + std::to_string(m_spriteSheet.getY()) + "), ";
    s += "number: " + std::to_string(m_number) + ", ";
    s += "name: " + m_name + ", ";
    s += "position: (" + std::to_string(m_position.getX()) + ", " + std::to_string(m_position.getY()) + "), ";
    s += "isSolid: " + std::to_string(m_isSolid) + "}";
    return s;
}