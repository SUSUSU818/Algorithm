#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define inf 0x3f3f3f3f 
using namespace std;

const int maxn = 1e3;
int n, m, dis[maxn][maxn], vis[maxn];
vector<int>mst;//用于存储最小生成树的顶点

void prim() {
	int minn = inf,u,v;
	for (int i = 0; i < mst.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (!vis[j]) {
				if (minn > dis[mst[i]][j]) {
					minn = dis[mst[i]][j];
					u = mst[i], v = j;
				}
			}
		}
	}

	//将遍历所得的与mst中的顶点相连的权重最小的顶点放入最小生成树
	mst.push_back(v);
	vis[v] = 1;
	cout << "v"<<u << "----v" << v << endl;//输出边

	//当所有顶点都在最小生成树中时，程序才会停止
	if(mst.size()<n)prim();
}

int main() {
	//初始化
	clr(dis, inf);

	//输入
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		dis[u][v] = dis[v][u] = w;
	}

	/*开始构造最小生成树*/
	//从顶点v0开始迭代  即先将v0放入最小生成树的顶点集合
	mst.push_back(0);
	vis[0] = 1;//vis[i]=1用来标记该顶点已在最小生成树中
	prim();
}
