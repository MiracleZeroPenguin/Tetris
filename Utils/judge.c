#include "game.h"
#include "judge.h"
#include "block.h"

int judgeInter(GameInfo gameInfo){ // 碰撞判断 
    Block x = gameInfo.current;
    int dir = x.direction % BlockMod[x.type];
    int i;
	for (i = 0; i < 4; ++i) {
        int tx = x.x + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][0];
        int ty = x.y + Direction[(BlockShape[x.type][i] + 4 * dir) % 16][1];
        if (tx <= 0 || tx >= 11) return 0;// 判断下落方块是否出界 
        if (ty <= 0) return 0;
        if (gameInfo.map[tx][ty]) return 0;// 判断下落方块是否与其他方块相交 
    }
    return 1;
}
