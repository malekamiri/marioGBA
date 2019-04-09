#include "draw.h"
#include "gba.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "images/garbage.h"
#include "images/start_screen.h"
#include "images/ground_block.h"
#include "images/mario_character.h"
#include "images/prize_block.h"
#include "images/prize_block_popped.h"
#include "images/mario_character_b.h"
#include "images/mario_character_blue.h"

#include "images/ennemy.h"

#include "images/flag_end.h"
#include "images/game_over.h"
#include "images/game_win.h"
// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
// #include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    drawGround(&(state->ground));
    drawMario(&(state->mario));
    //drawBlock(&(state->block));
    // draw the score
    char buffer[51];
    int score = state->score;
    sprintf(buffer, "Score: %d", score);
    drawString(5, 5, buffer, YELLOW);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    if (state->block->justMovedRight) {
        undrawBlockMarioMovedRight((state->block));
        state->block->justMovedRight = 0;
    }
    if (state->block->justMovedLeft) {
        undrawBlockMarioMovedLeft((state->block));
        state->block->justMovedLeft = 0;
    }
    if (state->brick_block->justMovedRight) {
        undrawBlockMarioMovedRight((state->brick_block));
        state->brick_block->justMovedRight = 0;
    }
    if (state->block->justMovedLeft) {
        undrawBlockMarioMovedLeft((state->brick_block));
        state->brick_block->justMovedLeft = 0;
    }
    if (state->scoreJustChanged) {
        drawRectDMA(5, 5, 50, 15, BACKGROUND);
        state->scoreJustChanged = 0;
    }


    // drawGround(&(state->ground));
    // fillScreenDMA(BACKGROUND);

}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.

    drawGround(&(state->ground));
    drawMario(&(state->mario));
    // if (state->block->isOnScreen) {
    //     drawBlock(&(state->block));
    // }
    if (state->block->startX + state->block->width > state->x) {
        drawBlock((state->block));

    }
    if (state->brick_block->startX + state->brick_block->width > state->x) {
        drawBrickBlock((state->brick_block));

    }

        //    drawImageDMA(18, state->flag->y, 35, 112, flag_end);


    if (state->x + 240 >= state->lengthOfLevel) {
        drawImageDMA(18, state->flag->y, 35, 112, flag_end);
    }

    if (state->x + 240 >= state->ennemy->startX && state->ennemy->y > -222) {
        drawEnnemy(state->ennemy);
    }
    // draw the score
    //drawRectDMA(0, 0, 200, 15, BACKGROUND);
    char buffer[51];
    int score = state->score;
    sprintf(buffer, "Score: %d", score);
    drawString(5, 5, buffer, YELLOW);

    if (state->gameOver) {
        if (state->win) {
            drawFullScreenImageDMA(game_win);
        } else {
            drawFullScreenImageDMA(game_over);
        }
    }
}


//This function draws the ground
void drawGround(Ground *ground) {
    for (int i = 0; i < 16; i++) {
        drawImageDMA(130, (ground->x + i * 15) % 240, 15, 15, ground_block);
        drawImageDMA(145, (ground->x + i * 15) % 240, 15, 15, ground_block);
    }

}
void drawGroundMarioMovedRight(Ground *ground) {
    ground->x -= 1;
    drawGround(ground);
}

void drawBlockMarioMovedRight(Block *block) {
    block->y -= 1;
    drawBlock(block);
}

void drawGroundMarioMovedLeft(Ground *ground) {
    ground->x += 1;
    drawGround(ground);
}

void drawBlockMarioMovedLeft(Block *block) {
    block->y += 1;
    drawBlock(block);
}

void undrawBlockMarioMovedRight(Block *block) {
    drawRectDMA(block->x, block->y + block->startX + 15, 1, 15, BACKGROUND);
}

void undrawBlockMarioMovedLeft(Block *block) {
    drawRectDMA(block->x, block->y - 3 + block->startX, 1, 15, BACKGROUND);
}

