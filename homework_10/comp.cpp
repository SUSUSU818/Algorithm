#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");

struct node{
	int s, f;
}t[maxn],ans[maxn];//t数组存储初始时间，ans存储使活动数量最多的时间安排

int cmp(const node& a, const node& b) {
	return a.f < b.f;
}

int main() {
	int n;
	fscanf_s(fpr, "%d", &n);
	for (int i = 1; i <= n; i++)
		fscanf_s(fpr, "%d %d", &t[i].s, &t[i].f);

	sort(t + 1, t + 1 + n, cmp);//按截止时间升序
	int k = 0;//最大的活动数量
	ans[++k] = t[1];
	for (int i = 2; i <= n; i++) {
		if (t[i].s >= ans[k].f)
			ans[++k] = t[i];
	}

	cout << "最大活动数量为：" << k << endl;
	cout << "安排的活动的起始和截止时间如下：\n";
	for (int i = 1; i <= k; i++)
		cout << ans[i].s << " " << ans[i].f << endl;
}
