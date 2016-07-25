/*

A zero-indexed array A consisting of N integers is given. A triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

•A[P] + A[Q] > A[R],
•A[Q] + A[R] > A[P],
•A[R] + A[P] > A[Q].

For example, consider array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20 
Triplet (0, 2, 4) is triangular.

Write a function:

int solution(int A[], int N);


that, given a zero-indexed array A consisting of N integers, returns 1 if there exists a triangular triplet for this array and returns 0 otherwise.

For example, given array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20 
the function should return 1, as explained above. Given array A such that:
  A[0] = 10    A[1] = 50    A[2] = 5
  A[3] = 1 
the function should return 0.

Assume that:

•N is an integer within the range [0..100,000];
•each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].

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
int checkTriangular(int p, int q, int r)
{
    if(p>0&&q>0&&r>0)
    {
        if(p>r-q&&q>p-r&&p>q-r)
         return 1;
         else return 0;
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
    if(N<3)
    {
    return 0;    
    }
    
    buildHeap(A,N);
    for(int i=0;i<N;i++)
    {
    result[i]=extractMax(A,N-i);    
    }
   
   for(int i=0;i<N-2;i++)
   {
        if( checkTriangular(result[i],result[i+1],result[i+2]))
        {
         return 1;
        }
    }
    
    return answer;
}