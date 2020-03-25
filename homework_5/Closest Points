#include <iostream>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;

FILE* fpr;
errno_t errr = fopen_s(&fpr, "input.txt", "r");//打开文件  只读

const int MAX_SIZE = 1000;

//点的坐标用结构体存储
struct node{
	double x, y;
}P[MAX_SIZE],Q[MAX_SIZE];

//求两点距离的平方的函数
double dis(node& a, node& b) {
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

//两个比较函数
int cmpx(node& a, node& b) {
	return a.x < b.x;
}

int cmpy(node& a, node& b) {
	return a.y < b.y;
}

//最近点对算法
double ecp(node P[], node Q[], int n) {

	double dminsq=inf;

	if (n <= 3) {	//蛮力算法
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i!=j)
					dminsq = min(dminsq, dis(P[i], P[j]));
			}
		}
	}
	else {	//分治策略
		node Pl[MAX_SIZE], Pr[MAX_SIZE], Ql[MAX_SIZE], Qr[MAX_SIZE],s[MAX_SIZE];	//l下标为左半段 r下标为右半段
		double m,dl,dr,d;
		int len1 = ceil(1.0*n / 2),len2,num=0;	//len1为左半段的元素个数  len2为右半段
		len2 = n - len1;

		//分成左右两段并复制到新结构体数组中  分治策略的体现
		for (int i = 0; i < len1; i++) {
			Pl[i] = P[i];
			Ql[i]= Q[i];
		}
		for (int i = 0; i < len2; i++) {
			Pr[i] = P[i];
			Qr[i] = Q[i];
		}

		//递归  求左右两段各自的最近点对
		dl = ecp(Pl, Ql, len1);
		dr = ecp(Pr, Qr, len2);
		d = min(dl, dr);
		dminsq = pow(d, 2);		//ecp函数返回的值是开方后的，平方后再参与比较
		m = P[len1 - 1].x;		//求分割线的x坐标值  用于检查位于分割线两侧是否存在更近的点对
	
		//将更近的点对存入s
		for (int i = 0; i < n; i++) {
			if (fabs(Q[i].x - m) < d)
				s[num++]= Q[i];
		}

		//求s中的最近点对和上面得到的dminsq两者的更小值
		for (int i = 0; i < num-1;i++) {
			int k = i + 1;
			while (k <= num - 1 && pow((s[k].y - s[i].y), 2)+pow((s[k].x - s[i].x), 2) < dminsq) {
				dminsq = min(pow((s[k].y - s[i].y), 2) + pow((s[k].x - s[i].x), 2), dminsq);
				k++;
			}
		}
	}
	return sqrt(dminsq);	//求出最小距离的平方后  最后来求平方根
}

int main() {
	int n;
	fscanf_s(fpr, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf_s(fpr, "%lf %lf", &P[i].x,&P[i].y);
		Q[i] = P[i];				//复制P到Q
	}

	sort(P, P + n, cmpx);  //P按x轴升序
	sort(Q, Q + n, cmpy);  //Q按y轴升序

	cout<<ecp(P, Q, n)<<endl;
}
