#include "log.h"
#include "draw.h"
#include <string.h>

void logOn(char *str){
	clearLog(); // 删旧的 
	strcpy(buf,str);
	flashLog(); // 换新的 
}

void clearLog(){
	SetPenColor("White");// 通过用背景色把之前的字重新写一遍来消除 
	MovePen(0.05,0.1);
	DrawTextString(buf);
}

void flashLog(){
	SetPenColor("Black");
	MovePen(0.05,0.1);
	DrawTextString(buf);// 画新的 
}
