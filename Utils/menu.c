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
	switch(nowMenuMode){ // 三种模式，配备三种处理模式 
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
					logOn("End input");// 回车结束 
					endInput();
					return ;
			}
			break;
	}	
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event); //GUI获取鼠标
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
			newUser(); // 新建 
			break;
		case 'a': case 'A':
			findUser(); // 打开 
			break;
		case 'h': case 'H':
			logOn("Open help");
			openHelp(); // 帮助 
			break;
		case 'q': case 'Q':
			ExitProcess(0); // 退出 
			break;
	}
}

void switchUserInfo(){
    if(isShowingInfo == 0){
			logOn("Switch to user information");
			drawUserInfo(); // 个人信息 
			isShowingInfo = 1;
		}else{
			logOn("Switch back");
			drawProducerInfo(); // 版权信息 
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
			StartIt(); // 开始游戏 
			break;
		case 'l': case 'L':
			logOn("Log out");
			logOut(); // 登出 
			break;
		case 'h': case 'H':
			logOn("Open help");
			openHelp(); // 帮助 
			break;
		case 'q': case 'Q':
			ExitProcess(0); // 退出 
			break;
		case 'u': case 'U':
			switchUserInfo(); // 用户信息 
			break;
		
	}
}

void solveInputing(char ch){
	uiGetChar(ch); // GUI字符输入
	logOn("Inputing");
	display(); //刷新显示
}

void startMenu(int x){
	// Menu 入口 
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
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    nowMenuMode = inputing;
    display();
}


// 文本编辑演示程序
void drawEditText()
{
	static char newnum[80] = "";
	static char firstName[80] = "";
	double fH = GetFontHeight();
	double h = fH*2; // 控件高度
	double w = winwidth/4; // 控件宽度
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
		drawLabel(x-fH/2-TextStringWidth("注册"), (y-=h*1.2)+fH*0.7, "注册");
	else
		drawLabel(x-fH/2-TextStringWidth("用户名"), (y-=h*1.2)+fH*0.7, "用户名");
	if( textbox(GenUIID(0), x, y, w, h, firstName, sizeof(firstName)) )
		sprintf(results,"%s", firstName);				/*(*^▽^*)*/ 
	drawLabel(x,y-=fH*1.2,newnum);
}

void display()
{
	// 刷新函数需要根据当前所处的模式来挑选自己的刷新方式 
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
			// 针对特殊状态特殊处理 
			if(isGameOver) drawOver(); // 游戏结束状态 
    		if(pauseFlag) drawPause(); // 游戏暂停状态 
    		if(quitFlag) drawConfQuit();//游戏确认退出状态 
   			if(restartFlag) drawConfRestart(); // 游戏确认重新开始状态 
			break;
	}
	
}

void drawReturn(){
	// 画返回键 
	if(button(GenUIID(123),PrimaryX+2.5*SquarLength,PrimaryY+3*SquarLength,2,0.4,"返回")){
		nowMenuMode = unDefinedMenu;
		display();
		// 只有在输入时有返回，所以一定是退回到未登录主菜单 
	}
}

void endInput(){
	if(strlen(results) == 0){
		strcpy(results,"blank");
	}
	int i;
	for(i=0;i<20;++i) userInfo.name[i] = results[i];
	userInfo.name[20] = '\0';
	if(inputMode == registerMode){ // 判断输入框是在注册还是在登录时调用的 
		userInfo.gameCount = 0;
		userInfo.bestScore = 0;
		userInfo.rank = -1;
		userInfo.totScore = 0; // 初始化用户数据 
		saveToFile(); // 保存数据 
		nowMenuMode = definedMenu;
		isDefined = 1;
		drawMenuDefined();
	}else{
		loadAccount(); // 读取数据 
		if(userInfo.rank != -2){ // 读取成功 
			nowMenuMode = definedMenu;
			isDefined = 1;
			drawMenuDefined();	
		}else{ // 读取失败 
			nowMenuMode = unDefinedMenu;
			drawMenuUndefined();
		}
	}
	
}

void logOut(){
	// 清除数据，退回上一级页面 
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
	system("help.txt");// 调用帮助文档 
}
