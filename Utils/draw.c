#include "draw.h"
#include "block.h"
#include "game.h"
#include "graphics.h"
#include "account.h"
#include "rank.h"
#include "log.h"
#include "imgui.h"
#include "menu.h"

void drawProducerInfo(); 
 
void drawGameGUI(){
	flashLog();
	SetPenColor("Black");
	DrawASquar(PrimaryX+12*SquarLength,PrimaryY+14*SquarLength,5*SquarLength,6*SquarLength) ;/*next输出位置*/
	DrawASquar(PrimaryX-7*SquarLength,PrimaryY+14*SquarLength,5*SquarLength,6*SquarLength) ;/*former输出位置*/
	MovePen(PrimaryX+13*SquarLength,PrimaryY+13*SquarLength) ;
	DrawTextString("NEXT BLOCK");
	MovePen(PrimaryX-7*SquarLength,PrimaryY+13*SquarLength) ;
	DrawTextString("FORMER BLOCK");
	MovePen(PrimaryX-7*SquarLength,PrimaryY+10*SquarLength);
	DrawTextString("STOP/START: [P]");
	MovePen(PrimaryX-7*SquarLength,PrimaryY+8*SquarLength);
	DrawTextString("RESTART: [R]");
	MovePen(PrimaryX-7*SquarLength,PrimaryY+6*SquarLength);
	DrawTextString("VOICE ON/OFF: [M]");
	MovePen(PrimaryX-7*SquarLength,PrimaryY+4*SquarLength);
	DrawTextString("QUIT: [Q]");
	/*GAME CONTENT*/
	MovePen(PrimaryX+12*SquarLength,PrimaryY+10*SquarLength);
	DrawTextString("NAME:");DrawTextString(userInfo.name);
	MovePen(PrimaryX+12*SquarLength,PrimaryY+8*SquarLength);
	DrawTextString("LEVEL:");drawTextInt(gameInfo.level);
	MovePen(PrimaryX+12*SquarLength,PrimaryY+6*SquarLength);
	DrawTextString("Eliminated Rows:");drawTextInt(gameInfo.totLines);
	MovePen(PrimaryX+12*SquarLength,PrimaryY+4*SquarLength);
	DrawTextString("HIGHEST SCORE:");drawTextInt(userInfo.bestScore);
	SetPenColor("Dark Gray");
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			DrawASquar(PrimaryX+i*SquarLength,PrimaryY+j*SquarLength,SquarLength,SquarLength);
		}
	}
	// next方块的绘制 
	Block x = gameInfo.next;
	int dir = x.direction % BlockMod[x.type];
    for (i = 0; i < 4; i++) {
        int pos_x = nextPosX + x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
        int pos_y = nextPosY + x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
        PaintSquar(pos_x,pos_y,x.type);
    }
    // hold 方块的绘制 
    x = gameInfo.hold;
    if(x.type){
		int dir = x.direction % BlockMod[x.type];
	    int i;
	    for (i = 0; i < 4; i++) {
	        int pos_x = holdPosX + x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
	        int pos_y = holdPosY + x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
	        PaintSquar(pos_x,pos_y,x.type);
	    }
	}
	drawMenuList();
}

void drawMenuList(){
	static char *menuListFile[] = {
            "File",
            "Save  (Ctrl-S)",
            "Load  (Ctrl-O)",
            "Exit  (Ctrl+E)",
			"Back  (Q)"};
    static char *menuListTool[] = {
            "Tool",
            "BGM   (N)",
            "Restart  (R)",
            "Pause  (P)"};
    static char *menuListHelp[] = {
            "Help",
            "About"};
    
    double x = PrimaryX - 10*SquarLength;
    double y = PrimaryY + 21.7*SquarLength;
    double h = SquarLength;
    double w = SquarLength*34/3;
    double wlist = SquarLength*26/3;
    // File 
    int selection = menuList(GenUIID(111), x, y - h, w, wlist, h, menuListFile,4);
    
    switch(selection){
		case 1:
			logOn("saved");
    	    saveGame();
    		break;
		case 2:
			logOn("load");
	    	if(loadGame()) display();
	    	else logOn("Load failed");
			break;
		case 3:
			ExitProcess(0);
			break;
	}
    // Tool
    selection = menuList(GenUIID(222), x + w, y - h, w, wlist, h, menuListTool,4);
    switch(selection){
        case 1:
        	modifyBGM();
            break;
        case 2:
        	restartIt();
            break;
        case 3:
            pauseIt();
			break;
        default:
            break;
    }
    // Help
    selection = menuList(GenUIID(333), x + 2 * w, y - h, w, wlist, h, menuListHelp,2);
	switch (selection){
		case 1:
			system("about.txt");
			break;
	}
}

