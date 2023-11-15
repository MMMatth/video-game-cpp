#ifndef CONST_HPP
#define CONST_HPP

/* window */
#define FPS_MAX 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "jeu"
/* cam */
#define CAM_WIDTH WINDOW_WIDTH
#define CAM_HEIGHT WINDOW_HEIGHT
/* character */
#define TAILLE_PERSONNAGE 64
#define DEPLACEMENT 5
#define ANIMATION_SPEED 100
#define NUM_FRAMES 9
#define CHARACTER_SAVE_PATH "../assets/csv/character.csv"
/* sound */
#define SOUND_PLAY "../assets/sound/pop.ogg"
#define SOUND_QUIT SOUND_PLAY
#define SOUND_JUMP "../assets/sound/jump.wav"
#define SOUND_BREAK_A_BLOCK "../assets/sound/dig.ogg"
#define SOUND_MOVE "../assets/sound/move.wav"
#define SOUND_PUT_A_BLOCK "../assets/sound/hit.ogg"
#define VOLUME 5
/* menu */
#define IMG_MENU "../assets/img/menu.JPEG"
/* inventory */
#define INVENTORY_HEIGHT 4
#define INVENTORY_WIDTH 9
#define INVENTORY_TILE_SIZE (CAM_WIDTH / INVENTORY_WIDTH) * 0.8
#define INVENTORY_OBJECT_SIZE INVENTORY_TILE_SIZE * 0.6
#define MAX_STACK_SIZE 64
#define INVENTORY_SAVE_PATH "../assets/csv/inventory.csv"
/* spritesheet */
#define SPRITESHEET_CSV_PATH "../assets/csv/spritesheet_data.csv"
#define SPRITESHEET_IMG_PATH "../assets/img/spritesheet.png"
/* font */
#define FONT_PATH "assets/fonts/arial.ttf"
#define FONT_COLOR Color(0, 0, 0)
/* map */
#define MAP_WIDTH 100
#define MAP_PATH "../assets/csv/map.csv"
#define MOUNTAIN_COEF 20 //
#define UNDERGROUND_COEF 10
#define SKY_HEIGHT_OVER_MOUTAIN 15
#define DIRT_HEIGHT 50
/* tree */
#define TREE_SIZE 4
#define ECART_TREE 10
#define LEAF_WIDTH 5
#define LEAF_HEIGHT 3
/* flower */
#define FLOWER_ECART 10
/* other */
#define SKY_COLOR Color(135, 206, 250)
#define TILE_SIZE 32

#endif
