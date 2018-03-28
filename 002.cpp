
#include <io.h> 
#include <stdio.h> 
#include"string.h"
#include<iostream>
#include <sys/stat.h>
#include <unistd.h>

#define N 100

typedef struct Route{
	
	char e[N][N];						//存储 0/1 串（某字符的哈夫曼编码逆序）
	int top;
	
}Route;								//用于哈夫曼编码临时存储的栈 

//栈的初始化 
int InitRoute(Route &RT){
	
	RT.top=0;
} 

//压栈 
void Push(Route &RT,char x[]){
	
	strcpy(RT.e[RT.top],x);
	RT.top++;
}

//弹栈 
int Pop(Route &RT){
	
	if(RT.top==0)	return 0;
	//strcpy(x,RT.e[RT.top-1]);
	RT.top--;
	return 1;
}


int stchar(char filename[])
{

	FILE *fp = NULL;

	int numchar = 0,numline=0,numword=0,wordlong=0;
	char word[100]={0};
	

	if ((fp = fopen(filename, "r")) == NULL)

	{

		printf("文件打开失败..\n");

		return 0;

	}

	while (!feof(fp)) {
		int ch=0;

		ch=fgetc(fp);
		
		if((ch>=65&&ch<=90)||(ch>=97&&ch<=122))
		{
			word[wordlong]=ch;
			//printf("%d%c",ch,word[numword]);
			wordlong++;
		}
			
		else if(ch>=48&&ch<=57&&wordlong>=4)
		{
			word[wordlong]=ch;
			wordlong++;
		}
		else if(word!="\0"&&wordlong>=4)
		{
			//printf("%s\n",word);
			numword++;
			word[0]=0;
			while(wordlong)
			{
				word[wordlong]=0;
				wordlong--;
			}
			
			wordlong=0;
		}
		else
		{
			word[0]=0;
			while(wordlong)
			{
				word[wordlong]=0;
				wordlong--;
			}
			
			wordlong=0;
		}
		
		//printf("%d\t",numword);
		//printf("%c",ch);

		numchar++;
		
		if (ch==10)
		
			numline++;

	}
	numchar=numchar-1;
	numline=numline+1;
	printf("\n %s 文件中共有字符个数: %d\t行数：%d\t\t单词数：%d\n\n", filename, numchar,numline,numword);

	fclose(fp);

	return 0;

}



void printDir(char path[])

{

	struct _finddata_t data;
	struct Route RT;
	char fileaddr[200];
	char filename[200];
	char filepath[200];
	strcpy(fileaddr,path);
	strcpy(filename,path);
	strcpy(filepath,path);
	InitRoute(RT);
	Push(RT,fileaddr);

	strcat(fileaddr, "\\*.*");
	//printf("\n\n%s\t%s\t%s\n\n",path,fileaddr,filename);
	
	while(RT.top!=0){
		
		struct stat st;
		
		strcpy(filepath,RT.e[RT.top-1]);
		printf("\n\n\t+++%s+++\n\n",filepath);
		strcpy(fileaddr,RT.e[RT.top-1]);
		
		stat(fileaddr,&st);
		if (S_ISDIR(st.st_mode))
		strcat(fileaddr, "\\*.*");
		else
			stchar(fileaddr);
		//printf("\n%s\n\n",fileaddr);
			Pop(RT);
		long hnd = _findfirst(fileaddr, &data);    // 查找文件名与正则表达式chRE的匹配第一个文件 

	if (hnd < 0)

	{

		perror(fileaddr);

	}

	int  nRet = (hnd <0) ? -1 : 1;

	while (!(_findnext(hnd, &data))&nRet>0)

	{
		

		if (data.attrib == _A_SUBDIR)  // 如果是目录 
		{
			
			if(strcmp(data.name,".")==0||strcmp(data.name,"..")==0)
				continue;
			printf("   [文件夹：%s]*\n", data.name);
			strcpy(filename,filepath);
			strcat(filename,"\\");
			strcat(filename,data.name);

			Push(RT,filename);
			
			//printf("\n%s\n",RT.e[RT.top-1]);
		}


		else
		{
			//printf("%s",data.name);
			strcpy(filename,filepath);
			strcat(filename,"\\");
			strcat(filename,data.name);
			stchar(filename);
		}

		//nRet = _findnext(hnd, &data);

	}

	_findclose(hnd);     // 关闭当前句柄 
	
	}
	

}

int main()

{

	printDir("G:\\VS project\\test1");

}
