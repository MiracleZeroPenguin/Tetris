#include <stdio.h>
#include "account.h"
#include "menu.h"
#include <string.h>
#include <windows.h>
#include "log.h"

void newAccount(){ // 新建账户  
	userInfo.name[0] = '\0'; // 初始化 
	userInfo.bestScore = -1;
	userInfo.gameCount = -1;
	userInfo.rank = -2;
	userInfo.totScore = -1;
	printf("flag = %d\n",inputMode); // 调试输出 
	inputBox();
}

void loadAccount(){ // 读取账户 
	strcpy(tmp,path);strcat(tmp,userInfo.name);strcat(tmp,".ter");
	logOn("loading saved file");
	printf("load save Filename is : %s\n",tmp);
	FILE* in = fopen(tmp,"rb"); // 打开二进制文件 
	if(in == NULL){ // 如果找不到存档 
		logOn("Can't find saves");
		MessageBox(NULL,"找不到存档","错误",MB_OK);
		userInfo.rank = -2;
		return ;
	}
	fread(&(userInfo.gameCount),sizeof(int),1,in);// 读取存档 
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
	FILE* out = fopen(tmp,"wb"); // 打开二进制文件 
	if(out == NULL){// 如果打开失败 
		MessageBox(NULL,"写出存档文件失败，请检查是否使用了非法字符","错误",MB_OK);
		return ;
	}
	fwrite(&(userInfo.gameCount),sizeof(int),1,out); // 写入数据 
	fwrite(&(userInfo.totScore),sizeof(int),1,out);
	fwrite(&(userInfo.bestScore),sizeof(int),1,out);
	fwrite(&(userInfo.rank),sizeof(int),1,out);
	printf("data : count : %d\n tot : %d\n best: %d\n rank: %d\n",userInfo.gameCount,userInfo.totScore,userInfo.bestScore,userInfo.rank);
	logOn("End saving");
	fclose(out);
	return ;
}

