#ifndef COMPILE_RANK
#define COMPILE_RANK

typedef struct{ // 排行榜节点 
    char* name[22]; // 名字 
	int score; // 分数 
    struct List* next; // 下一个节点 
} List;

typedef struct{ // 排行榜 
    int totNum; // 总节点数 
    List* head; // 排行榜头指针 
} RankList;

RankList rankList;

/* 
 * 函数名：updateRankList
 * 功能： 更新排行榜数据 
 */
void updateRankList();

/* 
 * 函数名：insert
 * 功能： 将当前用户成绩插入到排行榜 
 */
void insert();

/* 
 * 函数名：erase
 * 功能： 将当前用户信息从排行榜移除 
 */
void erase();

/* 
 * 函数名：loadList 
 * 功能： 从文件中读取排行榜信息 
 */
void loadList();
#endif
