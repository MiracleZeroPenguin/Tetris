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
// 以下两个函数用于播放下落、消除音效 
// 但是在实际测试中，发现不同设备可能会在mciSendString播放时死机
// 于是移除播放音效功能。。。 
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
