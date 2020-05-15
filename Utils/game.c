#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "game.h"
#include "rank.h"
#include "judge.h"
#include "menu.h"
#include "block.h"
#include "account.h"
#include "log.h"
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

int pauseFlag;
int restartFlag;
int quitFlag;
int isCtrlDown;
int isGameOver;

void TimerEventProcess(int timerID){ // 定时下落 
	if((timerID == normalDown) || (timerID == speederDown)){
		logOn("falling");
		gameInfo.current.y --;
		if(!judgeInter(gameInfo)){ // 如果碰撞判断成功，则判定为落下 
			gameInfo.current.y ++;
			if(endOneRound()) gameOver(); // 判断是否已经死了 
			else nextRound();
		}
	}
	if(isGameOver) return ;
	drawGame(gameInfo); // 刷新界面 
}

void modifyBGM(){
	if(banBGMFlag == 0){ // 关闭音乐 
		logOn("Stop BGM");
		banBGMFlag = 1;
		pauseBGM();
	}else{ // 打开音乐 
		logOn("Play BGM");
		banBGMFlag = 0;
		playBGM();
	}
}

void restartIt(){
	logOn("Restart");
	pauseFlag = 1; // 直接使用 pause 来使得游戏暂停 
	cancelTimer(normalDown);
	restartFlag = 1;
	drawConfRestart();
}

void pauseIt(){
	logOn("Pause");
	if(pauseFlag == 0){// 如果是正在运行中，则暂停游戏 
		printf("turn flag to 1\n");
		pauseFlag = 1;
		printf("flag : %d\n",pauseFlag);
		cancelTimer(normalDown);
		drawPause();
	}else{ // 如果正在暂停中，则开始游戏 
		pauseFlag = 0;
		startTimer(normalDown,normalDownTime);
		drawGame(gameInfo);
	}
}

void CharEventForGame(char ch){
    switch(ch){
    		case 's': case 'S':
    			printf("s\n");
    			if(isCtrlDown) saveGame();// 保存 
    			break;
    		case 'o': case 'O':
    			if(isCtrlDown) loadGame();// 读取 
    			break;
    		case 'e': case 'E':
    			ExitProcess(0); // 退出 
    			break;
    		case 'y': case 'Y': // 确认界面 (Yes)
    			if(restartFlag){
					restartFlag = 0; 
					Start();
				}
				if(quitFlag){
					quitFlag = 0;
					backToMenu();
				}
				break;
			case 'n': case 'N': // 确认界面 (No) 
				restartFlag = quitFlag = 0;
				pauseFlag = 0;
				startTimer(normalDown,normalDownTime);
				drawGame(gameInfo);
				break;
    		if(restartFlag || quitFlag) break;
			case 'z': case 'Z': // 交换方块 
				logOn("Switch block");
				if(switchBlockFlag == 1 || pauseFlag == 1) break; // 如果已经交换过了则 break 
				else switchBlockFlag = 1;
				if(gameInfo.hold.type == 0){// 如果手上没有方块 
					gameInfo.hold = gameInfo.current;
					nextRound();
				}else{ // 有方块的话。。。 
					Block t = gameInfo.hold;
					gameInfo.hold = gameInfo.current;
					t.x = 5;t.y = 20;
					gameInfo.current = t;
				}
				switch(gameInfo.hold.type){ // 根据方块种类对方块位置校准 
					case 1:
						gameInfo.hold.direction = 1;
						gameInfo.hold.x = 0;
						gameInfo.hold.y = 1; 
						break;
					case 4:
						gameInfo.hold.direction = 0;
						gameInfo.hold.x = -1;
						gameInfo.hold.y = 1;
						break;
					default:
						gameInfo.hold.direction = 0;
						gameInfo.hold.x = gameInfo.hold.y = 0;
				}
				drawGame(gameInfo);
	            break;
	        case 'p': case 'P': // 暂停 
	        	pauseIt();
	        	display();
	        	break;
	        case 'r': case 'R': // 重新开始 
	        	restartIt();
				break;
			case 'm': case 'M': // 音乐状态更改 
				modifyBGM();
				break;
			case 'q': case 'Q': // 退出 
				logOn("Quit");
				pauseFlag = 1;
				cancelTimer(normalDown);
				quitFlag = 1;
				drawConfQuit();
				break;
        default:
            break;
    }
}

