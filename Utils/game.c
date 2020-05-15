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

void TimerEventProcess(int timerID){ // ��ʱ���� 
	if((timerID == normalDown) || (timerID == speederDown)){
		logOn("falling");
		gameInfo.current.y --;
		if(!judgeInter(gameInfo)){ // �����ײ�жϳɹ������ж�Ϊ���� 
			gameInfo.current.y ++;
			if(endOneRound()) gameOver(); // �ж��Ƿ��Ѿ����� 
			else nextRound();
		}
	}
	if(isGameOver) return ;
	drawGame(gameInfo); // ˢ�½��� 
}

void modifyBGM(){
	if(banBGMFlag == 0){ // �ر����� 
		logOn("Stop BGM");
		banBGMFlag = 1;
		pauseBGM();
	}else{ // ������ 
		logOn("Play BGM");
		banBGMFlag = 0;
		playBGM();
	}
}

void restartIt(){
	logOn("Restart");
	pauseFlag = 1; // ֱ��ʹ�� pause ��ʹ����Ϸ��ͣ 
	cancelTimer(normalDown);
	restartFlag = 1;
	drawConfRestart();
}

void pauseIt(){
	logOn("Pause");
	if(pauseFlag == 0){// ��������������У�����ͣ��Ϸ 
		printf("turn flag to 1\n");
		pauseFlag = 1;
		printf("flag : %d\n",pauseFlag);
		cancelTimer(normalDown);
		drawPause();
	}else{ // ���������ͣ�У���ʼ��Ϸ 
		pauseFlag = 0;
		startTimer(normalDown,normalDownTime);
		drawGame(gameInfo);
	}
}

