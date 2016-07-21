
/**************************************************************************** 
 * @doc MissingInteger  * 

 * Request.
 Find the minimal positive integer not occurring in a given sequence.
Write a function:

int solution(int A[], int N);


that, given a non-empty zero-indexed array A of N integers, returns the minimal positive integer (greater than 0) that does not occur in A.

For example, given:
  A[0] = 1
  A[1] = 3
  A[2] = 6
  A[3] = 4
  A[4] = 1
  A[5] = 2 
the function should return 5.

Assume that:

•N is an integer within the range [1..100,000];
•each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].

Complexity:

•expected worst-case time complexity is O(N);
•expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

 * 21/7/2016
 * 
 ****************************************************************************/ 
int solution(int A[], int N) {

int* check;
//To match the index and return value, add one more element. Don't use the element indexed zero.

check=(int*)malloc(sizeof(int)*N+1); 
check[0]=1;

//initialization
for(int i=1;i<=N;i++)
{
check[i]=-1;    
}

// check the integer.
for(int i=0;i<N;i++)
{
 if(A[i]>0&&A[i]<N+1) 
 {
    if(check[A[i]]==-1)
    {
        check[A[i]]=1;
    }
 }

}

for(int i=1;i<=N;i++)
{
 
    if(check[i]==-1)
    {
        return i;
    }
}
// In case of N=1, A[0]=1
return N+1; 
}