void KeyboardEventForGame(int key,int event){
	static int down = 0;
	static int space = 0;
	static int left = 0;
	static int right = 0;
	static int up = 0;
    switch (event) {
	 	case KEY_DOWN:
	 		if(key == VK_CONTROL && isCtrlDown == 0) isCtrlDown = 1,printf("control down");
	 		if(isGameOver || pauseFlag) break;
			switch (key) {
			    case VK_UP: // 旋转方块 
			    	if(up == 0){
			    		up = 1;
			    		logOn("Turning");
						gameInfo.current.direction = (gameInfo.current.direction+1) % 4;
						if(!judgeInter(gameInfo)){ // 如果碰撞判定成功，则不允许旋转 
							gameInfo.current.direction = (gameInfo.current.direction-1+4)%4; 
						}
						drawGame(gameInfo);
                    }
					break;
			    case VK_DOWN: // 加速下落 
			    	if(down == 0){
			    		logOn("Speeder falling");
						cancelTimer(normalDown);// 通过改变加速器来进行加速下落 
						startTimer(speederDown,speederDownTime);
						drawGame(gameInfo);
						down = 1;
					}
                    break;
			    case VK_LEFT: // 左移 
			    	if(left == 0){
			    		left = 1;
			    		logOn("Move left");
						gameInfo.current.x --;
						if(!judgeInter(gameInfo)){ // 碰撞判定 
							gameInfo.current.x ++;
						}
						drawGame(gameInfo);
					}
                    break;
			    case VK_RIGHT: // 右移 
			    	if(right == 0){
						right = 1;
						logOn("Move Right");
						gameInfo.current.x ++;
						if(!judgeInter(gameInfo)){ // 碰撞判定 
							gameInfo.current.x --;
						}
						drawGame(gameInfo);
					}
                    break;
				case VK_SPACE: // 落下 
					if(space == 0){
						space = 1;
						logOn("Fall down");
						while(1){
							gameInfo.current.y --; // 一直下落直到碰撞判定成功 
							if(!judgeInter(gameInfo)) break;
						}
						gameInfo.current.y ++;
						drawGame(gameInfo);
						if(endOneRound()) gameOver();// 判断游戏是否结束 
						else nextRound();
						if(isGameOver) break;
						drawGame(gameInfo);
					}
					break;
			}
			break;
		case KEY_UP: // 通过按键锁，使得所有的按键必须松开后才能按下 
			if(key == VK_CONTROL && isCtrlDown == 1) isCtrlDown = 0,printf("control up");
			if(isGameOver) break;
			switch(key){
				case VK_DOWN:
					if(down == 1){
						logOn("Normal down");
						cancelTimer(speederDown);
						if(!isGameOver && !pauseFlag) startTimer(normalDown,normalDownTime);
						down = 0;
						drawGame(gameInfo);
					}
					break;
				case VK_SPACE:
					if(space == 1) space = 0;
					break;
				case VK_LEFT:
					if(left == 1) left = 0;
					break;
				case VK_RIGHT:
					if(right == 1) right = 0;
					break;
				case VK_UP:
					if(up == 1) up = 0;
					break;
			}
			break;
	 }	 
}

int endOneRound(){// 使落下的方块储存在游戏池中，并且进行消除以及游戏结束判定 
	logOn("Transfer block");
	Block x = gameInfo.current;
	int dir = x.direction % BlockMod[x.type];
    int i;
    for (i = 0; i < 4; i++) {
        int pos_x = x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
        int pos_y = x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
		if(pos_y > 20) return 1;// 判断是否游戏结束 
		gameInfo.map[pos_x][pos_y] = gameInfo.current.type;
    }
	int sco = checkEliminate(); // 计算消除行数 
	gameInfo.totLines += sco;
	if(sco != 0) checkLevel();
	return 0;
}

int checkEliminate(){
	logOn("Checking elimination");
	int i,j,k;
	int EliminateLines = 0;
	for(i=20;i>=1;--i){ // 自上而下逐行枚举行 
		if(checkLine(i)){ // 如果成功消除 
			++ EliminateLines;
			for(j=i;j<20;++j) for(k=1;k<=10;++k){ // 移动方块 
				gameInfo.map[k][j] = gameInfo.map[k][j+1];
			}
			for(k=1;k<=10;++k) gameInfo.map[j][20] = 0;
		}
	}
	if(EliminateLines != 0) playEliminate();// 落下&消除音效 
	else playDown(); 
	return EliminateLines;
}

int checkLine(int line){ // 检查消除条件 
	int i;
	for(i = 1;i<=10;++i){
		if(gameInfo.map[i][line] == 0) return 0;
	}
	return 1;
}

