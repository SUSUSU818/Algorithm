#include <iostream>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");//打开文件  只读
FILE* fpw;
errno_t errw = fopen_s(&fpw, "output.txt", "w");//打开或创建文件

const int maxn = 1e3;
int n, m, mp[maxn][maxn],dis[maxn],vis[maxn];

int Dijkstra(int u) {
    //将u行的数据存储在dis中
    for (int i = 1; i <= n; i++)
        dis[i] = mp[u][i];
    vis[1] = 1;

    for (int i = 1; i <= n; i++) {
        int minn = inf, minn_pos=-1;
        //找出剩下的最短距离
        for (int j = 1; j <= n; j++)
            if (!vis[j] && dis[j] < minn) {
                minn = dis[j];
                minn_pos = j;//记录剩下的最近的点
            }

        //标记该点已被加入中转点集合
        vis[minn_pos] = 1;

        //更新距离
        for (int j = 1; j <= n; j++)
            dis[j] = min(dis[j], mp[minn_pos][j] + dis[minn_pos]);

    }

    return dis[n];
}

int main()
{
    //初始化
    memset(mp,inf, sizeof mp);

    if (errr) {
        printf_s("fail to open the file!");
        exit(1);
    }
    else {
        fscanf_s(fpr, "%d %d", &n, &m);

        //自己到自己距离为0
        for (int i = 1; i <= n; i++)
            mp[i][i] = 0;

        for (int i = 1; i <= m; i++) {
            int u, v, w;
            fscanf_s(fpr, "%d %d %d", &u, &v, &w);
            mp[u][v] = w;
        }
    }

    //1代表a
    int ans=Dijkstra(1);

    //输出txt
    fprintf_s(fpw, "a到h的最短路径为%d\n", ans);

    //关闭文件
    fclose(fpr);
    fclose(fpw);
}
