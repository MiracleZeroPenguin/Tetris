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
#define SquarLength 0.3  /*�����α߳�*/ 
#define PrimaryX 3.0
#define PrimaryY 0.5

/* 
 * ��������DrawASquar
 * ���ܣ���ָ����������Ϳɫ
 * ������  x,y - λ��
 *         dx,dy - Ϳɫ����Ŀ�Ⱥ͸߶�
 */
void DrawASquar(double x,double y, double dx, double dy);

/* 
 * ��������fillRectangle
 * ���ܣ�����һ�����Σ�Ϳɫ�� 
 * ������  x,y - λ��
 *         dx,dy - ���εĿ�Ⱥ͸߶�
 */
void fillRectangle(double x, double y, double w, double h);

/* 
 * ��������PaintSquar
 * ���ܣ�����Ϸ�ص��ض�����Ϳ���ض���ɫ 
 * ������ newx,newy - ����λ��
 *        colortype - ��ɫID 
 */
void PaintSquar(int Newx,int Newy,int colortype);

/* 
 * ��������drawGame
 * ���ܣ�������Ϸ�н��� 
 * ������gameInfo - ��ǰ��Ϸ״̬ 
 */
void drawGame(GameInfo gameInfo);

/* 
 * ��������drawOver
 * ���ܣ�������Ϸ�������� 
 */
void drawOver();

/* 
 * ��������drawPause
 * ���ܣ�������ͣ���� 
 */
void drawPause();

/* 
 * ��������drawConfQuit
 * ���ܣ�����ȷ���˳����� 
 */
void drawConfQuit();

/* 
 * ��������drawConfRestart
 * ���ܣ�����ȷ�����¿�ʼ���� 
 */
void drawConfRestart();

/* 
 * ��������drawMenuUndefined
 * ���ܣ�����δ��¼ʱ�����˵����� 
 */
void drawMenuUndefined();

/* 
 * ��������drawMenuDefined
 * ���ܣ������ѵ�¼ʱ�����˵����� 
 */
void drawMenuDefined();

/* 
 * ��������drawTextInt
 * ���ܣ��ڵ�ǰ Pen��λ���������  
 * ������num_int - ��Ҫ��������� 
 */
void drawTextInt(int num_int);

/* 
 * ��������drawRankingList
 * ���ܣ��ڵ�ǰ��������²��ֻ������а� 
 */
void drawRankingList();

/* 
 * ��������drawBackground
 * ���ܣ��������˵����� 
 */
void drawBackground();

/* 
 * ��������drawProducerInfo
 * ���ܣ���ʾ��Ȩ��Ϣ 
 */
void drawProducerInfo();

/* 
 * ��������drawTitle
 * ���ܣ����� Tetris���� 
 */
void drawTitle();

/* 
 * ��������drawMenuList
 * ���ܣ���ʾ�˵��� 
 */
void drawMenuList();

/* 
 * ��������drawUserInfo
 * ���ܣ���ʾ�û���Ϣ 
 */
void drawUserInfo();

#endif
