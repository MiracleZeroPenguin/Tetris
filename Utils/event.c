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

void CharEventProcess(char ch){ // 分发获得的字符信息 
	switch(eventMode){
		case menuMode:
			CharEventForMenu(ch); // 分发给 Menu 
			break;
		case gameMode:
			CharEventForGame(ch); // 分发给 Game 
			break;
	}
}
void KeyboardEventProcess(int key,int event){ // 分发获得的字符信息 
	switch(eventMode){
		case menuMode:
			KeyboardEventForMenu(key,event); // 分发给 Menu 
			break;
		case gameMode:
			KeyboardEventForGame(key,event); // 分发给 Game 
			break;
	}
}
