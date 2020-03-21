#include <iostream>
using namespace std;

void merge(int a[],int left, int mid, int right,int temp[]) {
    int startA = left, startB = mid + 1,pos=1;        //startA、startB表示要归并的两段数组的开始下标  pos记录temp数组中的下标
    while (startA <= mid && startB <= right) {
        if (a[startA] < a[startB])                    //较小值存入temp数组
            temp[pos++]=a[startA++];
        else
            temp[pos++] = a[startB++];
    }

    //把两段数组（之一）剩余的数加在temp后
    while (startA<=mid)
        temp[pos++] = a[startA++];
    while (startB <= right)
        temp[pos++] = a[startB++];

    //更新原数组为归并后内容
    pos = 1;                                          //注意temp只存储了当前进行归并排序的数据
    for (int i = left; i <= right; i++)
        a[i] = temp[pos++];
}

void mergeSort(int a[], int left, int right,int temp[]) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(a, left, mid, temp);                //分治思想的体现
        mergeSort(a, mid + 1, right, temp);
        merge(a, left, mid, right, temp);             //归并排序后的两段数据
    }
}

int main()
{
    //下标从1开始
    int n = 8, a[9] = { 0,5,9,6,3,5,2,7,1 }, temp[9] = { 0 };

    cout << "排序前：";
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;

    mergeSort(a,1,n,temp);

    cout << "排序后：";
    for (int i = 1; i <= n; i++)
        cout << a[i] <<" ";
}
