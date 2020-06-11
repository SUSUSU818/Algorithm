#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

const int MAX_SIZE=100;
int N;
double minlen = 10000, x[MAX_SIZE], r[MAX_SIZE];//分别为最小圆排列长度，每个圆心横坐标，每个圆半径
double bestr[MAX_SIZE];//最小圆排列的半径顺序

double center(int t)//得到每个圆的圆心坐标
{
	double temp = 0;
	for (int j = 1; j < t; ++j)//因为目标圆有可能与排在它之前的任一圆相切，故需一一判断
	{
		double xvalue = x[j] + 2.0 * sqrt(r[t] * r[j]);
		if (xvalue > temp)
			temp = xvalue;
	}
	return temp;
}
void compute()
{
	double low = 0, high = 0;
	for (int i = 1; i < N; ++i)
	{
		if (x[i] - r[i] < low)
			low = x[i] - r[i];
		if (x[i] + r[i] > high)
			high = x[i] + r[i];
	}
	if (high - low < minlen)
	{
		minlen = high - low;
		for (int i = 1; i < N; ++i)
			bestr[i] = r[i];
	}
}
void backtrack(int t)
{
	if (t == N)
	{
		compute();
		return;
	}
	for (int j = t; j < N; ++j)
	{
		swap(r[t], r[j]);
		double centerx = center(t);
		if (centerx + r[t] + r[1] < minlen)
		{
			x[t] = centerx;
			backtrack(t + 1);
		}
		swap(r[t], r[j]);
	}
}
int main()
{
	ifstream inFile;
	inFile.open("input.txt");
	inFile >> N;
	N++;
	for (int i = 1; i < N; i++)
		inFile >> r[i];

	ofstream outFile;
	outFile.open("output.txt");
	outFile << "每个圆的半径分别为：";
	for (int i = 1; i < N; ++i)
		outFile << r[i] << ' ';
	outFile << endl;

	//回溯法求最短圆排列
	backtrack(1);

	outFile << "最小圆排列长度为：" << minlen << endl;
	outFile << "最优圆排列的顺序对应的半径分别为：";
	for (int i = 1; i < N; ++i)
		outFile<<bestr[i] << " ";

	cout << "运行成功！\n请在output.txt文件中查看结果" << endl;
	return 0;
}
