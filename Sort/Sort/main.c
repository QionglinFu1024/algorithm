//
//  main.c
//  Sort
//
//  Created by Qionglin Fu on 2019/1/8.
//  Copyright © 2019 Qionglin Fu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#pragma mark 冒泡排序
/**
 冒泡排序

 @param arr 要排序的数组
 @param count 数组长度
 */
void bubble_sort(int arr[],int count)
{
    int i,j,temp;
    for (i = 0 ; i < count -1; i++)
    {
        for (j = 0; j < count -1 -i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


#pragma mark 快速排序
/**
 快速排序

 @param a 要排序的数组
 @param left 一般选第一位或者0
 @param right 数组长度
 */
void quickSort(int a[],int left,int right)
{
    int i = left;
    int j = right;
    int temp = a[left];
    if (left > right)
        return;
    while (i != j)
    {
        while (i < j && a[j] >= temp)
            j--;
        if (j > i)
            a[i] = a[j];//a[i]已经赋值给temp,所以直接将a[j]赋值给a[i],赋值完之后a[j],有空位
        while (i < j && a[i] <= temp)
            i++;
        if (i < j)
            a[j] = a[i];
    }
    a[i] = temp;//把基准插入,此时i与j已经相等R[low..pivotpos-1].keys≤R[pivotpos].key≤R[pivotpos+1..high].keys
    quickSort(a, left, i-1);//递归左边
    quickSort(a, i+1, right);//递归右边
}


#pragma mark 插入排序
/**
 插入排序

 @param arr 排序的数组
 @param len 数组长度
 */
void insertSort(int arr[],int len)
{
    int i,j,temp;//定义临时变量，用于交换数据时存储
    for (i = 1; i < len; i++) //因为我们要对该待排序列的每一个元素都和前面的已排好序的序列进行插入，所以我们会对序列进行遍历
    {
        for (j = 0; j < i; j++)//第二层循环主要用于对已排好序的序列进行扫描，和要插入进来的数据进行逐一比较，然后决定插入到哪里
        {
            if (arr[j] > arr[i])//从前往后对已排好序的元素和待插入元素进行大小比较，然后直到找到一个元素比被插入元素大，则交换位置
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


#pragma mark 归并排序
/**
 将一个数组中的两个相邻有序区间合并成一个

 @param a 包含两个有序区间的数组
 @param start 第1个有序区间的起始地址。
 @param mid 第1个有序区间的结束地址。也是第2个有序区间的起始地址。
 @param end 第2个有序区间的结束地址。
 */
void merge(int a[], int start, int mid, int end)
{
    int *tmp = (int *)malloc((end-start+1)*sizeof(int));// tmp是汇总2个有序区的临时区域
    int i = start;// 第1个有序区的索引
    int j = mid + 1;// 第2个有序区的索引
    int k = 0;// 临时区域的索引
    while(i <= mid && j <= end)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while(i <= mid)
        tmp[k++] = a[i++];
    while(j <= end)
        tmp[k++] = a[j++];
    // 将排序后的元素，全部都整合到数组a中。
    for (i = 0; i < k; i++)
        a[start + i] = tmp[i];
    free(tmp);
}


/**
 归并排序(从上往下)

 @param a 待排序的数组
 @param start 数组的起始地址
 @param end 数组的结束地址
 */
void merge_sort_up2down(int a[], int start, int end)
{
    if(a==NULL || start >= end)
        return ;
    int mid = (end + start)/2;
    merge_sort_up2down(a, start, mid); // 递归排序a[start...mid]
    merge_sort_up2down(a, mid+1, end); // 递归排序a[mid+1...end]
    // a[start...mid] 和 a[mid...end]是两个有序空间，
    // 将它们排序成一个有序空间a[start...end]
    merge(a, start, mid, end);
}

#pragma mark 归并排序

/**
 对数组a做若干次合并：数组a的总长度为len，将它分为若干个长度为gap的子数组；
 将"每2个相邻的子数组" 进行合并排序。

 @param a 待排序的数组
 @param len 数组的长度
 @param gap 子数组的长度
 */
void merge_groups(int a[], int len, int gap)
{
    int i;
    // 将"每2个相邻的子数组" 进行合并排序。
    for(i = 0; i+2*gap-1 < len; i+=(2*gap))
        merge(a, i, i+gap-1, i+2*gap-1);
    // 若 i+gap-1 < len-1，则剩余一个子数组没有配对。
    // 将该子数组合并到已排序的数组中。
    if ( i+gap-1 < len-1)
        merge(a, i, i + gap - 1, len - 1);
}


/**
 归并排序(从下往上)

 @param a 待排序的数组
 @param len 数组的长度
 */
void merge_sort_down2up(int a[], int len)
{
    int n;
    if (a==NULL || len<=0)
        return ;
    for(n = 1; n < len; n*=2)
    merge_groups(a, len, n);
}


#pragma mark 二分查找
/**
 二分查找

 @param array 查找的目标数组
 @param length 数组长度
 @param key 查找的key
 @return 结果，-1没找到，其他找到
 */
int binarySerach(int array[],int length, int key)
{
    int left = 0;
    int right = length - 1;
    // 这里必须是 <=
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == key)
            return mid;
        else if (array[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

#pragma mark 希尔排序
/**
 希尔排序

 @param a 目标数组
 @param n 数组长度
 */
void ShellSort(int a[],int n)
{
    int gap,j;
    for (gap = n / 2; gap > 0; gap /= 2)  //控制步长
        for (j = gap; j < n;++j)  //++j操作是很巧妙地，这步操作省去了对数组进行分组的一层循环
        {
            int tmp = a[j];
            int prev = j - gap;
            while (prev>=0 && a[j]<a[prev]){  //这里是直接插入排序的核心步骤
                a[j] = a[prev];
                prev -= gap;
            }
            a[prev + gap] = tmp;
        }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int arr[9] = {10,92,13,43,52,12,23,45,65};
    int length = sizeof(arr)/sizeof(int);//求数组的长度
    
//    bubble_sort(arr, 9);
    
//    quickSort(arr, 0, length);
    
//    insertSort(arr, length);
    
//    merge_sort_up2down(arr, 0, length-1);
//    merge_sort_down2up(arr, length);
    
    ShellSort(arr, length);
    
//    int arr[9] = {10,11,13,43,52,66,67,76,87};
//    int length = sizeof(arr)/sizeof(int);//求数组的长度
//    int res = binarySerach(arr, length, 10);
//
//    if (res != -1)
//    {
//        printf("AAAAA");
//    } else {
//        printf("BBBBB");
//    }
    
    for (int i = 0; i <9; i++)
    {
        printf("%d\n",arr[i]);
    }
    
    return 0;
}

