//
//       ,___          .-;'
//       `"-.`\_...._/`.`
//    ,      \        /
// .-' ',    / ()   ()\					  一只丑陋皮卡丘的温馨提示： 
//`'._   \  /()    .  (|
//    > .' ;,     -'-  /
//   / <   |;,     __.;                   评测请开音量！！！ 
//   '-.'-.|  , \    , \				  求求大家手下留情！！！ 
//      `>.|;, \_)    \_)				  
//       `-;     ,    /					  
//          \    /   <
//           '. <`'-,_)
//            '._)
//===========================================================================
//
//  版权所有者： (由于不能透露个人信息已删除)
//				(由于不能透露个人信息已删除)
//							浙江大学计算机科学与技术学院
//
//  初次创建：2019年5月20日
//  最近修改：2019年5月31日
//
//===========================================================================



#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#define test 233666

void Main(){
	InitGraphics(); // 初始化这个神奇的库 
	//InitConsole(); // 控制台调试输出 
	// 通过调用四种函数来进行测试，使编译器编译函数 
	TimerEventProcess(test);
	KeyboardEventProcess(test,test);
	CharEventProcess(test);
	MouseEventProcess(test,test,test,test);
	// 注册四种回调函数 
	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
    startMenu(0); // 启动主菜单 
	return ;
}

