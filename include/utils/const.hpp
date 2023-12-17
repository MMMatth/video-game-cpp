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
#define CHAR_JUMP_HEIGHT 16
#define CHAR_SPEED 3
#define CHAR_LIFE 100
#define CHAR_MAX_LIFE 30
#define ANIMATION_SPEED 100
#define NUM_FRAMES 9
#define CHAR_FILE_NAME "character.csv"
#define CHAR_X MAP_WIDTH *TILE_SIZE / 2
#define CHAR_Y CHAR_HEIGHT * 2
#define RADUIS_ATTACK 500
#define CHAR_ATTACK 25

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
#define NUM_MONSTERS_WALKING 5
#define NUM_MONSTERS_FLYING 3
#define NUM_FRAMES_MONSTER 3

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_HEIGHT 3
#define HEALTH_BAR_OFFSET 5

#define MONSTERS_WIDTH 30
#define MONSTERS_HEIGHT 50

#define FLYING_MONSTERS_SPEED 3
#define WALKING_MONSTERS_SPEED 2
#define MONSTERS_SPAWN_RADIUS 50
#define JUMP_HEIGHT 16
#define ATTACKDISTANCE 400
#define MONSTER_FILE_NAME "monsters.csv"

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

#define DISTANCEMONSTERPLAYER 15
/* inventory */
#define INVENTORY_HEIGHT 4
#define INVENTORY_WIDTH 9
#define INVENTORY_TILE_SIZE (CAM_WIDTH / INVENTORY_WIDTH) * 0.8
#define INVENTORY_OBJECT_SIZE INVENTORY_TILE_SIZE * 0.6
#define MAX_STACK_SIZE 64
#define INVENTORY_SAVE_PATH "inventory.csv"

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

/* map generator param */
#define MAP_WIDTH 126      // the width of the map in tile
#define MOUNTAIN_COEF 16   // the coef of the mountain
#define UNDERGROUND_COEF 8 // the coef of the underground
#define SKY_HEIGHT_OVER_MOUTAIN                                                \
  32                                   // the amout of sky tile over the biggest
                                       // moutain
#define DIRT_HEIGHT 3                  // amout of dirt tile over the stone
#define TREE_IS_BACKGROUND true        // if the tree is in background
#define CURVE_ALLTITUDE_FREQUENCY 0.01 // the frequency for perlin noise
#define CAVE_FREQUENCY 0.09 // the frequency for NoiseType_OpenSimplex2S noise
#define TREE_SIZE 4
#define TILE_SIZE 32
#define ECART_TREE 10
#define LEAF_WIDTH 5
#define LEAF_HEIGHT 3
#define FLOWER_ECART 10
/* other map param */
#define MAP_SAVE_PATH "map.csv"
#define MAP_INPUT_PATH "../assets/input/map.csv"

/*day night cycle default date */
#define TIME_IN_DAY 240 // time in second
#define DEFAULT_SKY_COLOR Color(119, 181, 254)
#define DAY_NIGHT_CYCLE_FILE_NAME "day_night_cycle.csv"
#define DAY_NIGHT_CYCLE_IMG_PATH "../assets/img/day_night_cycle.png"

/* other */
#define GAME_MODE 1
#define MAX_LIFE 100
#define ZERO 0

#endif
