#include <iostream>
#include <cstdio>

using namespace std;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");

FILE* fpw;
errno_t errw = fopen_s(&fpw, "output.txt", "w");

int n, m,a = 1, b = 1,cnt;
int graph[20][20],color[20];

bool check(int x) {
    for (int i = 1; i <= n; i++)
        if (graph[x][i] && color[x] == color[i])
            return false;
    return true;
}

void backtrack(int cur) {
    if (cur > n) {
        for (int i = 1; i <= n; i++)
            fprintf_s(fpw,"%d ", color[i]);
        cnt++;
        fprintf_s(fpw,"\n");
    }
    else {
        for (int i = 1; i <= m; i++) {
            color[cur] = i;
            if (check(cur))
                backtrack(cur + 1);
            color[cur] = 0;
        }
    }
}

int main()
{
    fscanf_s(fpr, "%d %d", &n, &m);
    while (fscanf_s(fpr,"%d %d", &a, &b) != EOF && a && b)
        graph[a][b] = graph[b][a] = 1;
    backtrack(1);
    if (cnt)fprintf_s(fpw, "Total=%d\n", cnt);
    else fprintf_s(fpw, "NO\n");
    cout << "程序结束，请在output.txt中查看结果\n";
    return 0;
}
