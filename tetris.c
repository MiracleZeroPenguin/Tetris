//
//       ,___          .-;'
//       `"-.`\_...._/`.`
//    ,      \        /
// .-' ',    / ()   ()\					  һֻ��ªƤ�������ܰ��ʾ�� 
//`'._   \  /()    .  (|
//    > .' ;,     -'-  /
//   / <   |;,     __.;                   �����뿪���������� 
//   '-.'-.|  , \    , \				  �������������飡���� 
//      `>.|;, \_)    \_)				  
//       `-;     ,    /					  
//          \    /   <
//           '. <`'-,_)
//            '._)
//===========================================================================
//
//  ��Ȩ�����ߣ� (���ڲ���͸¶������Ϣ��ɾ��)
//				(���ڲ���͸¶������Ϣ��ɾ��)
//							�㽭��ѧ�������ѧ�뼼��ѧԺ
//
//  ���δ�����2019��5��20��
//  ����޸ģ�2019��5��31��
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
	InitGraphics(); // ��ʼ���������Ŀ� 
	//InitConsole(); // ����̨������� 
	// ͨ���������ֺ��������в��ԣ�ʹ���������뺯�� 
	TimerEventProcess(test);
	KeyboardEventProcess(test,test);
	CharEventProcess(test);
	MouseEventProcess(test,test,test,test);
	// ע�����ֻص����� 
	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
    startMenu(0); // �������˵� 
	return ;
}