void drawProducerInfo(){			/*o(╥﹏╥)o a new one*/
	SetPenColor("White");
	fillRectangle(PrimaryX+11*SquarLength, PrimaryY+SquarLength,15*SquarLength, 9*SquarLength);
	SetPenColor("Black");
	MovePen(PrimaryX+13*SquarLength,PrimaryY+8*SquarLength);
	DrawTextString("Copyright information");
	MovePen(PrimaryX+13*SquarLength,PrimaryY+7*SquarLength);
	DrawTextString("Producer:");
	MovePen(PrimaryX+14*SquarLength,PrimaryY+6*SquarLength);
	DrawTextString("Miracle_Zero"); // 由于不能透露个人信息。。。 
	MovePen(PrimaryX+14*SquarLength,PrimaryY+5*SquarLength);
	DrawTextString("Sky_Miner"); // 由于不能透露个人信息。。。 
	MovePen(PrimaryX+13*SquarLength,PrimaryY+4*SquarLength);
	DrawTextString("Production time:");
	MovePen(PrimaryX+14*SquarLength,PrimaryY+3*SquarLength);
	DrawTextString("2019.5.20-2019.5.27");
	MovePen(PrimaryX+13*SquarLength,PrimaryY+2*SquarLength);
	DrawTextString("If there are similarities");
	MovePen(PrimaryX+15*SquarLength,PrimaryY+1*SquarLength);
	DrawTextString("that's all.");
}

void drawTitle(){		/*o(╥﹏╥)o a new one*/
	// 这玩意闪的人眼瞎。。。 
	PaintSquar(-5,19,rand()%7+1);PaintSquar(-4,19,rand()%7+1);PaintSquar(-3,19,rand()%7+1);
	PaintSquar(-4,18,rand()%7+1);PaintSquar(-4,17,rand()%7+1);PaintSquar(-4,16,rand()%7+1);PaintSquar(-4,15,rand()%7+1);
	
	PaintSquar(-1,19,rand()%7+1);PaintSquar(0,19,rand()%7+1);PaintSquar(1,19,rand()%7+1);
	PaintSquar(-1,17,rand()%7+1);PaintSquar(0,17,rand()%7+1);PaintSquar(1,17,rand()%7+1);
	PaintSquar(-1,15,rand()%7+1);PaintSquar(0,15,rand()%7+1);PaintSquar(1,15,rand()%7+1);
	PaintSquar(-1,18,rand()%7+1);PaintSquar(-1,16,rand()%7+1);
	
	PaintSquar(3,19,rand()%7+1);PaintSquar(4,19,rand()%7+1);PaintSquar(5,19,rand()%7+1);
	PaintSquar(4,18,rand()%7+1);PaintSquar(4,17,rand()%7+1);PaintSquar(4,16,rand()%7+1);PaintSquar(4,15,rand()%7+1);
	
	PaintSquar(7,19,rand()%7+1);PaintSquar(8,19,rand()%7+1);PaintSquar(9,19,rand()%7+1);
	PaintSquar(7,17,rand()%7+1);PaintSquar(8,17,rand()%7+1);PaintSquar(9,17,rand()%7+1);
	PaintSquar(7,16,rand()%7+1);PaintSquar(8,16,rand()%7+1);
	PaintSquar(7,18,rand()%7+1);PaintSquar(7,15,rand()%7+1);PaintSquar(9,15,rand()%7+1);PaintSquar(9,18,rand()%7+1);
	
	PaintSquar(11,19,rand()%7+1);PaintSquar(12,19,rand()%7+1);PaintSquar(13,19,rand()%7+1);
	PaintSquar(11,15,rand()%7+1);PaintSquar(12,15,rand()%7+1);PaintSquar(13,15,rand()%7+1);
	PaintSquar(12,18,rand()%7+1);PaintSquar(12,17,rand()%7+1);PaintSquar(12,16,rand()%7+1);
	
	PaintSquar(15,19,rand()%7+1);PaintSquar(16,19,rand()%7+1);PaintSquar(17,19,rand()%7+1);PaintSquar(18,19,rand()%7+1);
	PaintSquar(15,17,rand()%7+1);PaintSquar(16,17,rand()%7+1);PaintSquar(17,17,rand()%7+1);
	PaintSquar(15,15,rand()%7+1);PaintSquar(16,15,rand()%7+1);PaintSquar(17,15,rand()%7+1);PaintSquar(18,15,rand()%7+1);
	PaintSquar(15,18,rand()%7+1);PaintSquar(18,16,rand()%7+1);
} 

