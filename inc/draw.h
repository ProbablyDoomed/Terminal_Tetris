#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

#define SCREEN_WIDTH  (64)
#define SCREEN_HEIGHT (32)

void draw_Init();
void draw_DrawPlayArea();
void draw_DrawScore(uint64_t score);
void draw_DrawBlock(uint16_t blockX, uint16_t blockY);

#endif /* DRAW_H */

