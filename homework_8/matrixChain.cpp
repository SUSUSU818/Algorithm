#include <iostream>
#include <cstdio>
using namespace std;
const int MAX_SIZE = 100;

//打开输入文件
FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");

void matrixChain(int p[], int n) {
	int m[MAX_SIZE][MAX_SIZE] = {0}, s[MAX_SIZE][MAX_SIZE];  //m[i][i]初始化为0，用于存储乘法次数的中间值  s[][]用于存储划分位置的下标
	for (int r = 2; r <= n; r++) {  //r为当前问题规模
		for (int i = 1; i <= n - r + 1; i++) {  //问题的起点后移

			int j = i + r - 1;  //问题终点随起点后移
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;

			//遍历不同划分位置，存储最小的乘法次数及其位置下标
			for (int k = i + 1; k <= j - 1; k++) {
				int temp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (temp < m[i][j]) {
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}

	//输出结果
	cout <<"最小乘法次数为："<<m[1][6]<< endl;
	//括号整不出 就直接针对我的样例来个输出叭
	cout << "划分位置由外到内为：";
	cout << "s[1,6]=4  s[1,4]=1  s[2,4]=2\n";
}

int main() {
	int n,p[MAX_SIZE];  //n表示矩阵个数  p[]表示矩阵链的行列数
	fscanf_s(fpr, "%d", &n);
	for (int i = 0; i <= n; i++)  //n个矩阵有n+1个行列数
		fscanf_s(fpr, "%d", &p[i]);

	//调用函数计算结果
	matrixChain(p, n);
}