void DrawASquar(double x,double y, double dx, double dy){
	MovePen(x,y);
	DrawLine(dx,0);
	DrawLine(0,dy);
	DrawLine(-dx,0);
	DrawLine(0,-dy); 
}	
	
void PaintSquar(int Newx,int Newy,int colortype){
	double x,y;
	switch(colortype){
		case 1:SetPenColor("Color1");break;
		case 2:SetPenColor("Color2");break;
		case 3:SetPenColor("Color3");break;
		case 4:SetPenColor("Color4");break;
		case 5:SetPenColor("Color5");break;
		case 6:SetPenColor("Color6");break;
		case 7:SetPenColor("Color7");break;
		case 8:SetPenColor("Color8");break;
		case 9:SetPenColor("Color9");break;
		case 0:SetPenColor("White");break;
	}
	x=(double)Newx*1.0;
	y=(double)Newy*1.0;
	x=PrimaryX+(x-1)*SquarLength*1.0;
	y=PrimaryY+(y-1)*SquarLength*1.0;
    fillRectangle(x,y,SquarLength,SquarLength);

}

void fillRectangle(double x, double y, double w, double h)
{
    MovePen(x, y);
    StartFilledRegion(0.5); // 开始
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    EndFilledRegion();   // 结束
}

void drawGame(GameInfo gameInfo){
	DisplayClear();
	drawGameGUI();
	int i,j;
	for(i=1;i<=10;++i) for(j=1;j<=20;++j){
		if(gameInfo.map[i][j] != 0) PaintSquar(i,j,gameInfo.map[i][j]);
	}
	Block x = gameInfo.current;
	int dir = x.direction % BlockMod[x.type];
    for (i = 0; i < 4; i++) {
        int pos_x = x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
        int pos_y = x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
        if(1 <= pos_x && pos_x <= 10 && pos_y <= 20 && pos_y >= 1){
			PaintSquar(pos_x,pos_y,x.type);
		}
    }
}

void drawOver(){
	int i,j;
	for(i=3;i<=8;i++){
		for(j=10;j<=14;j++){
			PaintSquar(i,j,0);
		}
	}
	SetPenColor("Red");
	SetPenSize(GetPenSize()*3);
	MovePen(PrimaryX+2*SquarLength,PrimaryY+9*SquarLength);
	DrawLine(6*SquarLength,0);
	DrawLine(0,5*SquarLength);
	DrawLine(-(6*SquarLength),0);
	DrawLine(0,-(5*SquarLength)); 
	MovePen(PrimaryX+3.5*SquarLength,PrimaryY+11.5*SquarLength);
	DrawTextString("GAME OVER");
	SetPenSize(GetPenSize()/3);
}

void drawPause(){
	int i,j;
	for(i=3;i<=8;i++){
		for(j=10;j<=14;j++){
			PaintSquar(i,j,0);
		}
	}
	SetPenColor("Red");
	SetPenSize(GetPenSize()*3);
	MovePen(PrimaryX+2*SquarLength,PrimaryY+9*SquarLength);
	DrawLine(6*SquarLength,0);
	DrawLine(0,5*SquarLength);
	DrawLine(-(6*SquarLength),0);
	DrawLine(0,-(5*SquarLength)); 
	MovePen(PrimaryX+2.2*SquarLength,PrimaryY+11.5*SquarLength);
	DrawTextString("Pause |press [P] to start|");
	SetPenSize(GetPenSize()/3);
}

void drawMenuUndefined(){		/*(*^▽^*)*/

	DisplayClear();
	flashLog();
	drawBackground();
	drawProducerInfo();
	drawRankingList();
	drawTitle();
//	SetPenColor("Black"); 
	MovePen(PrimaryX+13*SquarLength,PrimaryY+11*SquarLength);
	DrawTextString("Sorry, you haven't logged in yet.");
//	
//	MovePen(PrimaryX+2.5*SquarLength,PrimaryY+9*SquarLength);
//	DrawTextString("NEW USER: W   LOG IN: A");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+6*SquarLength);
//	DrawTextString("HELP: H");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+5*SquarLength);
//	DrawTextString("EXIT: Q");
	MovePen(PrimaryX-5*SquarLength,PrimaryY-1*SquarLength);
	DrawTextString("If you want to achieve some function, press the corresponding shortcut key on the keyboard.");

	
	if(button(GenUIID(111),PrimaryX+2.5*SquarLength,PrimaryY+9*SquarLength,2,0.4,"新建用户 (W)")){
		newUser();
		return ;
	}
	
	if(button(GenUIID(222),PrimaryX+2.5*SquarLength,PrimaryY+7*SquarLength,2,0.4,"打开游戏用户 (A)")){
		findUser();
		return ;
	}
	
	if(button(GenUIID(333),PrimaryX+2.5*SquarLength,PrimaryY+5*SquarLength,2,0.4,"帮助 (H)")){
		logOn("Open help");
		openHelp();
		return ;
	}
	
	if(button(GenUIID(444),PrimaryX+2.5*SquarLength,PrimaryY+3*SquarLength,2,0.4,"退出 (H)")){
		ExitProcess(0);
	}

}

