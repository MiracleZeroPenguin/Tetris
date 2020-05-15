#ifndef INCLUDED
#define INCLUDED

typedef struct{ // �û���Ϣ�ṹ�� 
    char name[22]; // ���� 
    int gameCount; // ��Ϸ���� 
    int totScore;  // �ܵ÷� 
    int bestScore; // ��ߵ÷� 
    int rank;      // ����״̬��ʶ 
} UserInfo;

static char path[50] = ".//saves//"; // �浵·�� 
static char tmp[50]; 

UserInfo userInfo; // ���嵱ǰ�û� 

/* 
 * ��������newAccount
 * ���ܣ��½��û�������Ϊ��ǰ�û�  
 */
void newAccount(); 

/* 
 * ��������loadAccount
 * ���ܣ����ļ��ж�ȡ�����˻� 
 */
void loadAccount();

/* 
 * ��������saveToFile
 * ���ܣ�����ǰ�û���Ϣ���� 
 */
void saveToFile();

#endif
