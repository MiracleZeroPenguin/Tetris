#include "event.h"
#include "game.h"
#include "menu.h"

static int eventMode;

void setToGameMode(){
	eventMode = gameMode;
}

void setToMenuMode(){
	eventMode = menuMode;
}

void CharEventProcess(char ch){ // �ַ���õ��ַ���Ϣ 
	switch(eventMode){
		case menuMode:
			CharEventForMenu(ch); // �ַ��� Menu 
			break;
		case gameMode:
			CharEventForGame(ch); // �ַ��� Game 
			break;
	}
}
void KeyboardEventProcess(int key,int event){ // �ַ���õ��ַ���Ϣ 
	switch(eventMode){
		case menuMode:
			KeyboardEventForMenu(key,event); // �ַ��� Menu 
			break;
		case gameMode:
			KeyboardEventForGame(key,event); // �ַ��� Game 
			break;
	}
}
