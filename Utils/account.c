#include <stdio.h>
#include "account.h"
#include "menu.h"
#include <string.h>
#include <windows.h>
#include "log.h"

void newAccount(){ // �½��˻�  
	userInfo.name[0] = '\0'; // ��ʼ�� 
	userInfo.bestScore = -1;
	userInfo.gameCount = -1;
	userInfo.rank = -2;
	userInfo.totScore = -1;
	printf("flag = %d\n",inputMode); // ������� 
	inputBox();
}

void loadAccount(){ // ��ȡ�˻� 
	strcpy(tmp,path);strcat(tmp,userInfo.name);strcat(tmp,".ter");
	logOn("loading saved file");
	printf("load save Filename is : %s\n",tmp);
	FILE* in = fopen(tmp,"rb"); // �򿪶������ļ� 
	if(in == NULL){ // ����Ҳ����浵 
		logOn("Can't find saves");
		MessageBox(NULL,"�Ҳ����浵","����",MB_OK);
		userInfo.rank = -2;
		return ;
	}
	fread(&(userInfo.gameCount),sizeof(int),1,in);// ��ȡ�浵 
	fread(&(userInfo.totScore),sizeof(int),1,in);
	fread(&(userInfo.bestScore),sizeof(int),1,in);
	fread(&(userInfo.rank),sizeof(int),1,in);
	logOn("saved");
	printf("data : count : %d\n tot : %d\n best: %d\n rank: %d\n",userInfo.gameCount,userInfo.totScore,userInfo.bestScore,userInfo.rank);
	fclose(in);
}

void saveToFile(){
	strcpy(tmp,path);strcat(tmp,userInfo.name);strcat(tmp,".ter");
	logOn("saving user file ...");
	printf("save to file with name: %s\n",tmp);
	FILE* out = fopen(tmp,"wb"); // �򿪶������ļ� 
	if(out == NULL){// �����ʧ�� 
		MessageBox(NULL,"д���浵�ļ�ʧ�ܣ������Ƿ�ʹ���˷Ƿ��ַ�","����",MB_OK);
		return ;
	}
	fwrite(&(userInfo.gameCount),sizeof(int),1,out); // д������ 
	fwrite(&(userInfo.totScore),sizeof(int),1,out);
	fwrite(&(userInfo.bestScore),sizeof(int),1,out);
	fwrite(&(userInfo.rank),sizeof(int),1,out);
	printf("data : count : %d\n tot : %d\n best: %d\n rank: %d\n",userInfo.gameCount,userInfo.totScore,userInfo.bestScore,userInfo.rank);
	logOn("End saving");
	fclose(out);
	return ;
}

