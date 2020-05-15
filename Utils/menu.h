#ifndef COMPILE_MENU
#define COMPILE_MENU

#define unDefinedMenu 0
#define definedMenu 1
#define inputing 2
#define playing 3

#define registerMode 1
#define loginMode 2

int isShowingInfo; // 是否正在显示用户信息 

static int isDefined = 0; // 用户是否登录 
static int nowMenuMode; // 当前菜单模式 （未登录、登录、输入中、游戏中） 
static int inputMode; // 输入模式（注册输入、登录输入） 
static double winwidth, winheight;   // 窗口尺寸
static char results[200] = ""; // 输入字符储存 

/* 
 * 函数名：newUser 
 * 功能：新建用户 
 */
void newUser();

/* 
 * 函数名：findUser 
 * 功能：使用已有用户 
 */
void findUser();

/* 
 * 函数名：CharEventForMenu 
 * 功能： 接受分发的面对菜单及其功能的字符信息并处理 
 * 参数: ch - 字符信息 
 */
void CharEventForMenu(char ch);

/* 
 * 函数名：solveDefined 
 * 功能： 接受分发的面对已登录菜单的字符信息并处理 
 * 参数: ch - 字符信息 
 */
void solveDefined(char ch);

/* 
 * 函数名：solveUndefined 
 * 功能： 接受分发的面对未登录菜单的字符信息并处理 
 * 参数: ch - 字符信息 
 */
void solveUndefined(char ch);

/* 
 * 函数名：solveInputing
 * 功能： 接受分发的面对输入中的字符信息并处理 
 * 参数: ch - 字符信息 
 */
void solveInputing(char ch);

/* 
 * 函数名：KeyboardEventForMenu
 * 功能： 接受分发的面对输入过程的键盘信息并处理 
 * 参数: key - 是按下还是松开 
 *       event - 所按键位 
 */
void KeyboardEventForMenu(int key,int event);

/* 
 * 函数名：startMenu
 * 功能： 显示菜单、并进行初始化 
 * 参数: x - 启动的菜单模式 (0 :未登录模式 || 1 : 已登录模式) 
 */
void startMenu(int x);

/* 
 * 函数名：inputBox
 * 功能： 显示输入界面、并进行相关初始化 
 */
void inputBox();

/* 
 * 函数名：display 
 * 功能： 对当前界面进行刷新 
 */
void display();

/* 
 * 函数名：endInput 
 * 功能： 与 inputBox结合使用，用于结束输入 
 */
void endInput();

/* 
 * 函数名：logOut 
 * 功能： 登出当前用户 
 */
void logOut();

/* 
 * 函数名：openHelp 
 * 功能： 打开帮助文档 
 */
void openHelp();

/* 
 * 函数名：switchUserInfo 
 * 功能： 切换用户信息显示状态 
 */
void switchUserInfo();

/* 
 * 函数名：drawReturn 
 * 功能： 绘制返回按钮 
 */
void drawReturn();
#endif
