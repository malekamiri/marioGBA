#ifndef DRAW_H
#define DRAW_H

#include "logic.h"

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state);

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state);

// If you have anything else you need accessible from outside the graphics.c
// file, you can add them here. You likely won't.
void drawMario(Mario *mario);
void drawMarioMovedRight(Mario *mario);
void undrawMarioMovedRight(Mario *mario);
void drawMarioMovedLeft(Mario *mario);
void undrawMarioMovedLeft(Mario *mario);
void drawMarioJump(Mario *mario, Block *block);
void undrawMarioMovedUp(Mario *mario);
void undrawMarioMovedDown(Mario *mario);
void drawBlock(Block *block);
void drawGround(Ground *ground);
void drawGroundMarioMovedRight(Ground *ground);
void drawBlockMarioMovedRight(Block *block);
void undrawBlockMarioMovedRight(Block *block);
void drawBlockMarioMovedLeft(Block *block);
void drawGroundMarioMovedLeft(Ground *ground);
void undrawBlockMarioMovedLeft(Block *block);
void drawBlockJump(Block *block);
void undrawBlockMovedUp(Block *block);
void undrawBlockMovedDown(Block *block);
void drawBrickBlock(Block *block);
#endif
