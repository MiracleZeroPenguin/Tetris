#ifndef COMPILE_DRAW
#define COMPILE_DRAW 

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include "block.h"
#include "game.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include<math.h>

#define PI 3.1415926
#define SquarLength 0.3  /*正方形边长*/ 
#define PrimaryX 3.0
#define PrimaryY 0.5

/* 
 * 函数名：DrawASquar
 * 功能：对指定矩形区域涂色
 * 参数：  x,y - 位置
 *         dx,dy - 涂色区域的宽度和高度
 */
void DrawASquar(double x,double y, double dx, double dy);

/* 
 * 函数名：fillRectangle
 * 功能：绘制一个矩形（涂色） 
 * 参数：  x,y - 位置
 *         dx,dy - 矩形的宽度和高度
 */
void fillRectangle(double x, double y, double w, double h);

/* 
 * 函数名：PaintSquar
 * 功能：将游戏池的特定方格涂上特定颜色 
 * 参数： newx,newy - 方格位置
 *        colortype - 颜色ID 
 */
void PaintSquar(int Newx,int Newy,int colortype);

/* 
 * 函数名：drawGame
 * 功能：绘制游戏中界面 
 * 参数：gameInfo - 当前游戏状态 
 */
void drawGame(GameInfo gameInfo);

/* 
 * 函数名：drawOver
 * 功能：绘制游戏结束窗口 
 */
void drawOver();

/* 
 * 函数名：drawPause
 * 功能：绘制暂停窗口 
 */
void drawPause();

/* 
 * 函数名：drawConfQuit
 * 功能：绘制确认退出窗口 
 */
void drawConfQuit();

/* 
 * 函数名：drawConfRestart
 * 功能：绘制确认重新开始窗口 
 */
void drawConfRestart();

/* 
 * 函数名：drawMenuUndefined
 * 功能：绘制未登录时的主菜单界面 
 */
void drawMenuUndefined();

/* 
 * 函数名：drawMenuDefined
 * 功能：绘制已登录时的主菜单界面 
 */
void drawMenuDefined();

/* 
 * 函数名：drawTextInt
 * 功能：在当前 Pen的位置输出数字  
 * 参数：num_int - 需要输出的数字 
 */
void drawTextInt(int num_int);

/* 
 * 函数名：drawRankingList
 * 功能：在当前界面的左下部分绘制排行榜 
 */
void drawRankingList();

/* 
 * 函数名：drawBackground
 * 功能：绘制主菜单背景 
 */
void drawBackground();

/* 
 * 函数名：drawProducerInfo
 * 功能：显示版权信息 
 */
void drawProducerInfo();

/* 
 * 函数名：drawTitle
 * 功能：绘制 Tetris标题 
 */
void drawTitle();

/* 
 * 函数名：drawMenuList
 * 功能：显示菜单栏 
 */
void drawMenuList();

/* 
 * 函数名：drawUserInfo
 * 功能：显示用户信息 
 */
void drawUserInfo();

#endif
