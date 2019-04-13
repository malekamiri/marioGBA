#ifndef MYLIB_H
#define MYLIB_H

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
void drawEnnemy(Ennemy *ennemy);
void undrawEnnemyMovedLeft(Ennemy *ennemy);

#endif