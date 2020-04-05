#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");

void select(vector<int> s,int n,int k) {

	vector<int> temp,m,s1, s2;
	temp = s;

	//把s划分成最多5个一组，并把每组的中位数放到集合m
	for (int i = 0; i < n; i += 5) {

		int len = min(5, n - i);
		sort(temp.begin() + i, temp.begin() + i+len);

		m.push_back(temp[i + (len-1)/2]);
		//temp.clear();		//清空元素，不回收空间
	}

	sort(m.begin(), m.end());	//中位数单独排序
	int cnt = m.size();
	int mmid = m[(cnt-1)/ 2];	//求出中位数的中位数m*

	//划分为ABCD，且S1=S1并C,S2=S2并B，AD中较小的放入S1，较大的放入S2
	for (int i = 0; i < n; i += 5) {

		//若该组不足5个，则直接遍历比较大小
		if (n - i < 5) {
			for (int j = i; j < n; j++) {
				if (temp[j] > mmid)
					s2.push_back(temp[j]);
				else if(temp[j]<mmid)
					s1.push_back(temp[j]);
			}
			break;
		}

		//该组个数为5个时
		if (temp[i + 2] < mmid) {	//该组中位数小于m*时
			for (int j = i; j <=i+2; j++)
				s1.push_back(temp[j]);
			for (int j = i + 3; j < i+5; j++) {
				if (temp[j] > mmid)
					s2.push_back(temp[j]);
				else s1.push_back(temp[j]);
			}
		}
		else if (temp[i + 2] > mmid) {	//该组中位数大于m*时
			for (int j = i; j <= i+2; j++) {
				if (temp[j] > mmid)
					s2.push_back(temp[j]);
				else s1.push_back(temp[j]);
			}
			for (int j = i + 3; j < i+5; j++)
				s2.push_back(temp[j]);
		}
		else {	//该中位数等于m*时   注意：m*不存入S1或S2，直接丢弃
			for (int j = i; j < i+2; j++)
				s1.push_back(temp[j]);

			for (int j = i + 3; j <i+5; j++)
				s2.push_back(temp[j]);
		}
	}

	int cnt1 = s1.size(), cnt2 = s2.size();
	if (k == cnt1+1) {
		cout << mmid << endl;
		return;
	}
	else if (k <= cnt1)
		select(s1, cnt1, k);
	else
		select(s2, cnt2, k - cnt1 - 1);
}

int main() {
	int n, k,a;			//n是5的倍数     k表示第k小元素
	vector<int>s;		//s存储数组
	fscanf_s(fpr, "%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		fscanf_s(fpr, "%d", &a);
		s.push_back(a);
	}

	//输出input.txt中的内容
	cout << "n=" << n << " k=" <<k<< endl;
	for (int i = 0; i < s.size(); i++)
		cout << s[i] << " ";

	//调用select函数输出结果
	cout << "\n第" << k << "小的数为：";
	select(s, n, k);
}
