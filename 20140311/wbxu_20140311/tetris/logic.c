#include <stdio.h>
#include <stdlib.h> //for rand
#include <time.h>

#include "logic.h"
#include "ui.h"

//background
char g_BackGround[GAME_ROWS][GAME_COLS];

//brick
int g_nCurX;        //brick X坐标
int g_nCurY;        //brick Y坐标
int g_nType;        //brick 类型
int g_nRotate;      //旋转方式

//whether fixed
int g_nFixed;

//score
int g_nScore;

//pause
int g_nPause;

char g_Brick[][BRICK_COLS] = {
    //type 1: line
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
	0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
	0, 0, 0, 0,
    
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    
    //type 2: L
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
	0, 0, 0, 0,
    
    0, 0, 0, 0,
    0, 1, 1, 1,
    0, 1, 0, 0,
	0, 0, 0, 0,
    
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    
    0, 0, 0, 0,
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    
    //type 3: squre
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    
    //type 4: T
    0, 1, 1, 1,
    0, 0, 1, 0,
    0, 0, 1, 0,
	0, 0, 0, 0,
    
    0, 0, 0, 1,
    0, 1, 1, 1,
    0, 0, 0, 1,
	0, 0, 0, 0,
    
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 1, 1, 1,
	0, 0, 0, 0,
    
    0, 1, 0, 0,
    0, 1, 1, 1,
    0, 1, 0, 0,
	0, 0, 0, 0,
};

void
ResetBackGround(void)
{
    int i, j;
    
    for (i = 0; i < GAME_ROWS; i++)
    {
        for (j = 0; j < GAME_COLS; j++)
        {
            if ((0 == j)                    //1st colum
                || ((GAME_COLS - 1) == j)   //last colum
                || ((GAME_ROWS - 1) == i)   //last line
                )
            {
                g_BackGround[i][j] = GAME_WALL;
            }//wall
            else
            {
                g_BackGround[i][j] = GAME_NOT_WALL;
            }//not wall            
        }//end for cols
    }//end for rows
}

void
InitBackGround(void)
{
    //
    ResetBackGround();

    //
    DrawBackGround();
}

/*
Function: to judge whether this game is over.
*/
int
IsGameOver(void)
{
    int x, y;

    x = 0;
    y = 1;

    if (1 == IsMovable(x, y))
    {

        return 0;
    }

    return 1;
}

void
CreateBrick(void)
{
    //now use rand() to get a brick from g_Brick[][BRICK_COLUS]
    //brick is determined by (type, rotate)

    int nType;      //types of all brick

    //4 is the kinds of rotote
    nType   = (sizeof(g_Brick) / sizeof(g_Brick[0])) / (BRICK_ROWS * 4);

    srand((unsigned)time(NULL));
    
    g_nType     = rand() % nType;
    g_nRotate   = rand() % 4;
    g_nCurX     = (GAME_COLS) / 2 - 2;
    g_nCurY     = 0;   

    //this is for fix
    g_nFixed = 0;

    //aft brick created, judge whether is game over 
    //according to whether this brick can move down
    if (1 == IsGameOver())
    {
        printf("Game Over !!!\r\n");
        system("pause");
        exit(-1);
    }
}

