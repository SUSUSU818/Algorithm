#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_SIZE = 100;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");

int main() {
	int m, n,	//m万元  n项投资
		f[MAX_SIZE][MAX_SIZE],		//存储初始收益
		dp[MAX_SIZE][MAX_SIZE] = { 0 },		//记录局部最大收益
		invest[MAX_SIZE][MAX_SIZE];		//invest[]用于记录投资方案
	
	//读取输入
	fscanf_s(fpr, "%d %d", &m,&n);
	for (int i = 0; i <= m; i++)
		for (int j = 1; j <= n; j++)
			fscanf_s(fpr, "%d", &f[j][i]);

	//动态规划
	for (int k = 1; k <= n; k++) 
		for (int x = 1; x <= m; x++)
			for (int i = 0; i <= x; i++)
				if (dp[k - 1][x - i] + f[k][i] >= dp[k][x]) {
					dp[k][x] = dp[k - 1][x - i] + f[k][i];
					invest[k][x] = i;
				}


	//输出
	/*
	for (int x = 1; x <= m; x++) {
		for (int k = 1; k <= n; k++)
			cout << dp[k][x] << " "<<invest[k][x]<<" ";
		cout << endl;
	}
	*/

	cout <<"最大收益为："<< dp[n][m] << endl;
	cout << "分配方案为：\n";
	int sum = m;
	for (int i = n; i >= 1;i--) {
		cout << "分配给第" << i << "个项目" << invest[i][sum] << "万\n";
		sum -= invest[i][sum];
	}
}
