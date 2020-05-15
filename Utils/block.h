
#ifndef fuckyou
#define fuckyou

// 以下三数组为俄罗斯方块位置计算中间变量 
int Direction[16][2];
int BlockShape[8][4];
int BlockMod[8];

typedef struct { //  方块类 
    int x, y;     // 方块坐标 
    int direction;// 方块朝向 
    int type;     // 方块种类 
}Block;

/* 
 * 函数名：randomBlock
 * 功能：随机产生一个方块 
 * 返回值: Block - 随机产生的方块 
 */
Block randomBlock();

#endif
