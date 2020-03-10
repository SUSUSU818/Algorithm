#include <iostream>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;

const int maxn = 1e5;
int n, m, cnt=0,fa[maxn];

//结构体存储边的信息
struct edge {
    int u, v, w;
}a[maxn];

int cmp(const edge &a, const edge &b) {
    return a.w < b.w;
}

/*并查集  确保不成*/
//找父亲
int find(int x) {
    return fa[x] == x ? x : find(fa[x]);
}

//合并
void merge(int x,int y) {
    fa[find(y)] = find(x);
}

void kruskal() {
    //按边权重从小到大排序
    sort(a, a + m, cmp);

    //按权重从小到大遍历
    for (int i = 0; i < m; i++) {
        if (cnt == n - 1)break;//如果边数==n-1就退出
        if (find(a[i].u) != find(a[i].v)) {
            merge(a[i].u, a[i].v);
            cout << "v"<<a[i].u << "----v" << a[i].v << endl;//输出边
            cnt++;
        }
    }
}

int main()
{
    //初始化
    clr(a, inf);

    //输入
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> a[i].u >> a[i].v >> a[i].w;

    //初始化 每个顶点的父亲是自己
    for (int i = 0; i < n; i++)fa[i] = i;

    //调用函数构造最小生成树
    kruskal();
}
