#include "log.h"
#include "draw.h"
#include <string.h>

void logOn(char *str){
	clearLog(); // ɾ�ɵ� 
	strcpy(buf,str);
	flashLog(); // ���µ� 
}

void clearLog(){
	SetPenColor("White");// ͨ���ñ���ɫ��֮ǰ��������дһ�������� 
	MovePen(0.05,0.1);
	DrawTextString(buf);
}

void flashLog(){
	SetPenColor("Black");
	MovePen(0.05,0.1);
	DrawTextString(buf);// ���µ� 
}
