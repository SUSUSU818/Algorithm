#include <iostream>
using namespace std;

const int MAXN = 1e3;
int n, a[MAXN], cnt;

void BinarySearch(int x) {
	int l=1, r=n, mid,flag=0;
	while (l <= r) {
		mid = (l + r) / 2;
		if (a[mid] < x)l = mid + 1;
		else if (a[mid] > x)r = mid-1;
		else {
			cout << mid << endl;
			flag = 1;//标记x存在
			break;
		}
	}
	if (!flag)
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
		BinarySearch(x);
	}
}
