#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "genlib.h"
#include "conio.h"
#include "game.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include "music.h"
#include "log.h"
  
void playBGM(){
	logOn("Play BGM");
	PlaySound(TEXT(".//res//background.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void pauseBGM(){
	PlaySound(NULL,NULL,NULL);
}
// ���������������ڲ������䡢������Ч 
// ������ʵ�ʲ����У����ֲ�ͬ�豸���ܻ���mciSendString����ʱ����
// �����Ƴ�������Ч���ܡ����� 
void playEliminate(){
	
//	if(mciSendString(TEXT("close \".//res//eliminate.wav\" "), NULL, 0, NULL))
//		mciSendString(TEXT("open \".//res//eliminate.wav\" "), NULL, 0, NULL);
//	else mciSendString(TEXT("open \".//res//eliminate.wav\" "), NULL, 0, NULL);
//	mciSendString(TEXT("play \".//res//eliminate.wav\" "),NULL,0,NULL);
}

void playDown(){
	
//	if(mciSendString(TEXT("close \".//res//down.wav\" "), NULL, 0, NULL))
//		mciSendString(TEXT("open \".//res//down.wav\" "), NULL, 0, NULL);
//	else mciSendString(TEXT("open \".//res//down.wav\" "), NULL, 0, NULL);
//	mciSendString(TEXT("play \".//res//down.wav\" "),NULL,0,NULL);
	
}