void CharEventForGame(char ch){
    switch(ch){
    		case 's': case 'S':
    			printf("s\n");
    			if(isCtrlDown) saveGame();// ���� 
    			break;
    		case 'o': case 'O':
    			if(isCtrlDown) loadGame();// ��ȡ 
    			break;
    		case 'e': case 'E':
    			ExitProcess(0); // �˳� 
    			break;
    		case 'y': case 'Y': // ȷ�Ͻ��� (Yes)
    			if(restartFlag){
					restartFlag = 0; 
					Start();
				}
				if(quitFlag){
					quitFlag = 0;
					backToMenu();
				}
				break;
			case 'n': case 'N': // ȷ�Ͻ��� (No) 
				restartFlag = quitFlag = 0;
				pauseFlag = 0;
				startTimer(normalDown,normalDownTime);
				drawGame(gameInfo);
				break;
    		if(restartFlag || quitFlag) break;
			case 'z': case 'Z': // �������� 
				logOn("Switch block");
				if(switchBlockFlag == 1 || pauseFlag == 1) break; // ����Ѿ����������� break 
				else switchBlockFlag = 1;
				if(gameInfo.hold.type == 0){// �������û�з��� 
					gameInfo.hold = gameInfo.current;
					nextRound();
				}else{ // �з���Ļ������� 
					Block t = gameInfo.hold;
					gameInfo.hold = gameInfo.current;
					t.x = 5;t.y = 20;
					gameInfo.current = t;
				}
				switch(gameInfo.hold.type){ // ���ݷ�������Է���λ��У׼ 
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
	        case 'p': case 'P': // ��ͣ 
	        	pauseIt();
	        	display();
	        	break;
	        case 'r': case 'R': // ���¿�ʼ 
	        	restartIt();
				break;
			case 'm': case 'M': // ����״̬���� 
				modifyBGM();
				break;
			case 'q': case 'Q': // �˳� 
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
			    case VK_UP: // ��ת���� 
			    	if(up == 0){
			    		up = 1;
			    		logOn("Turning");
						gameInfo.current.direction = (gameInfo.current.direction+1) % 4;
						if(!judgeInter(gameInfo)){ // �����ײ�ж��ɹ�����������ת 
							gameInfo.current.direction = (gameInfo.current.direction-1+4)%4; 
						}
						drawGame(gameInfo);
                    }
					break;
			    case VK_DOWN: // �������� 
			    	if(down == 0){
			    		logOn("Speeder falling");
						cancelTimer(normalDown);// ͨ���ı�����������м������� 
						startTimer(speederDown,speederDownTime);
						drawGame(gameInfo);
						down = 1;
					}
                    break;
			    case VK_LEFT: // ���� 
			    	if(left == 0){
			    		left = 1;
			    		logOn("Move left");
						gameInfo.current.x --;
						if(!judgeInter(gameInfo)){ // ��ײ�ж� 
							gameInfo.current.x ++;
						}
						drawGame(gameInfo);
					}
                    break;
			    case VK_RIGHT: // ���� 
			    	if(right == 0){
						right = 1;
						logOn("Move Right");
						gameInfo.current.x ++;
						if(!judgeInter(gameInfo)){ // ��ײ�ж� 
							gameInfo.current.x --;
						}
						drawGame(gameInfo);
					}
                    break;
				case VK_SPACE: // ���� 
					if(space == 0){
						space = 1;
						logOn("Fall down");
						while(1){
							gameInfo.current.y --; // һֱ����ֱ����ײ�ж��ɹ� 
							if(!judgeInter(gameInfo)) break;
						}
						gameInfo.current.y ++;
						drawGame(gameInfo);
						if(endOneRound()) gameOver();// �ж���Ϸ�Ƿ���� 
						else nextRound();
						if(isGameOver) break;
						drawGame(gameInfo);
					}
					break;
			}
			break;
		case KEY_UP: // ͨ����������ʹ�����еİ��������ɿ�����ܰ��� 
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

int endOneRound(){// ʹ���µķ��鴢������Ϸ���У����ҽ��������Լ���Ϸ�����ж� 
	logOn("Transfer block");
	Block x = gameInfo.current;
	int dir = x.direction % BlockMod[x.type];
    int i;
    for (i = 0; i < 4; i++) {
        int pos_x = x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
        int pos_y = x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
		if(pos_y > 20) return 1;// �ж��Ƿ���Ϸ���� 
		gameInfo.map[pos_x][pos_y] = gameInfo.current.type;
    }
	int sco = checkEliminate(); // ������������ 
	gameInfo.totLines += sco;
	if(sco != 0) checkLevel();
	return 0;
}

int checkEliminate(){
	logOn("Checking elimination");
	int i,j,k;
	int EliminateLines = 0;
	for(i=20;i>=1;--i){ // ���϶�������ö���� 
		if(checkLine(i)){ // ����ɹ����� 
			++ EliminateLines;
			for(j=i;j<20;++j) for(k=1;k<=10;++k){ // �ƶ����� 
				gameInfo.map[k][j] = gameInfo.map[k][j+1];
			}
			for(k=1;k<=10;++k) gameInfo.map[j][20] = 0;
		}
	}
	if(EliminateLines != 0) playEliminate();// ����&������Ч 
	else playDown(); 
	return EliminateLines;
}

int checkLine(int line){ // ����������� 
	int i;
	for(i = 1;i<=10;++i){
		if(gameInfo.map[i][line] == 0) return 0;
	}
	return 1;
}

void nextRound(){
	switchBlockFlag = 0;
	gameInfo.current = gameInfo.next; // �������� 
	gameInfo.current.x = 5;
	gameInfo.current.y = 20;
	gameInfo.next = randomBlock(); // ������� 
}

void Start(){
	logOn("Start game");
	setToGameMode();
	playBGM();
	int i,j,k;
	// һϵ�еĳ�ʼ�� 
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
	// ͳ������ 
	userInfo.gameCount += 1;
	userInfo.totScore += gameInfo.totLines;
	userInfo.bestScore = max(userInfo.bestScore,gameInfo.totLines);
	saveToFile();
	updateRankList();
}

void checkLevel(){ 
	int sco = gameInfo.totLines;
	int newLevel = min(sco/10 + 1,15);// ����ȼ� 
	if(newLevel != gameInfo.level){
		gameInfo.level = min(sco / 10 + 1,15); // 15��Ϊ���� 
		cancelTimer(normalDown);
		startTimer(normalDown,normalDownTime);
	}
}

void backToMenu(){
	pauseBGM();
	startMenu(1);
}

void saveGame(){
	FILE * out = fopen(".//saves//playing.status","wb"); // �򿪴浵�ļ� 
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

int loadGame(){// ͬ�� 
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
