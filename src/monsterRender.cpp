#include "../include/monsterRender.hpp"


MonsterRender::MonsterRender(Monster &monster): m_monster(monster){}

/*Draw function for MonsterRender class*/
void MonsterRender::draw(RenderWindow& window, Monster& monster) {
    /*Get direction and sprites from the Monster*/
    map<string, bool> direction = monster.getDirection();
    unordered_map<string, Sprite> sprites = monster.getSprites();

    /*Calculate the frame for animation based on elapsed time*/
    int frame = (m_clock.getElapsedTime().asMilliseconds() / ANIMATION_SPEED) % NUM_FRAMES_MONSTER;
    
    /*Calculate the position of the Monster for drawing*/
    int x = monster.getX() + (monster.getWidth() / 2); 
    int y = monster.getY();

    /*Check the direction and draw the appropriate sprite*/
    if (direction["right"]) {
        drawSprites(x, y, sprites["moveRight" + to_string(frame + 1)], &window, monster.getWidth(), monster.getHeight());
    } else if (direction["left"]) {
        drawSprites(x, y, sprites["moveLeft" + to_string(frame + 1)], &window, monster.getWidth(), monster.getHeight());
    }
}
