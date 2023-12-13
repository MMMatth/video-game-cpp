#ifndef CONST_HPP
#define CONST_HPP

/* other */
// #define
#define SAVE_PATH "../assets/save/"
#define INPUT_PATH "../assets/input/"
/* window */
#define FPS_MAX 60
#define TICKS_PER_FRAME 60.f
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "jeu"
/* cam */
#define CAM_WIDTH WINDOW_WIDTH * 0.75
#define CAM_HEIGHT WINDOW_HEIGHT * 0.75
#define CAM_SAVE_PATH "cam.csv"

/* character default */
#define CHAR_WIDTH 28
#define CHAR_HEIGHT 58
#define CHAR_JUMP_HEIGHT 80
#define CHAR_SPEED 3
#define CHAR_LIFE 100
#define CHAR_MAX_LIFE 30
#define ANIMATION_SPEED 100
#define NUM_FRAMES 9
#define CHAR_FILE_NAME "character.csv"
#define CHAR_X MAP_WIDTH *TILE_SIZE / 2
#define CHAR_Y CHAR_HEIGHT * 2

/* sound */
#define SOUND_CLICK "../assets/sound/pop.ogg"
#define SOUND_JUMP "../assets/sound/jump.wav"
#define SOUND_BREAK_A_BLOCK "../assets/sound/dig.ogg"
#define SOUND_MOVE "../assets/sound/move.wav"
#define SOUND_PUT_A_BLOCK "../assets/sound/hit.ogg"
#define VOLUME 50
/* menu */
#define VOLUME_ON_IMG_PATH "../assets/img/volume_on.png"
#define VOLUME_OFF_IMG_PATH "../assets/img/volume_off.png"
/*pause*/
#define IMG_PAUSE_ON "../assets/img/menuSoundOnPause.jpeg"
#define IMG_PAUSE_OFF "../assets/img/menuSoundOffPause.jpeg"
/*monster*/
#define IMG_MONSTER "../assets/img/monster.bmp"
#define NUM_MONSTERS_WALKING 3
#define NUM_MONSTERS_FLYING 2
#define NUM_FRAMES_MONSTER 3
#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_HEIGHT 3
#define HEALTH_BAR_OFFSET 5
#define MONSTERS_WIDTH 30
#define MONSTERS_HEIGHT 50
#define FLYING_MONSTERS_SPEED 3
#define WALKING_MONSTERS_SPEED 2
#define MONSTERS_SPAWN_RADIUS 50
#define JUMP_HEIGHT 18
#define ATTACKDISTANCE 400

/* inventory default data*/
#define INV_HEIGHT 4 // amout of tile in the inv in height
#define INV_WIDTH 9  // amout of tile in the inv in width
#define INV_TILE_SIZE (CAM_WIDTH / INV_WIDTH) * 0.8 // tile size in pixel
#define INV_OBJ_SIZE INV_TILE_SIZE * 0.6            // obj size in tile
#define MAX_STACK_SIZE 64 // max amount of item in a stack
#define INV_FILE_NAME "inventory.csv"
// inventory position
#define X_LOWER_BAR_OFFSET (INV_WIDTH * INV_TILE_SIZE) / 2
#define Y_LOWER_BAR_OFFSET -(CAM_HEIGHT / 2 - INV_TILE_SIZE * 2)
#define X_INV_OFFSET (INV_WIDTH * INV_TILE_SIZE) / 2
#define Y_INV_OFFSET (INV_HEIGHT * INV_TILE_SIZE) / 2
#define TOP_LEFT_INV_TILE (INV_TILE_SIZE - INV_OBJ_SIZE) / 2

/* spritesheet */
#define SPRITESHEET_INPUT_PATH "../assets/input/spritesheet_data.csv"
#define SPRITESHEET_IMG_PATH "../assets/img/spritesheet.png"
/* font */
#define FONT_PATH "assets/fonts/arial.ttf"
#define MINECRAFT_FONT_PATH "assets/fonts/minecraft.ttf"
#define FONT_COLOR Color(218, 225, 16)
#define WITE_COLOR Color::White
#define BLACK_COLOR Color::Black
#define RED_COLOR Color::Red
/* map */
#define MAP_WIDTH 150
#define MAP_SAVE_PATH "map.csv"
#define MAP_INPUT_PATH "../assets/input/map.csv"
#define MOUNTAIN_COEF 20 //
#define UNDERGROUND_COEF 10
#define SKY_HEIGHT_OVER_MOUTAIN 15
#define DIRT_HEIGHT 3
/* tree */
#define TREE_SIZE 4
#define ECART_TREE 10
#define LEAF_WIDTH 5
#define LEAF_HEIGHT 3
/* flower */
#define FLOWER_ECART 10

/*day night cycle default date */
#define TIME_IN_DAY 240 // time in second
#define DEFAULT_SKY_COLOR Color(119, 181, 254)
#define DAY_NIGHT_CYCLE_FILE_NAME "day_night_cycle.csv"
#define DAY_NIGHT_CYCLE_IMG_PATH "../assets/img/day_night_cycle.png"

/* other */
#define TILE_SIZE 32
#define GAME_MODE 1
#define MAX_LIFE 100
#define ZERO 0

#endif
