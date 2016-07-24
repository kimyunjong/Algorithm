
/*

A DNA sequence can be represented as a string consisting of the letters A, C, G and T, which correspond to the types of successive nucleotides in the sequence. Each nucleotide has an impact factor, which is an integer. Nucleotides of types A, C, G and T have impact factors of 1, 2, 3 and 4, respectively. You are going to answer several queries of the form: What is the minimal impact factor of nucleotides contained in a particular part of the given DNA sequence?

The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1] consisting of N characters. There are M queries, which are given in non-empty arrays P and Q, each consisting of M integers. The K-th query (0 ≤ K < M) requires you to find the minimal impact factor of nucleotides contained in the DNA sequence between positions P[K] and Q[K] (inclusive).

For example, consider string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6 
The answers to these M = 3 queries are as follows:

•The part of the DNA between positions 2 and 4 contains nucleotides G and C (twice), whose impact factors are 3 and 2 respectively, so the answer is 2.
•The part between positions 5 and 5 contains a single nucleotide T, whose impact factor is 4, so the answer is 4.
•The part between positions 0 and 6 (the whole string) contains all nucleotides, in particular nucleotide A whose impact factor is 1, so the answer is 1.

Assume that the following declarations are given:

struct Results {
  int * A;
  int M;
};


Write a function:

struct Results solution(char *S, int P[], int Q[], int M);


that, given a non-empty zero-indexed string S consisting of N characters and two non-empty zero-indexed arrays P and Q consisting of M integers, returns an array consisting of M integers specifying the consecutive answers to all queries.

The sequence should be returned as:

•a Results structure (in C), or
•a vector of integers (in C++), or
•a Results record (in Pascal), or
•an array of integers (in any other programming language).

For example, given the string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6 
the function should return the values [2, 4, 1], as explained above.

Assume that:

•N is an integer within the range [1..100,000];
•M is an integer within the range [1..50,000];
•each element of arrays P, Q is an integer within the range [0..N − 1];
•P[K] ≤ Q[K], where 0 ≤ K < M;
•string S consists only of upper-case English letters A, C, G, T.

Complexity:

•expected worst-case time complexity is O(N+M);
•expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Elements of input arrays can be modified.

Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited. 

*/
typedef struct mystruct{
    int* current;
    }Record;

struct Results solution(char *S, int P[], int Q[], int M) {
    struct Results result;
    int charNum=4;
    result.A =(int*)malloc(sizeof(int)*M);
    result.M = M;
    int N=strlen(S);
    if( N==1)
    {
        for(int i=0;i<M;i++)
        {
             if(S[0]=='A')
             {
                result.A[i]=1;
             }
            else if(S[0]=='C')
             {
                result.A[i]=2;
             }
             else if(S[0]=='G')
             {
                result.A[i]=3;
             }
             else if(S[0]=='T')
              {
                 result.A[i]=4;
             }    
        }
    }
        
   //initialize the records array. 
    Record *records=(Record*)malloc(sizeof(Record)*N);
    for(int i=0;i<N;i++)
    {
        records[i].current=(int*)malloc(sizeof(int)*charNum);
         for(int j=0;j<charNum;j++)
        {
             records[i].current[j]=0;    
         }
    }
    
    
    //count each character. 
    for(int i=0;i<N;i++)
    {  
        //set the previos array information.
       if(i!=0)
       {
            for(int j=0;j<charNum;j++)
            {
                records[i].current[j]=records[i-1].current[j];
            }
        }
         //add the current information
        if(S[i]=='A')
        {
            records[i].current[0]++;
        }
        else if(S[i]=='C')
        {
          records[i].current[1]++;
         }
        else if(S[i]=='G')
        {
            records[i].current[2]++;
         }
         else if(S[i]=='T')
        {
         records[i].current[3]++;
         }   
    }
    //check the queries.
    for(int i=0;i< M;i++)
    {   int temp[4]={0,0,0,0};
        int count=0;
        
        for(int j=0;j<charNum;j++)
        {   
            if(P[i]!=0)
            {
                temp[j]=records[Q[i]].current[j]-records[P[i]-1].current[j];
            }
            else 
            {
                temp[j]=records[Q[i]].current[j];
            }
            //If there is the minimum character, save the current index into the result and get out of the loop.
            if(temp[j]!=0)
            {
                  result.A[i]=j+1;
                  break;
            }
            count++;
        }
        //if the the P and Q are same index.
        if(count==charNum)
        {
           for(int j=0;j<charNum;j++)
            {   if(i!=0){
                    temp[j]=records[Q[i]].current[j]-records[Q[i]-1].current[j];
                    if(temp[j]!=0)
                    {
                        result.A[i]=j+1;
                        break;
                    }
                }
                else{
                    temp[j]=records[Q[i]].current[j];
                    if(temp[j]!=0)
                    {
                        result.A[i]=j+1;
                        break;
                    }
                }
            }
        }
    }   
    return result;
}