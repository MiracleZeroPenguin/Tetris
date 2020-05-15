#ifndef INCLUDED
#define INCLUDED

typedef struct{ // 用户信息结构体 
    char name[22]; // 姓名 
    int gameCount; // 游戏次数 
    int totScore;  // 总得分 
    int bestScore; // 最高得分 
    int rank;      // 特殊状态标识 
} UserInfo;

static char path[50] = ".//saves//"; // 存档路径 
static char tmp[50]; 

UserInfo userInfo; // 定义当前用户 

/* 
 * 函数名：newAccount
 * 功能：新建用户，并作为当前用户  
 */
void newAccount(); 

/* 
 * 函数名：loadAccount
 * 功能：从文件中读取已有账户 
 */
void loadAccount();

/* 
 * 函数名：saveToFile
 * 功能：将当前用户信息保存 
 */
void saveToFile();

#endif
