#ifndef COMPILE_LOG
#define COMPILE_LOG

static char buf[50] = "Log space";// �ַ������� 

/* 
 * ��������logON
 * ���ܣ���������ַ�����ʾ��״̬���� 
 * ������str - �������Ҫ��ʾ���ַ��� 
 */
void logON(char *str);

/* 
 * ��������clearLog
 * ���ܣ�����������ڵ��ַ� 
 */
void clearLog();

/* 
 * ��������flashLog
 * ���ܣ���ʾ�������ڵ��ַ� 
 */
void flashLog();

#endif
