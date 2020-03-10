#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;

FILE* fpr;
errno_t errr= fopen_s(&fpr, "input.txt", "r");//打开文件  只读
FILE* fpw;
errno_t errw= fopen_s(&fpw,"output.txt", "w");//打开或创建文件  用于写

const int maxn = 1e3;
int n, m, dis[maxn][maxn];//n顶点数 m边数 dis两点距离

void Floyd() {
    //cnt从小到大实现局部最优
    for (int cnt = 1; cnt <= n; cnt++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][cnt] + dis[cnt][j]);
}

int main()
{
    //初始化
    memset(dis, inf, sizeof dis);//距离初始化为很大的值

    //读取输入
    if (errr) {
        printf_s("fail to open the file!");
        exit(1);
    }
    else {
        fscanf_s(fpr, "%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
            dis[i][i] = 0;//自己到自己距离为0
        for (int i = 0; i < m; i++) {
            int u, v, w;
            fscanf_s(fpr, "%d %d %d", &u, &v, &w);
            dis[u][v] = w;
        }
    }

    Floyd();

    //输出txt
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fprintf_s(fpw, "%d %d %d\n", i, j, dis[i][j]);

    //关闭文件
    fclose(fpr);
    fclose(fpw);
}
