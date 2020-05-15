#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxSize = 100;

typedef struct Node
{
	int weight,parent,lchild, rchild;   
}HTNode, * HfTree;  
typedef char** HfCode;  

HfTree create_HfTree(int* w, int n);
void select(HfTree HT, int k, int& min1, int& min2);
int min(HfTree HT, int k);
void HfCoding(HfTree HT, HfCode& HC, int n);

int main()
{
	//初始化
	int n=8,w[] = { 5,5,10,10,10,15,20,25 };//w为每个字符的权重
	char s[] = "abcdefgh";
	HfCode HC = NULL;
	HfTree hTree = create_HfTree(w, n);

	//调用哈夫曼编码
	HfCoding(hTree, HC, n);

	//输出字符对应的编码
	printf("从根结点到叶子结点编码结果为：\n");
	for (int i = 0; i < n; ++i) {
		printf("%c—%s\n",s[i], HC[i]);
	}
}

//构造哈夫曼树
HfTree create_HfTree(int* w, int n)
{
	int total = 2 * n - 1;
	HfTree HT = (HfTree)malloc(total * sizeof(HTNode));

	int i;
	for (i = 0; i < n; i++)
	{
		HT[i].parent =HT[i].lchild = HT[i].rchild = -1;
		HT[i].weight = *w;
		w++;
	}
	for (; i < total; i++)
	{
		HT[i].parent = HT[i].lchild = HT[i].rchild = -1;
		HT[i].weight = 0;
	}

	int min1, min2;//用于保存每次循环选出的两个weight最小且parent为0的节点
	for (i = n; i < total; i++)
	{
		select(HT, i, min1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}
	return HT;
}

//从HT的前k个元素中选出两个weight最小且parent为-1的节点
void select(HfTree HT, int k, int& min1, int& min2)
{
	min1 = min(HT, k);
	min2 = min(HT, k);
}

//从HT的前k个元素中选出weight最小且parent为-1的节点，返回其下标
int min(HfTree HT, int k)
{
	int i = 0,mini,min_weight;
  
	while (HT[i].parent != -1)
		i++;
	min_weight = HT[i].weight;
	mini = i;
 
	for (; i < k; i++)
	{
		if (HT[i].weight < min_weight && HT[i].parent == -1)
		{
			min_weight = HT[i].weight;
			mini = i;
		}
	}
 
	HT[mini].parent = 1;

	return mini;
}

//求哈夫曼编码
void HfCoding(HfTree HT, HfCode& HC, int n)
{
	HC = (HfCode)malloc(n * sizeof(char*));
	char* code = (char*)malloc(n * sizeof(char));
	int cur = 2 * n - 2,code_len = 0;  

	for (int i = 0; i < cur + 1; i++)
	{
		HT[i].weight = 0;
	}
  
	while (cur != -1)
	{
		if (HT[cur].weight == 0)
		{
			HT[cur].weight = 1;
			if (HT[cur].lchild != -1)
			{  
				code[code_len++] = '0';
				cur = HT[cur].lchild;
			}
			else
			{   
				code[code_len] = '\0';
				HC[cur] = (char*)malloc((code_len + 1) * sizeof(char));
				if (!HC[cur])
				{
					printf("HC[cur] malloc faild!");
					exit(-1);
				}
				strcpy(HC[cur], code);
			}
		}
		else if (HT[cur].weight == 1)
		{
			HT[cur].weight = 2; 
			if (HT[cur].rchild != -1)
			{ 
				code[code_len++] = '1';
				cur = HT[cur].rchild;
			}
		}
		else
		{
			HT[cur].weight = 0;
			cur = HT[cur].parent;
			--code_len;
		}
	}
	free(code);
}