void nextRound(){
	switchBlockFlag = 0;
	gameInfo.current = gameInfo.next; // 交换方块 
	gameInfo.current.x = 5;
	gameInfo.current.y = 20;
	gameInfo.next = randomBlock(); // 随机方块 
}

void Start(){
	logOn("Start game");
	setToGameMode();
	playBGM();
	int i,j,k;
	// 一系列的初始化 
	for(i=1;i<=10;++i) for(j=1;j<=20;++j) gameInfo.map[i][j] = 0;
	gameInfo.current = randomBlock();
	gameInfo.next = randomBlock();
	gameInfo.hold.type = 0;
	gameInfo.current.x = 5;
	gameInfo.current.y = 20;
	gameInfo.level = 1;
	gameInfo.totLines = 0;
	switchBlockFlag = 0;
	isGameOver = 0;
	pauseFlag = banBGMFlag = restartFlag = quitFlag = 0;
	startTimer(normalDown,normalDownTime);
	drawGame(gameInfo);
}

void gameOver(){
	cancelTimer(normalDown);
	cancelTimer(speederDown);
	isGameOver = 1;
	drawOver();
	// 统计数据 
	userInfo.gameCount += 1;
	userInfo.totScore += gameInfo.totLines;
	userInfo.bestScore = max(userInfo.bestScore,gameInfo.totLines);
	saveToFile();
	updateRankList();
}

void checkLevel(){ 
	int sco = gameInfo.totLines;
	int newLevel = min(sco/10 + 1,15);// 计算等级 
	if(newLevel != gameInfo.level){
		gameInfo.level = min(sco / 10 + 1,15); // 15级为满级 
		cancelTimer(normalDown);
		startTimer(normalDown,normalDownTime);
	}
}

void backToMenu(){
	pauseBGM();
	startMenu(1);
}

void saveGame(){
	FILE * out = fopen(".//saves//playing.status","wb"); // 打开存档文件 
	if(out == NULL) return ;
	fwrite(&(gameInfo.level),sizeof(int),1,out);
	fwrite(&(gameInfo.totLines),sizeof(int),1,out);
	int i,j;
	for(i=1;i<=10;++i) for(j=1;j<=20;++j)
		fwrite(&(gameInfo.map[i][j]),sizeof(int),1,out);
	fwrite(&(gameInfo.current.direction),sizeof(int),1,out);
	fwrite(&(gameInfo.current.type),sizeof(int),1,out);
	fwrite(&(gameInfo.current.x),sizeof(int),1,out);
	fwrite(&(gameInfo.current.y),sizeof(int),1,out);
	
	fwrite(&(gameInfo.hold.direction),sizeof(int),1,out);
	fwrite(&(gameInfo.hold.type),sizeof(int),1,out);
	fwrite(&(gameInfo.hold.x),sizeof(int),1,out);
	fwrite(&(gameInfo.hold.y),sizeof(int),1,out);
	
	fwrite(&(gameInfo.next.direction),sizeof(int),1,out);
	fwrite(&(gameInfo.next.type),sizeof(int),1,out);
	fwrite(&(gameInfo.next.x),sizeof(int),1,out);
	fwrite(&(gameInfo.next.y),sizeof(int),1,out);
	
	fclose(out);
}

int loadGame(){// 同理 
	FILE * in = fopen(".//saves//playing.status","rb");
	if(in == NULL) return 0;
	fread(&(gameInfo.level),sizeof(int),1,in);
	fread(&(gameInfo.totLines),sizeof(int),1,in);
	int i,j;
	for(i=1;i<=10;++i) for(j=1;j<=20;++j)
		fread(&(gameInfo.map[i][j]),sizeof(int),1,in);
	fread(&(gameInfo.current.direction),sizeof(int),1,in);
	fread(&(gameInfo.current.type),sizeof(int),1,in);
	fread(&(gameInfo.current.x),sizeof(int),1,in);
	fread(&(gameInfo.current.y),sizeof(int),1,in);
	
	fread(&(gameInfo.hold.direction),sizeof(int),1,in);
	fread(&(gameInfo.hold.type),sizeof(int),1,in);
	fread(&(gameInfo.hold.x),sizeof(int),1,in);
	fread(&(gameInfo.hold.y),sizeof(int),1,in);
	
	fread(&(gameInfo.next.direction),sizeof(int),1,in);
	fread(&(gameInfo.next.type),sizeof(int),1,in);
	fread(&(gameInfo.next.x),sizeof(int),1,in);
	fread(&(gameInfo.next.y),sizeof(int),1,in);

	fclose(in);
}
