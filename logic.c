#include "logic.h"
#include "draw.h"

#include <stdio.h>
#include <stdlib.h>

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->gameOver = 0;
    appState->win = 0;
    Mario mario;
    mario.width = 35;
    mario.height = 35;
    mario.x = 95;
    mario.y = 40;
    mario.justMovedRight = 0;
    mario.justMovedLeft = 0;
    mario.justMovedUp = 0;
    mario.justMovedDown = 0;
    // mario.isJumpingUp = 0;
    // mario.isJumpingDown = 0;
    appState->mario = mario;

    Ground ground;
    ground.x = 130;
    ground.y = 0;
    ground.justMovedRight = 0;
    ground.justMovedLeft = 0;
    appState->ground = ground;

    Block *block = malloc(sizeof(Block));
    if (block == 0) {
        return;
    }
    block->x = 58;
    block->y = 0;
    block->width = 15;
    block->height = 15;
    block->isPopped = 0;
    block->justMovedRight = 0;
    block->justMovedLeft = 0;
    block->startX = 130;
    block->isOnScreen = 1;
    block->prize = 1;
    appState->block = block;


    Block *brick_block = malloc(sizeof(Block));
    if (brick_block == 0) {
        return;
    }
    brick_block->x = 58;
    brick_block->y = 0;
    brick_block->width = 15;
    brick_block->height = 15;
    brick_block->isPopped = 0;
    brick_block->justMovedRight = 0;
    brick_block->justMovedLeft = 0;
    brick_block->startX = 145;
    brick_block->isOnScreen = 1;
    brick_block->prize = 0;
    appState->brick_block = brick_block;

    Ennemy *ennemy = malloc(sizeof(Ennemy));
    if (ennemy == 0) {
        return;
    }
    ennemy->width = 18;
    ennemy->height = 18;
    ennemy->x = 112;
    ennemy->y = 0;
    ennemy->startX = 350;
    ennemy->justMovedRight = 0;
    ennemy->justMovedLeft = 0;
    appState->ennemy = ennemy;


    Flag *flag = malloc(sizeof(Flag));
    if (flag == 0) {
        return;
    }
    flag->x = 18;
    flag->y = 205;
    flag->justMovedRight = 0;
    flag->justMovedLeft = 0;
    appState->flag = flag;

    appState->score = 0;
    appState->scoreJustChanged = 0;
    appState->x = 0;
    appState->lengthOfLevel = 800;

    // appState->reset = 0;

}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */


    if (KEY_DOWN((BUTTON_RIGHT), keysPressedNow)) {

            currentAppState->ground.x -= 1;
            currentAppState->block->y -= 1;
            currentAppState->block->justMovedRight = 1;

            currentAppState->brick_block->y -= 1;
            currentAppState->brick_block->justMovedRight = 1;


            currentAppState->ground.justMovedRight = 1;
            currentAppState->x += 1;

            if (currentAppState->x + 240 >= currentAppState->lengthOfLevel) {
                currentAppState->flag->y -= 1;
            }
            if (currentAppState->x + 100 >= currentAppState->lengthOfLevel) {
                currentAppState->gameOver = 1;
                currentAppState->win = 1;
            }

            // if (currentAppState->block->y + currentAppState->block->startX < 0 || currentAppState->block->y + currentAppState->block->startX > 160) {
            //     currentAppState->block->isOnScreen = 0;
            // } else {
            //     currentAppState->block->isOnScreen = 1;
            // }

    }
    if (KEY_DOWN((BUTTON_LEFT), keysPressedNow)) {

            currentAppState->ground.x += 1;
            currentAppState->block->y += 1;
            currentAppState->block->justMovedLeft = 1;
            currentAppState->ground.justMovedLeft = 1;

            currentAppState->brick_block->y += 1;
            currentAppState->brick_block->justMovedLeft = 1;

            currentAppState->x -= 1;

            if (currentAppState->x + 240 >= currentAppState->lengthOfLevel) {
                currentAppState->flag->y += 1;
            }

            if (currentAppState->x + 100 >= currentAppState->lengthOfLevel) {
                currentAppState->gameOver = 1;
                currentAppState->win = 1;
            }
            if (currentAppState->x + 240 >= currentAppState->ennemy->startX) {
                currentAppState->ennemy->y -= 3;
            }

    }
    if (KEY_JUST_PRESSED((BUTTON_UP), keysPressedNow, keysPressedBefore)) {
        if (currentAppState->mario.y > currentAppState->block->y + currentAppState->block->startX - currentAppState->mario.width && currentAppState->mario.y < currentAppState->block->y + currentAppState->block->startX + currentAppState->block->width && !currentAppState->block->isPopped) {
            drawMarioJump(&(currentAppState->mario), (currentAppState->block));
            currentAppState->score += 1000;
            currentAppState->scoreJustChanged = 1;
        } else if (currentAppState->mario.y > currentAppState->brick_block->y + currentAppState->brick_block->startX - currentAppState->mario.width && currentAppState->mario.y < currentAppState->brick_block->y + currentAppState->brick_block->startX + currentAppState->brick_block->width && !currentAppState->brick_block->isPopped) {
            drawMarioJump(&(currentAppState->mario), (currentAppState->brick_block));
            currentAppState->score += 1000;
            currentAppState->scoreJustChanged = 1;
        } else {
            drawMarioJump(&(currentAppState->mario), 0);
        }
        if (currentAppState->x + 240 >= currentAppState->ennemy->startX) {
            currentAppState->ennemy->y += 1;
        }

    }
    if (currentAppState->x + 240 >= currentAppState->ennemy->startX) {
        currentAppState->ennemy->y -= 1;
        // if (currentAppState->x + 35 == currentAppState->ennemy->startX + currentAppState->ennemy->y) {
        //     currentAppState->gameOver = 1;
        // }
    }


    if (KEY_JUST_PRESSED((BUTTON_SELECT), keysPressedNow, keysPressedBefore)) {
        //if win is set to 1 but not gameOver. It means reset.
        currentAppState->win = 1;

    }
    AppState nextAppState = *currentAppState;

    return nextAppState;
}
