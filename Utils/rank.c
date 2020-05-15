#include "rank.h"
#include "account.h"
#include "draw.h"
#include "log.h"
#include <stdio.h>
#include <windows.h>

void insert(){
	puts("inserting in list");
	logOn("Adding new record");
	printf("it has %d Info before insert\n",rankList.totNum);
    List *tmp = (List*)malloc(sizeof(List));
    tmp->score = userInfo.bestScore;
	strcpy(tmp->name,userInfo.name);
	tmp->next = NULL;
	puts("ready to insert");
    if(rankList.head == NULL) rankList.head = tmp; // ͷָ��Ϊ�� 
    else{
        if(userInfo.bestScore > rankList.head->score){// �����Ϊͷָ�� 
            tmp->next = rankList.head;
            rankList.head = tmp;
            puts("insert in first one");
        }else{ // �������ط����� 
            List *i = rankList.head->next;
            List *j = rankList.head;
            while(1){
                if(i == NULL || userInfo.bestScore > i->score){
                    j->next = tmp;
                    tmp->next = i;
                    if(i != NULL) printf("insert before %s",i->name);
                    else puts("insert in the end");
					break;
                }
                i = i->next;
                j = j->next;
            }
        }
    }
    rankList.totNum ++;
	puts("insert ended");
	printf("now list has %d info\n",rankList.totNum);
}

void erase(){
    if(rankList.head == NULL) return ;
    puts("deleting old records");
	if(strcmp(rankList.head->name,userInfo.name) == 0){// ɾ��ͷ 
        List *it = rankList.head;
        rankList.head = rankList.head->next;
        free(it);
        rankList.totNum --;
        return ;
    }
    List *i = rankList.head->next;
    List *j = rankList.head;
    for(;i != NULL;i = i->next,j = j->next){
        if(strcmp(i->name,userInfo.name) == 0){ // �ҵ� 
        	printf("delete %s %d\n",i->name,i->score);
            j->next = i->next;
            rankList.totNum--;
			break;
        }
	}
    puts("deleting ended");
}

void saveList(){
	logOn("Save changes");
	FILE *out = fopen("list.log","wb"); // �����а���Ϣ�ļ� 
	if(out == NULL){// ��ʧ�� 
		MessageBox(NULL,"�������а���Ϣʧ�ܣ����鵱ǰĿ¼д��Ȩ��","����",MB_OK);
		return ;
	}
	puts("start saving ranklist infomation");
	List* head = rankList.head;
	int n;
	if(head == NULL) n = 0;
	else n = rankList.totNum; // ��ȡ���а��ܸ��� 
	printf("tot player : %d\n",n);
	fwrite(&n,sizeof(int),1,out);
	List *i = head;
	for(;i != NULL;i = i->next){ // ������а���Ϣ 
		printf("saving : %s %d\n",i->name,i->score);
		fwrite(&(i->name),sizeof(i->name),1,out);
		fwrite(&(i->score),sizeof(int),1,out);
	}
	fclose(out);
	puts("saving ended");
	return ;
}

void loadList(){
	logOn("Load datas");
	rankList.head = NULL;
	rankList.totNum = 0;
	FILE *in = fopen("list.log","rb");
	if(in == NULL) return ; // �Ҳ����浵��Ϣ��ֱ���½����а� 
	puts("start to load List information");
	fread(&rankList.totNum,sizeof(int),1,in); // ��ȡ���� 
	printf("tot player = %d\n",rankList.totNum);
	if(rankList.totNum == 0) return ;
	rankList.head = (List*)malloc(sizeof(List));
	List *it = rankList.head;
	fread(&(it->name),sizeof(it->name),1,in); // ��ȡ��һ�� 
	fread(&(it->score),sizeof(int),1,in);
	printf("loading %s %d\n",it->name,it->score);
	it->next = NULL;
	int i;
	for(i=2;i<=rankList.totNum;++i){ // ��ȡʣ������ 
		List *tmp = (List*)malloc(sizeof(List));
		fread(&(tmp->name),sizeof(tmp->name),1,in);
		fread(&(tmp->score),sizeof(int),1,in);
		printf("loading %s %d\n",tmp->name,tmp->score);
		it->next = tmp;tmp->next = NULL;
		it = tmp;
	}
	puts("load end");
	return ;
}

void updateRankList(){ // ʹ�õ�ǰ�û����ݸ������а� 
	erase(); // ɾ�������� 
	insert(); // ��������� 
	saveList(); // ���� 
}

