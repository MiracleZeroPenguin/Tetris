#include "menu.h"
#include "account.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "draw.h"
#include "game.h"
#include "rank.h"
#include "conio.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"

int isShowingInfo;

void CharEventForMenu(char ch){
	switch(nowMenuMode){ // ����ģʽ���䱸���ִ���ģʽ 
		case unDefinedMenu:
			solveUndefined(ch);
			break;
		case definedMenu:
			solveDefined(ch);
			break;
		case inputing:
			solveInputing(ch);
			break;
	}
}

void KeyboardEventForMenu(int key,int event){
	if(nowMenuMode != inputing) return ;
	switch(event){
		case KEY_DOWN:
			break;
		case KEY_UP:
			switch(key){
				case VK_RETURN:
					logOn("End input");// �س����� 
					endInput();
					return ;
			}
			break;
	}	
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display();
}

void newUser(){
	inputMode = registerMode;
	logOn("Creating new user");
	newAccount();
}

void findUser(){
	inputMode = loginMode;
	logOn("Use existed saves");
	newAccount();

}

void solveUndefined(char ch){
	switch(ch){
		case 'w': case 'W':
			newUser(); // �½� 
			break;
		case 'a': case 'A':
			findUser(); // �� 
			break;
		case 'h': case 'H':
			logOn("Open help");
			openHelp(); // ���� 
			break;
		case 'q': case 'Q':
			ExitProcess(0); // �˳� 
			break;
	}
}

void switchUserInfo(){
    if(isShowingInfo == 0){
			logOn("Switch to user information");
			drawUserInfo(); // ������Ϣ 
			isShowingInfo = 1;
		}else{
			logOn("Switch back");
			drawProducerInfo(); // ��Ȩ��Ϣ 
			isShowingInfo = 0;
	}
} 

void StartIt(){
	logOn("Start game");
	nowMenuMode = playing;
	Start();
}

void solveDefined(char ch){
	switch(ch){
		case 's': case 'S':
			StartIt(); // ��ʼ��Ϸ 
			break;
		case 'l': case 'L':
			logOn("Log out");
			logOut(); // �ǳ� 
			break;
		case 'h': case 'H':
			logOn("Open help");
			openHelp(); // ���� 
			break;
		case 'q': case 'Q':
			ExitProcess(0); // �˳� 
			break;
		case 'u': case 'U':
			switchUserInfo(); // �û���Ϣ 
			break;
		
	}
}

void solveInputing(char ch){
	uiGetChar(ch); // GUI�ַ�����
	logOn("Inputing");
	display(); //ˢ����ʾ
}

void startMenu(int x){
	// Menu ��� 
	logOn("Start menu");
	loadList();
	setToMenuMode();
	nowMenuMode = x;
	isShowingInfo = 0;
	switch(isDefined){
		case 0:
			drawMenuUndefined();
			break;
		case 1:
			drawMenuDefined();
			break;
	}
}

void inputBox() 
{
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    nowMenuMode = inputing;
    display();
}


// �ı��༭��ʾ����
void drawEditText()
{
	static char newnum[80] = "";
	static char firstName[80] = "";
	double fH = GetFontHeight();
	double h = fH*2; // �ؼ��߶�
	double w = winwidth/4; // �ؼ����
	double x = winwidth/2-w/2;
	double y = winheight/2;
	drawBackground();
	drawRankingList();
	drawTitle();
	flashLog();
	SetPenColor("Black");
	MovePen(PrimaryX-5*SquarLength,PrimaryY-1*SquarLength);
	DrawTextString("If you want to achieve some function, press the corresponding shortcut key on the keyboard.");
	SetPenColor("Brown"); 
	if(inputMode == registerMode)
		drawLabel(x-fH/2-TextStringWidth("ע��"), (y-=h*1.2)+fH*0.7, "ע��");
	else
		drawLabel(x-fH/2-TextStringWidth("�û���"), (y-=h*1.2)+fH*0.7, "�û���");
	if( textbox(GenUIID(0), x, y, w, h, firstName, sizeof(firstName)) )
		sprintf(results,"%s", firstName);				/*(*^��^*)*/ 
	drawLabel(x,y-=fH*1.2,newnum);
}

void display()
{
	// ˢ�º�����Ҫ���ݵ�ǰ������ģʽ����ѡ�Լ���ˢ�·�ʽ 
	//printf("come in display : %d (mode)\n",nowMenuMode);
	printf("get flag %d\n",pauseFlag);
	switch(nowMenuMode){
		case unDefinedMenu:
			drawMenuUndefined();
			break;
		case definedMenu:
			drawMenuDefined();
			break;
		case inputing:
			DisplayClear();
			drawEditText();
			drawReturn();
			break;
		case playing:
			drawGame(gameInfo);
			// �������״̬���⴦�� 
			if(isGameOver) drawOver(); // ��Ϸ����״̬ 
    		if(pauseFlag) drawPause(); // ��Ϸ��ͣ״̬ 
    		if(quitFlag) drawConfQuit();//��Ϸȷ���˳�״̬ 
   			if(restartFlag) drawConfRestart(); // ��Ϸȷ�����¿�ʼ״̬ 
			break;
	}
	
}

void drawReturn(){
	// �����ؼ� 
	if(button(GenUIID(123),PrimaryX+2.5*SquarLength,PrimaryY+3*SquarLength,2,0.4,"����")){
		nowMenuMode = unDefinedMenu;
		display();
		// ֻ��������ʱ�з��أ�����һ�����˻ص�δ��¼���˵� 
	}
}

void endInput(){
	if(strlen(results) == 0){
		strcpy(results,"blank");
	}
	int i;
	for(i=0;i<20;++i) userInfo.name[i] = results[i];
	userInfo.name[20] = '\0';
	if(inputMode == registerMode){ // �ж����������ע�ỹ���ڵ�¼ʱ���õ� 
		userInfo.gameCount = 0;
		userInfo.bestScore = 0;
		userInfo.rank = -1;
		userInfo.totScore = 0; // ��ʼ���û����� 
		saveToFile(); // �������� 
		nowMenuMode = definedMenu;
		isDefined = 1;
		drawMenuDefined();
	}else{
		loadAccount(); // ��ȡ���� 
		if(userInfo.rank != -2){ // ��ȡ�ɹ� 
			nowMenuMode = definedMenu;
			isDefined = 1;
			drawMenuDefined();	
		}else{ // ��ȡʧ�� 
			nowMenuMode = unDefinedMenu;
			drawMenuUndefined();
		}
	}
	
}

void logOut(){
	// ������ݣ��˻���һ��ҳ�� 
	userInfo.name[0] = '\0';
	userInfo.bestScore = -1;
	userInfo.gameCount = -1;
	userInfo.rank = -1;
	userInfo.totScore = -1;
	nowMenuMode = unDefinedMenu;
	isDefined = 0;
	drawMenuUndefined();
}

void openHelp(){
	puts("opening help");
	system("help.txt");// ���ð����ĵ� 
}
