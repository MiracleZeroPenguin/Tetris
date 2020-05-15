
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "extgraph.h"
#include "block.h"

//��ʽ���� 
int Direction[16][2] = {
        {0,  0},{-1, 0},{-2, 0},{-1, 1},
        {0,  0},{0,  1},{0,  2},{1,  1},
        {0,  0},{1,  0},{2,  0},{1,  -1},
        {0,  0},{0,  -1},{0,  -2},{-1, -1}
};
int BlockShape[8][4] = {
        {0, 0, 0,  0},{0, 1, 9,  10},{0, 1, 3,  9},{0, 1, 9,  7},
        {0, 9, 11, 13},{0, 1, 5,  7},{0, 1, 5,  9},{0, 3, 5,  9}
};
int BlockMod[8] = {1, 2, 4, 4, 1, 4, 4, 4};

Block randomBlock(){ // ���ש�� 
    static int inited = 0;
    if(inited == 0){
        inited = 1;
        srand(time(NULL)); // �趨������� 
    }
    Block ret;
    ret.type = rand() % 8 + 1;
    if(ret.type == 8) ret.type = 1;
    switch(ret.type){ // �������ɵķ������ͣ�����΢����У׼����λ�� 
		case 1:
			ret.direction = 1;
			ret.x = 0;
			ret.y = 1; 
			break;
		case 4:
			ret.direction = 0;
			ret.x = -1;
			ret.y = 1;
			break;
		default:
			ret.direction = 0;
			ret.x = ret.y = 0;
	}
    return ret;
}