void drawMenuDefined(){		/*(*^▽^*)*/ 
	DisplayClear();
	flashLog();
	drawBackground();
	if(!isShowingInfo) drawProducerInfo();
	else drawUserInfo();
	drawTitle();
	drawRankingList();
//	SetPenColor("Black"); 
	MovePen(PrimaryX+13*SquarLength,PrimaryY+11*SquarLength);
	DrawTextString("Hello, ");DrawTextString(userInfo.name);DrawTextString(" !");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+17*SquarLength);
////	DrawTextString("MENU");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+10*SquarLength);
//	DrawTextString("START: S");
//	MovePen(PrimaryX+3*SquarLength,PrimaryY+13*SquarLength);
//	//DrawTextString("RANKING LIST:XXX");
//	MovePen(PrimaryX+3*SquarLength,PrimaryY+8*SquarLength);
//	DrawTextString("USER INFORMATION: U");
//	MovePen(PrimaryX+3.5*SquarLength,PrimaryY+9*SquarLength);
//	//DrawTextString("PRESERVE:XXX");
//	MovePen(PrimaryX+4.5*SquarLength,PrimaryY+7*SquarLength);
//	DrawTextString("LOG OUT: L");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+6*SquarLength);
//	DrawTextString("HELP: H");
//	MovePen(PrimaryX+5*SquarLength,PrimaryY+5*SquarLength);
//	DrawTextString("EXIT: Q");
	MovePen(PrimaryX-5*SquarLength,PrimaryY-1*SquarLength);
	DrawTextString("If you want to achieve some function, press the corresponding shortcut key on the keyboard.");
	if(button(GenUIID(111),PrimaryX+2.5*SquarLength,PrimaryY+9*SquarLength,2,0.4,"开始游戏 (S)")){
		StartIt();
		return ;
	}
	
	if(button(GenUIID(222),PrimaryX+2.5*SquarLength,PrimaryY+7*SquarLength,2,0.4,"个人信息 (U)")){
		switchUserInfo();
		//return ;
	}
	
	if(button(GenUIID(333),PrimaryX+2.5*SquarLength,PrimaryY+5*SquarLength,2,0.4,"登出 (L)")){
		logOn("Log out");
		logOut();
		return ;
	}
	
	if(button(GenUIID(444),PrimaryX+2.5*SquarLength,PrimaryY+3*SquarLength,2,0.4,"帮助 (H)")){
		logOn("Open help");
		openHelp();
		return ;
	}
	
	if(button(GenUIID(555),PrimaryX+2.5*SquarLength,PrimaryY+1*SquarLength,2,0.4,"退出 (H)")){
		ExitProcess(0);
	}
}
void drawTextInt(int num_int){
	char str_int[30];
    itoa(num_int, str_int, 10);  //把整数num_int转成字符串str_int
	DrawTextString(str_int);
}

void drawConfRestart(){
	int i,j;
	for(i=3;i<=8;i++){
		for(j=10;j<=14;j++){
			PaintSquar(i,j,0);
		}
	}
	SetPenColor("Red");
	SetPenSize(GetPenSize()*3);
	MovePen(PrimaryX+2*SquarLength,PrimaryY+9*SquarLength);
	DrawLine(6*SquarLength,0);
	DrawLine(0,5*SquarLength);
	DrawLine(-(6*SquarLength),0);
	DrawLine(0,-(5*SquarLength)); 
	MovePen(PrimaryX+2.4*SquarLength,PrimaryY+11.5*SquarLength);
	DrawTextString("确定要重新开始吗(y/n)");
	SetPenSize(GetPenSize()/3);
}

