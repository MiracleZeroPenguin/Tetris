
#ifndef fuckyou
#define fuckyou

// ����������Ϊ����˹����λ�ü����м���� 
int Direction[16][2];
int BlockShape[8][4];
int BlockMod[8];

typedef struct { //  ������ 
    int x, y;     // �������� 
    int direction;// ���鳯�� 
    int type;     // �������� 
}Block;

/* 
 * ��������randomBlock
 * ���ܣ��������һ������ 
 * ����ֵ: Block - ��������ķ��� 
 */
Block randomBlock();

#endif