//This function draws mario on the ground
void drawMario(Mario *mario) {
    drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character_b);

}

void drawMarioMovedRight(Mario *mario) {
    mario->y += 3;
    drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character_b);
}

void undrawMarioMovedRight(Mario *mario) {
    drawRectDMA(mario->x, mario->y - 3, 3, 35, BACKGROUND);
}

void drawMarioMovedLeft(Mario *mario) {
    mario->y -= 3;
    drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character_b);
}

void undrawMarioMovedLeft(Mario *mario) {
    drawRectDMA(mario->x, mario->y + mario->width, 3, 35, BACKGROUND);
}

void undrawMarioMovedUp(Mario *mario) {
    drawRectDMA(mario->x + mario->width, mario->y, 35, 3, BACKGROUND);
}
void undrawMarioMovedDown(Mario *mario) {
    drawRectDMA(mario->x - 3, mario->y, 35, 3, BACKGROUND);
}


void drawMarioJump(Mario *mario, Block *block) {
    for (int i = 0; i < 7; i++) {
        mario->x -= 3;
        drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character_b);
        undrawMarioMovedUp(mario);
        volatile int x = 0;
        for (int i = 0; i < 8000; i++) {
                x++;
        }
    }
    if (block != 0) {
        drawBlockJump(block);
    }

    for (int i = 7; i > 0; i--) {
        mario->x += 3;
        drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character_b);
        undrawMarioMovedDown(mario);

        volatile int x = 0;
        for (int i = 0; i < 8000; i++) {
                x++;
        }
    }
    //drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character);

}

void drawBlockJump(Block *block) {
    for (int i = 0; i < 3; i++) {
        block->x -= 3;
        if (block->prize) {
            drawImageDMA(block->x, block->y + block->startX, block->width, block->height, prize_block);
        } else {
            drawImageDMA(block->x, block->y + block->startX, block->width, block->height, ground_block);
        }

        undrawBlockMovedUp(block);
        volatile int x = 0;
        for (int i = 0; i < 8000; i++) {
                x++;
        }
    }
    for (int i = 3; i > 0; i--) {
        block->x += 3;
        if (block->prize) {
            drawImageDMA(block->x, block->y + block->startX, block->width, block->height, prize_block);
        } else {
            drawImageDMA(block->x, block->y + block->startX, block->width, block->height, ground_block);
        }
        undrawBlockMovedDown(block);

        volatile int x = 0;
        for (int i = 0; i < 8000; i++) {
                x++;
        }
    }
    drawImageDMA(block->x, block->y + block->startX, block->width, block->height, prize_block_popped);
    block->isPopped = 1;
    //drawImageDMA(mario->x, mario->y, mario->width, mario->height, mario_character);

}
void undrawBlockMovedUp(Block *block) {

    drawRectDMA(block->x + block->width, block->y + block->startX, 35, 3, BACKGROUND);
}
void undrawBlockMovedDown(Block *block) {
    drawRectDMA(block->x - 3, block->y + block->startX, 35, 3, BACKGROUND);
}

void drawBlock(Block *block) {
    if (!block->isPopped) {
        drawImageDMA(block->x, block->y + block->startX, 15, 15, prize_block);
    } else {
        drawImageDMA(block->x, block->y + block->startX, 15, 15, prize_block_popped);
    }


}
void drawBrickBlock(Block *block) {
    if (!block->isPopped) {
        drawImageDMA(block->x, block->y + block->startX, 15, 15, ground_block);
    } else {
        drawRectDMA(block->x, block->y + block->startX, 15, 15, BACKGROUND);
    }


}

void drawEnnemy(Ennemy *ennemy_mario) {

    drawImageDMA(ennemy_mario->x, ennemy_mario->y + 222, ennemy_mario->width, ennemy_mario->height, mario_ennemy);
}





//TODO : refactor x into y. mario->x becomes mario->y and drawImageDMA(x,y) becomes drawImageDMA(y,x)