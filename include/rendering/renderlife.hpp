// #ifndef RENDERLIFE_HPP
// #define RENDERLIFE_HPP

// #include "../utils/draw.hpp"
// #include <SFML/Graphics.hpp>
// #include <unordered_map>

// using namespace sf;
// using namespace std;

// void renderLife(RenderWindow &window, unordered_map<string, Sprite> sprites,
//                 int life, int camX, int camY) {
//   int entire_heart = life / 2;
//   int half_heart = life % 2;
//   int x = camX - (INVENTORY_WIDTH * INVENTORY_TILE_SIZE) / 2;
//   int y = camY + CAM_HEIGHT / 2 - INVENTORY_TILE_SIZE * 2 - 20;

//   for (int i = 0; i < 10; i++) {
//     drawSprites(x + i * 15, y, sprites["BLACK_HEART"], &window, 15, 15);
//   }
//   for (int i = 0; i < entire_heart; i++) {
//     drawSprites(x + i * 15, y, sprites["HEART"], &window, 15, 15);
//   }
//   for (int i = half_heart; i < entire_heart + half_heart; i++) {
//     drawSprites(x + i * 15, y, sprites["HALF_HEART"], &window, 15, 15);
//   }
// }

// #endif /* RENDERLIFE_HPP */