void drawConfQuit(){
	int i,j;
	for(i=3;i<=8;i++){
		for(j=10;j<=14;j++){
			PaintSquar(i,j,0);
		}
	}
	SetPenColor("Red");
	SetPenSize(GetPenSize()*3);
	MovePen(PrimaryX+2*SquarLength,PrimaryY+9*SquarLength);
	DrawLine(6*SquarLength,0);
	DrawLine(0,5*SquarLength);
	DrawLine(-(6*SquarLength),0);
	DrawLine(0,-(5*SquarLength)); 
	MovePen(PrimaryX+2.4*SquarLength,PrimaryY+11.5*SquarLength);
	DrawTextString("确定返回主菜单吗(y/n)");
	SetPenSize(GetPenSize()/3);
}

void drawRankingList(){		/*(*^▽^*)*/ 
	SetPenColor("Black"); 
	int i,j;
	for(i=-8;i<=0;i++){
		PaintSquar(i,12,8);
		PaintSquar(i,10,8);
		PaintSquar(i,8,8);
		PaintSquar(i,6,8);
		PaintSquar(i,4,8);
		PaintSquar(i,2,8);

		PaintSquar(i,11,9);
		PaintSquar(i,9,9);
		PaintSquar(i,7,9);
		PaintSquar(i,5,9);
		PaintSquar(i,3,9);

	}
	SetPenColor("Black");
	MovePen(PrimaryX-8.6*SquarLength,PrimaryY+11.3*SquarLength);
	DrawTextString("USER NAME");
	MovePen(PrimaryX-4.5*SquarLength,PrimaryY+11.3*SquarLength);
	DrawTextString("SCORE");
	MovePen(PrimaryX-1.7*SquarLength,PrimaryY+11.3*SquarLength);
	DrawTextString("RANK");
	List * it = rankList.head;
	for(i=1;i<=10;i++){
		MovePen(PrimaryX-8.6*SquarLength,PrimaryY+(11.3-i)*SquarLength);
		if(it == NULL) DrawTextString("USER NAME");
		else DrawTextString(it->name);
		MovePen(PrimaryX-4.5*SquarLength,PrimaryY+(11.3-i)*SquarLength);
		if(it == NULL) DrawTextString("SCORE");
		else drawTextInt(it->score);
		MovePen(PrimaryX-1.2*SquarLength,PrimaryY+(11.3-i)*SquarLength);
		drawTextInt(i);
		if(it != NULL) it = it->next;
	}
}

void drawBackground(){		/*(*^▽^*)just change the color*/
	SetPenColor("Color7");
	int i;
	for(i=0;i<=20;i++){
		MovePen(PrimaryX+(0.5*i+1)*SquarLength,PrimaryY);
		DrawLine((5-0.25*i)*SquarLength,(5-0.25*i)*SquarLength);
	}
	SetPenColor("Color8");
	SetPenSize(GetPenSize()*2);
	for(i=0;i<=9;i++){
		MovePen(PrimaryX+11*SquarLength,PrimaryY+(5-0.5*i)*SquarLength);
		DrawLine(-(5+0.25*i)*SquarLength,(5+0.25*i)*SquarLength);
	}
	for(i=-1;i<=9;i++){
		MovePen(PrimaryX+(3.5+0.25*i)*SquarLength,PrimaryY+(3+0.25*i)*SquarLength);
		DrawLine(-2.25*SquarLength,2.25*SquarLength);
	}
	for(i=0;i<=8;i++){
		MovePen(PrimaryX+(0.25*i+1)*SquarLength,PrimaryY+(0.5+0.25*i)*SquarLength);
		DrawLine(-(0.25*i)*SquarLength,(0.25*i)*SquarLength);
	}
	SetPenSize(GetPenSize()/2);
	drawProducerInfo(); 
} 

void drawUserInfo(){
	SetPenColor("White");
	fillRectangle(PrimaryX+11*SquarLength, PrimaryY+1*SquarLength,15*SquarLength, 9*SquarLength);
	SetPenColor("Black");
	MovePen(PrimaryX+13*SquarLength,PrimaryY+8*SquarLength);
	DrawTextString("Personal information");
	MovePen(PrimaryX+13*SquarLength,PrimaryY+7*SquarLength);
	DrawTextString("NAME:");DrawTextString(userInfo.name);
	MovePen(PrimaryX+13*SquarLength,PrimaryY+6*SquarLength);
	DrawTextString("PLAYED TIMES:");drawTextInt(userInfo.gameCount);
	MovePen(PrimaryX+13*SquarLength,PrimaryY+5*SquarLength);
	DrawTextString("Total elimination:");drawTextInt(userInfo.totScore);
	MovePen(PrimaryX+13*SquarLength,PrimaryY+4*SquarLength);
	DrawTextString("Best elimination:");drawTextInt(userInfo.bestScore);
}
