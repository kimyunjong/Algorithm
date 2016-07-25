// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
/*

writer: Joel Kim 
date: 25_07_2016

Write a function

int solution(int A[], int N);


that, given a zero-indexed array A consisting of N integers, returns the number of distinct values in array A.

Assume that:

•N is an integer within the range [0..100,000];
•each element of array A is an integer within the range [−1,000,000..1,000,000].

For example, given array A consisting of six elements such that:
A[0] = 2    A[1] = 1    A[2] = 1
A[3] = 2    A[4] = 3    A[5] = 1 
the function should return 3, because there are 3 distinct values appearing in array A, namely 1, 2 and 3.

Complexity:

•expected worst-case time complexity is O(N*log(N));
•expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.

Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited. 

*/

void heapify(int* arr, int arrSize, int parent)
{
    int l, r, max;
    l = parent * 2 + 1;
    r = parent * 2 + 2;

    if (l<arrSize&&arr[l]>arr[parent])max = l;
    else max = parent;
    if (r<arrSize&&arr[r]>arr[max])max = r;

    if (max != parent){
        int temp = arr[parent];
        arr[parent] = arr[max];
        arr[max] = temp;
        heapify(arr, arrSize, max);
    }
}
void buildHeap(int* arr, int arrSize)
{
    int current = arrSize/2;
    for (int i = current; i >= 0; i --)
    {
        
        heapify(arr, arrSize, i);
        if (i == 0)
        {
            break;
        }
    }
}
int extractMax(int* arr, int arrSize)
{
    int temp = arr[arrSize - 1];
    arr[arrSize - 1] = arr[0];
    arr[0] = temp;
    heapify(arr, arrSize - 1, 0);
    return  arr[arrSize - 1];
}
int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int* result=(int*)malloc(sizeof(int)*N);
    int answer=0;
    buildHeap(A,N);
    for(int i=0;i<N;i++)
    {
    result[i]=extractMax(A,N-i);    
    }
    for(int i=0;i<N;i++)
    {
     if(i==0){
        answer++;    
     }
     else{
        if(result[i]!=result[i-1])
        {
        answer++;    
        }
         
     }
        
    }
    return answer;
}