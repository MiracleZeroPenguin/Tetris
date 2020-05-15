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
    if(rankList.head == NULL) rankList.head = tmp; // 头指针为空 
    else{
        if(userInfo.bestScore > rankList.head->score){// 插入后为头指针 
            tmp->next = rankList.head;
            rankList.head = tmp;
            puts("insert in first one");
        }else{ // 在其他地方插入 
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
	if(strcmp(rankList.head->name,userInfo.name) == 0){// 删除头 
        List *it = rankList.head;
        rankList.head = rankList.head->next;
        free(it);
        rankList.totNum --;
        return ;
    }
    List *i = rankList.head->next;
    List *j = rankList.head;
    for(;i != NULL;i = i->next,j = j->next){
        if(strcmp(i->name,userInfo.name) == 0){ // 找到 
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
	FILE *out = fopen("list.log","wb"); // 打开排行榜信息文件 
	if(out == NULL){// 打开失败 
		MessageBox(NULL,"储存排行榜信息失败，请检查当前目录写入权限","错误",MB_OK);
		return ;
	}
	puts("start saving ranklist infomation");
	List* head = rankList.head;
	int n;
	if(head == NULL) n = 0;
	else n = rankList.totNum; // 获取排行榜总个数 
	printf("tot player : %d\n",n);
	fwrite(&n,sizeof(int),1,out);
	List *i = head;
	for(;i != NULL;i = i->next){ // 输出排行榜信息 
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
	if(in == NULL) return ; // 找不到存档信息，直接新建排行榜 
	puts("start to load List information");
	fread(&rankList.totNum,sizeof(int),1,in); // 读取个数 
	printf("tot player = %d\n",rankList.totNum);
	if(rankList.totNum == 0) return ;
	rankList.head = (List*)malloc(sizeof(List));
	List *it = rankList.head;
	fread(&(it->name),sizeof(it->name),1,in); // 读取第一个 
	fread(&(it->score),sizeof(int),1,in);
	printf("loading %s %d\n",it->name,it->score);
	it->next = NULL;
	int i;
	for(i=2;i<=rankList.totNum;++i){ // 读取剩余所有 
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

void updateRankList(){ // 使用当前用户数据更新排行榜 
	erase(); // 删除旧数据 
	insert(); // 添加新数据 
	saveList(); // 保存 
}

