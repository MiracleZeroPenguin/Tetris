#ifndef COMPILE_GAME
#define COMPILE_GAME

#include "block.h"

#define test 233666
#define normalDown 1
#define speederDown 2
#define normalDownTime (600 - 30*(gameInfo.level-1) )
#define speederDownTime 60

#define nextPosX 15
#define nextPosY 17

#define holdPosX -4
#define holdPosY 17

typedef struct{
    int map[12][22];
    Block current;
    Block hold;
    Block next;
	int totLines;
	int level;
} GameInfo;


GameInfo gameInfo;

// 游戏是否已经结束 
int isGameOver;

// 本轮是否已经交换过方块 （一次下落中至多交换一次） 
int switchBlockFlag;

// 是否已暂停 
int pauseFlag;

// 是否已停用背景音乐 
int banBGMFlag;

// 是否正在确认是否重新开始 
int restartFlag;

// 正在确认是否退出到主菜单 
int quitFlag;

// Ctrl键是否按下 
int isCtrlDown;

/* 
 * 函数名：endOneRound
 * 功能：结束这一轮下落，并进行消除判断、数据更新 
 */
int endOneRound();

/* 
 * 函数名：nextRound
 * 功能：进入下一轮，随机生成一个方块作为 next 
 */
void nextRound();

/* 
 * 函数名：checkEliminate
 * 功能：检查当前游戏池是否存在满足消除条件的行，如果存在，则进行消除 
 * 返回值: int - 消除的行数 
 */
int checkEliminate();

/* 
 * 函数名：Start
 * 功能：开始整局游戏，包括计时器、标记的初始化等 
 */
void Start();

/* 
 * 函数名：backToMenu
 * 功能：从游戏中返回主菜单，是游戏状态的退出函数 
 */
void backToMenu();

/* 
 * 函数名：gameOver
 * 功能：游戏结束时调用，统计数据并调用排行榜接口、显示游戏结束等操作 
 */
void gameOver();

/* 
 * 函数名：checkLine
 * 功能：检查某一行是否符合消除条件 
 * 参数：line - 需要检查的行坐标 
 * 返回值:
 *   int - 0 ： 表示该行不满足消除条件
 *       - 1 ： 表示该行满足消除条件 
 */
int checkLine(int line);

/* 
 * 函数名：checkLevel
 * 功能：通过当前的分数计算等级，并对等级进行更新 
 */
void checkLevel();

/* 
 * 函数名：modifyBGM
 * 功能：更改背景音乐的状态 
 *       如果背景音乐正在播放，调用该函数则停用背景音乐
 *       反之亦然 
 */
void modifyBGM();

/* 
 * 函数名：pauseIt
 * 功能：暂停游戏 
 */
void pauseIt();

/* 
 * 函数名：restartIt
 * 功能：重新开始游戏 
 */
void restartIt();

/* 
 * 函数名：saveGame
 * 功能：储存该局游戏 
 */
void saveGame();

/* 
 * 函数名：loadGame
 * 功能：读取上次储存的游戏 
 */
int loadGame();

#endif
