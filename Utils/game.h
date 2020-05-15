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

// ��Ϸ�Ƿ��Ѿ����� 
int isGameOver;

// �����Ƿ��Ѿ����������� ��һ�����������ཻ��һ�Σ� 
int switchBlockFlag;

// �Ƿ�����ͣ 
int pauseFlag;

// �Ƿ���ͣ�ñ������� 
int banBGMFlag;

// �Ƿ�����ȷ���Ƿ����¿�ʼ 
int restartFlag;

// ����ȷ���Ƿ��˳������˵� 
int quitFlag;

// Ctrl���Ƿ��� 
int isCtrlDown;

/* 
 * ��������endOneRound
 * ���ܣ�������һ�����䣬�����������жϡ����ݸ��� 
 */
int endOneRound();

/* 
 * ��������nextRound
 * ���ܣ�������һ�֣��������һ��������Ϊ next 
 */
void nextRound();

/* 
 * ��������checkEliminate
 * ���ܣ���鵱ǰ��Ϸ���Ƿ�������������������У�������ڣ���������� 
 * ����ֵ: int - ���������� 
 */
int checkEliminate();

/* 
 * ��������Start
 * ���ܣ���ʼ������Ϸ��������ʱ������ǵĳ�ʼ���� 
 */
void Start();

/* 
 * ��������backToMenu
 * ���ܣ�����Ϸ�з������˵�������Ϸ״̬���˳����� 
 */
void backToMenu();

/* 
 * ��������gameOver
 * ���ܣ���Ϸ����ʱ���ã�ͳ�����ݲ��������а�ӿڡ���ʾ��Ϸ�����Ȳ��� 
 */
void gameOver();

/* 
 * ��������checkLine
 * ���ܣ����ĳһ���Ƿ������������ 
 * ������line - ��Ҫ���������� 
 * ����ֵ:
 *   int - 0 �� ��ʾ���в�������������
 *       - 1 �� ��ʾ���������������� 
 */
int checkLine(int line);

/* 
 * ��������checkLevel
 * ���ܣ�ͨ����ǰ�ķ�������ȼ������Եȼ����и��� 
 */
void checkLevel();

/* 
 * ��������modifyBGM
 * ���ܣ����ı������ֵ�״̬ 
 *       ��������������ڲ��ţ����øú�����ͣ�ñ�������
 *       ��֮��Ȼ 
 */
void modifyBGM();

/* 
 * ��������pauseIt
 * ���ܣ���ͣ��Ϸ 
 */
void pauseIt();

/* 
 * ��������restartIt
 * ���ܣ����¿�ʼ��Ϸ 
 */
void restartIt();

/* 
 * ��������saveGame
 * ���ܣ�����þ���Ϸ 
 */
void saveGame();

/* 
 * ��������loadGame
 * ���ܣ���ȡ�ϴδ������Ϸ 
 */
int loadGame();

#endif
