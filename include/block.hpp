#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "point.hpp"
#include "const.hpp"

using namespace std;


class Block {
public:
    // Constructeur par défaut
    Block();

    // Constructeur avec initialisation des attributs
    Block(int spriteSheetX, int spriteSheetY, int number, std::string name, int blockX, int blockY, bool isSolid);

    bool estDansCam(int posCamX,int posCamY, int largeur, int hauteur);
    
    // collision
    bool collide(int persoX, int persoY, int persoLargeur, int persoHauteur);
    bool collide(int persoX, int persoY, int persoLargeur, int persoHauteur, int persoVitesseX, int persoVitesseY);

    // Getters
    Point getSpriteSheet() const;
    int getNumber() const;
    std::string getName() const;
    int getX() const;
    int getY() const;
    bool isSolid() const;

    // Setters
    void setSpriteSheetX(int spriteSheetX);
    void setSpriteSheetY(int spriteSheetY);
    void setNumber(int number);
    void setName(std::string name);
    void setPosition(Point position);
    void setSolid(bool isSolid);

    // to string
    std::string toString() const;

private:
    Point m_spriteSheet;
    int m_number;
    std::string m_name;
    Point m_position;
    bool m_isSolid;
};

#endif