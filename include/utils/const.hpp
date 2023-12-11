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
/* character */
#define CHAR_DEFAULT_COORD_X MAP_WIDTH *TILE_SIZE / 2
#define CHAR_DEFAULT_COORD_Y TAILLE_PERSONNAGE * 2
#define TAILLE_PERSONNAGE 64
#define DEPLACEMENT 5
#define ANIMATION_SPEED 100
#define NUM_FRAMES 9
#define CHARACTER_SAVE_PATH "character.csv"
#define CHARACTER_MAX_LIFE 30
/* sound */
#define SOUND_PLAY "../assets/sound/pop.ogg"
#define SOUND_QUIT SOUND_PLAY
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
#define NUM_MONSTERS_FLYING 1
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
/*day night cycle*/
#define DEFAULT_TIME_DAY 240 // 4 min
#define DAY_NIGHT_CYCLE_CSV_PATH "day_night_cycle.csv"
#define DAY_NIGHT_CYCLE_IMG_PATH "../assets/img/day_night_cycle.png"
#define DEFAULT_SKY_COLOR Color(119, 181, 254)

/* other */
#define TILE_SIZE 32
#define GAME_MODE 1
#define MAX_LIFE 100
#define ZERO 0

#endif
