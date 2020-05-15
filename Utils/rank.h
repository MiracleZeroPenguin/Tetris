#ifndef COMPILE_RANK
#define COMPILE_RANK

typedef struct{ // ���а�ڵ� 
    char* name[22]; // ���� 
	int score; // ���� 
    struct List* next; // ��һ���ڵ� 
} List;

typedef struct{ // ���а� 
    int totNum; // �ܽڵ��� 
    List* head; // ���а�ͷָ�� 
} RankList;

RankList rankList;

/* 
 * ��������updateRankList
 * ���ܣ� �������а����� 
 */
void updateRankList();

/* 
 * ��������insert
 * ���ܣ� ����ǰ�û��ɼ����뵽���а� 
 */
void insert();

/* 
 * ��������erase
 * ���ܣ� ����ǰ�û���Ϣ�����а��Ƴ� 
 */
void erase();

/* 
 * ��������loadList 
 * ���ܣ� ���ļ��ж�ȡ���а���Ϣ 
 */
void loadList();
#endif