/*
Function: whether the brick can be moved

Return  : 0 cannot be moved, 1 can
*/
int
IsMovable(int x, int y)
{
    int i, j;

    if (1 == g_nFixed)
    {
        return 0;
    }

    for (i = 0; i < BRICK_ROWS; i++)
    {
        for (j = 0; j < BRICK_COLS; j++)
        {
            if (GAME_WALL == g_Brick[BRICK_START + i][j])
            {
                if (GAME_WALL == g_BackGround[g_nCurY + i + y][g_nCurX + j + x])
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

/*
Function: whether this row can be released.

Return  : 0 for no, 1 for yes.
*/
int 
IsReleasable(int row)
{
    int col;

    for (col = 1; col < GAME_COLS - 1; col++)
    {
        //if GAME_NOT_WALL exists within this line, then cannot be released
        if (GAME_NOT_WALL == g_BackGround[row][col])
        {
            return 0;
        }
    }

    return 1;
}

/*
Function: move rows b4 this row down

*/
void
MoveLines(int row)
{
    int i, j;

    for (i = row; i > 0; i--)
    {
        if (1 == IsEmpty(i))
        {
            break;
        }

        for (j = 1; j < GAME_COLS - 1; j++)
        {
            g_BackGround[i][j] = g_BackGround[i - 1][j];
            
            /*
            //can also be done like this
            //just move GAME_NOT_WALL, those GAME_WALL keeps unchanged
            if (GAME_NOT_WALL == g_BackGround[i - 1][j])
            {
                g_BackGround[i][j] = g_BackGround[i - 1][j];
            }
            */
        }
    }//end for row
}

/*
Function: whether this row is empty
*/
int
IsEmpty(int row)
{
    int j;
    int empty;

    empty = 1;

    for (j = 1; j < GAME_COLS - 1; j++)
    {
        //if there is wall existing
        if (GAME_WALL == g_BackGround[row][j])
        {
            empty = 0;
        }
    }

    return empty;
}

/*
Function: release those line already filled with bricks

Return  : how many lines released.
*/
int
ReleaseLine(void)
{
    int nreleased;  //how many lines released
    int empty;     //whether this line is empty
    int row;

    nreleased = 0;
    empty    = 0;  //not empty

    for (row = GAME_ROWS - 2; row > 0; row-- )
    {
        //if this row is empty, then there is no need to go on.
        if (1 == IsEmpty(row))
        {
            break;
        }

        //whether this line can be released.
        if (1 == IsReleasable(row))
        {
            nreleased += 1;

            MoveLines(row);

            //need to step back to judge again for this row
            row += 1;                      
        }        
    }
    return nreleased;
}

#if 0
/*
Function: release those line already filled with bricks

Return  : how many lines released.
*/
int
ReleaseLine(void)
{
    int nreleased;
    int nempty;     //whether this line is empty;
    int i, j;

    nreleased = 0;
    nempty   = 1;
    
    for (i = GAME_ROWS - 1 - 1; i >= 0; i--)
    {
        for (j = 1; j < GAME_COLS - 1; j++)
        {
            if (GAME_NOT_WALL == g_BackGround[i][j])
            {
                break;
            }
        }
        
        //this line not all filled with bricks
        if (GAME_COLS - 1 != j)
        {
            break;
        }
        else
        {
            nreleased += 1;
        }
    }

    //now move lines down if there are lines released.
    for (i = GAME_ROWS - 1 - 1 - nreleased; (nreleased > 0)&&(i >= 0); i--)
    {
        for (j = 1; j < GAME_COLS - 1; j++)
        {
            if (GAME_NOT_WALL == g_BackGround[i][j])
            {
                g_BackGround[i + nreleased][j] = GAME_NOT_WALL;
            }
            else
            {
                nempty = 0;
            }
        }

        //no bricks within this line, it's empty, no more lines to be moved.
        if (1 == nempty)
        {
            break;
        }

    }

    return nreleased;
}

#endif

/*
Function: fix the brick if can, else fix it.
*/
void
FixBrick(void)
{
    int released = 0;

    //cannot move anymore
    g_nFixed = 1;

    ChangeBackGround(GAME_WALL);

    //now consider release line
    released = ReleaseLine();

    if (0 != released)
    {
        SetScore(released);
    }

    //now create a new brick
    CreateBrick();
}

/*
Function: set score
*/
void
SetScore(int released)
{
    g_nScore += (GAME_COLS - 2) * released;
}

/*
Function: Move up, that is to rotate
*/
void
MoveUp(void)
{
    int irotate;
    
    //save
    irotate = g_nRotate;

    //rotate firstly, then justify whether movable
    g_nRotate = (g_nRotate + 1) % 4;

    if (0 == IsMovable(0, 0))
    {
        //if cannot, restore
        g_nRotate = irotate;
    }
}

void
MoveFix(void)
{
    int x, y;
    x = 0;
    y = 1;
    
    while (1 == IsMovable(x, y))
    {
        g_nCurY += 1;
    }

    FixBrick();
}
/*
Function: move brick down if can, else we should fix it.
*/
void
MoveDown(void)
{
    int x, y;
    x = 0;
    y = 1;

    if (1 == IsMovable(x, y))
    {
        g_nCurY += 1;
    }
    else
    {
        FixBrick();
    }
}

void
MoveLeft(void)
{
    int x, y;
    x = -1;
    y = 0;
    
    if (1 == IsMovable(x, y))
    {
        g_nCurX -= 1;
    }   
    
}

void
MoveRight(void)
{
    int x, y;
    x = 1;
    y = 0;
    
    if (1 == IsMovable(x, y))
    {
        g_nCurX += 1;
    }    
}

void
StartGame(void)
{
    InitBackGround();

    CreateBrick();

    DrawBrick(); 

    GetInput();
}