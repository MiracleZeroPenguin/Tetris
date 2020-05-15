#ifndef COMPILE_LOG
#define COMPILE_LOG

static char buf[50] = "Log space";// 字符缓冲区 

/* 
 * 函数名：logON
 * 功能：将传入的字符串显示在状态栏中 
 * 参数：str - 传入的需要显示的字符串 
 */
void logON(char *str);

/* 
 * 函数名：clearLog
 * 功能：清除缓冲区内的字符 
 */
void clearLog();

/* 
 * 函数名：flashLog
 * 功能：显示缓冲区内的字符 
 */
void flashLog();

#endif
