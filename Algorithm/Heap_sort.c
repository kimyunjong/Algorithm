// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
/*

writer: Joel Kim 
date: 25_07_2016

Sort the array by using Heap sort. Return the largest value.

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
    buildHeap(A,N);
    for(int i=0;i<N;i++)
    {
    result[i]=extractMax(A,N-i);    
    }
    return result[0];
    
}