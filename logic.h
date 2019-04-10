#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

typedef struct {

   int height;
   int width;

   int x;
   int y;

   int justMovedRight;
   int justMovedLeft;
   int justMovedUp;
   int justMovedDown;

   // int isJumpingUp;
   // int isJumpingDown;
 } Mario;

 typedef struct {

   int height;
   int width;

   int x;
   int y;

   int startX;

   int justMovedRight;
   int justMovedLeft;
 } Ennemy;

 typedef struct {

   int x;
   int y;
   int justMovedRight;
   int justMovedLeft;
 } Ground;

typedef struct {

   int x;
   int y;
   int justMovedRight;
   int justMovedLeft;
 } Flag;

typedef struct {
    int height;
    int width;
    int x;
    int y;
    int isPopped;
    int justMovedRight;
    int justMovedLeft;
    int startX;
    int isOnScreen;
    int prize;
 } Block;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    int win;
    int score;
    int scoreJustChanged;

    int x;
    int lengthOfLevel;
    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */
    Mario mario;
    Ground ground;
    Block *block;
    Block *brick_block;
    Ennemy *ennemy;
    Flag *flag;


} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
typedef struct {

   int height;
   int width;

   int x;
   int y;
 } Mario;
*
*/




// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
