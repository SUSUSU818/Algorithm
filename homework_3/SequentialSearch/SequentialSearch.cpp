#include <iostream>
using namespace std;

const int MAXN = 1e3;
int n, a[MAXN],cnt;

//找到第一个x并输出其下标
void sequenSearch(int x) {
	//遍历查找x
	int i=0;
	for (i = 1; i <= n; i++) {
		if (a[i] == x) {
			cout << i << endl;
			break;
		}
	}
	if (i == n+1)
		cout << "0" << endl;
}

int main() {
	//输入
	cout << "请输入数组个数：";
	cin >> n;

	cout << "请输入数组元素：";
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	cout << "请输入查找次数：";
	cin >> cnt;

	while (cnt--) {
		int x;
		cout << "请输入要查找的数：";
		cin >> x;
		sequenSearch(x);
	}
}
