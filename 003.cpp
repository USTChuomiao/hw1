
#include <io.h> 
#include <stdio.h> 
#include"string.h"
#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include"stdlib.h"

#define N 100

int snumchar=0,snumline=0,snumword=0;



typedef struct Route{
	
	char e[N][N];						
	int top;
	
}Route;							

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


typedef struct Hash{
	char data[3]={0};
	struct Node *next;
}Hash;

typedef struct Node{
	char dword[200]={0};
	int times=0;
	struct Node *next;
}Node;

void Hasht(Hash HT[],char word[])
{
	int i,HTnum=0;
	Node *p=NULL,*q=NULL,*l=NULL;
	
	//for(i=0;i<676;i++)
	//printf("%s\n",HT[i].data);
	
	if (word[0]>=97&&word[0]<=122) 
		HTnum+=(word[0]-97)*26;
	else if(word[0]>=65&&word[0]<=90)
		HTnum+=(word[0]-65)*26;
		
	if (word[1]>=97&&word[1]<=122) 
		HTnum+=word[1]-97;
	else if(word[1]>=65&&word[1]<=90)
		HTnum+=word[1]-65;	
	
	//printf("\n%d\n",HTnum);
	//printf("%d\n",HT[HTnum].next==NULL);
	
	
	if (HT[HTnum].next==NULL)
	{
		p=(Node*)malloc(sizeof(Node));
		strcpy(p->dword,word);
		p->times=1;
		p->next=NULL;
		HT[HTnum].next=p;
		p=NULL;
		free(p);
	}
	else
	{
		p=(Node*)malloc(sizeof(Node));
		q=(Node*)malloc(sizeof(Node));
		p=HT[HTnum].next;
		q=p->next;
		if (q==NULL)	
			if (strcasecmp(word,p->dword)>0)
			{
				l=(Node*)malloc(sizeof(Node));
				strcpy(l->dword,word);
				l->times=1;
				l->next=NULL;
				p->next=l;
				p=NULL;
				q=NULL;
				l=NULL;
				free(p);
				free(q);
				free(l);
			}	
			else if (strcasecmp(word,p->dword)==0)
			{
				if (strcmp(word,p->dword)>=0)
				{
					p->times=p->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
					
				else
				{
					strcpy(p->dword,word);
					p->times=p->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
				
			}
			else
			{
				l=(Node*)malloc(sizeof(Node));
				strcpy(l->dword,word);
				l->times=1;
				l->next=p;
				HT[HTnum].next=l;
				p=NULL;
				q=NULL;
				l=NULL;
				free(p);
				free(q);
				free(l);
			}
		while (q!=NULL)
		{
			if (strcasecmp(word,q->dword)>0)
			{
				p=q;
				q=q->next;
				if (q==NULL)
				{
					l=(Node*)malloc(sizeof(Node));
					strcpy(l->dword,word);
					l->times=1;
					l->next=NULL;
					p->next=l;
					p=NULL;
					q=NULL;
					l=NULL;
					free(p);
					free(q);
					free(l);
				}
			}
			else if (strcasecmp(word,q->dword)==0)
			{
				if (strcmp(word,p->dword)>=0)
				{
					q->times=q->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
					
				else
				{
					strcpy(q->dword,word);
					q->times=q->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
			}
			else if (strcasecmp(word,q->dword)<0&&strcasecmp(word,p->dword)>0)
			{
				l=(Node*)malloc(sizeof(Node));
				strcpy(l->dword,word);
				l->times=1;
				l->next=q;
				p->next=l;
				p=NULL;
				q=NULL;
				l=NULL;
				free(p);
				free(q);
				free(l);
			}
			else if (strcasecmp(word,p->dword)==0)
			{
				if (strcmp(word,p->dword)>=0)
				{
					p->times=p->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
					
				else
				{
					strcpy(p->dword,word);
					p->times=p->times+1;
					p=NULL;
					q=NULL;
					free(p);
					free(q);
				}
			}
			else
			{
				l=(Node*)malloc(sizeof(Node));
				strcpy(l->dword,word);
				l->times=1;
				l->next=HT[HTnum].next;
				HT[HTnum].next=l;
				p=NULL;
				q=NULL;
				l=NULL;
				free(p);
				free(q);
				free(l);
				
			}
		}
		
	}
	//printf("%s\n",HT[HTnum].next->dword);		
}


int stchar(char filename[],Hash HT[])
{

	FILE *fp = NULL;

	int numchar = 0,numline=0,numword=0,wordlong=0;
	char word[200]={0};
	

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
			Hasht(HT,word);
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

		if (ch!='\n'&&ch!='\0')
			
			numchar++;
		
		if (ch==10)
		
			numline++;

	}
	numchar=numchar-1;
	numline=numline+1;
	printf("\n %s 文件中共有字符个数: %d\t行数：%d\t\t单词数：%d\n\n", filename, numchar,numline,numword);

	fclose(fp);

	snumchar+=numchar;
	snumline+=numline;
	snumword+=numword;

	return 0;

}



void printDir(char path[],Hash HT[])

{
	int filenum=0;
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
		{
			stchar(fileaddr,HT);
			filenum++;
		}

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
			stchar(filename,HT);
			filenum++;
		}

		//nRet = _findnext(hnd, &data);

	}

	_findclose(hnd);     // 关闭当前句柄 
	
	}
	
	printf("\n****文件总数：%d\t",filenum);

}

int main()

{
	Hash HT[676];
	Node *p=NULL;
	p=(Node*)malloc(sizeof(Node));
	int i=0;
	for (i=0;i<676;i++)
	{
		HT[i].data[0]=97+i/26;
		HT[i].data[1]=97+(i%26);
		HT[i].next=NULL;
	}
	
	printDir("G:\\VS project\\test1",HT);
	
	printf("字符总数：%d\t总行数：%d\t单词总数：%d\n",snumchar,snumline,snumword);

	for (i=0;i<676;i++)
	{
		p=HT[i].next;
		while (p!=NULL)
		{
			printf("\n%-20s\t%d\n",p->dword,p->times);
			p=p->next;
		}
	}
		

	//printf("\n%s\t%d\n",HT[0].next->dword,HT[0].next->times);
	//printf("\n%s\t%d\n",HT[0].next->next->dword,HT[0].next->next->times);
}
