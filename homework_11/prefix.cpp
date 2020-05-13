#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define maxSize 100

typedef struct Node
{
	int weight;       
	int parent;            
	int lchild, rchild;   
}HTNode, * HuffmanTree;  
typedef char** HuffmanCode;  

HuffmanTree create_HuffmanTree(int* w, int n);
void select_min(HuffmanTree HT, int k, int& min1, int& min2);
int min(HuffmanTree HT, int k);
void HuffmanCoding(HuffmanTree HT, HuffmanCode& HC, int n);
int main()
{
	int n=5,w[] = { 35,10,20,20,15 };

	HuffmanCode HC = NULL;
	HuffmanTree hTree = create_HuffmanTree(w, n);

	printf("从根结点到叶子结点编码结果为：\n");
	HuffmanCoding(hTree, HC, n);
}

HuffmanTree create_HuffmanTree(int* w, int n)
{
	int total = 2 * n - 1;
	HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
	{
		printf("HuffmanTree malloc faild!");
		exit(-1);
	}
	int i;

	for (i = 0; i < n; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = *w;
		w++;
	}
 
	for (; i < total; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = 0;
	}

	int min1, min2;
	for (i = n; i < total; i++)
	{
		select_min(HT, i, min1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}
	return HT;
}

void select_min(HuffmanTree HT, int k, int& min1, int& min2)
{
	min1 = min(HT, k);
	min2 = min(HT, k);
}

int min(HuffmanTree HT, int k)
{
	int i = 0,min,min_weight;
  
	while (HT[i].parent != -1)
		i++;
	min_weight = HT[i].weight;
	min = i;
 
	for (; i < k; i++)
	{
		if (HT[i].weight < min_weight && HT[i].parent == -1)
		{
			min_weight = HT[i].weight;
			min = i;
		}
	}
 
	HT[min].parent = 1;

	return min;
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode& HC, int n)
{
	HC = (HuffmanCode)malloc(n * sizeof(char*));
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
	for (int i = 0; i < n; ++i) {
		printf("%s\n", HC[i]);
	}
	free(code);
}
