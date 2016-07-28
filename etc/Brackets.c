/*

A string S consisting of N characters is considered to be properly nested if any of the following conditions is true:

•S is empty;
•S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
•S has the form "VW" where V and W are properly nested strings.

For example, the string "{[()()]}" is properly nested but "([)()]" is not.

Write a function:

int solution(char *S);


that, given a string S consisting of N characters, returns 1 if S is properly nested and 0 otherwise.

For example, given S = "{[()()]}", the function should return 1 and given S = "([)()]", the function should return 0, as explained above.

Assume that:

•N is an integer within the range [0..200,000];
•string S consists only of the following characters: "(", "{", "[", "]", "}" and/or ")".

Complexity:

•expected worst-case time complexity is O(N);
•expected worst-case space complexity is O(N) (not counting the storage required for input arguments).

Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited. 

*/
int solution(char *S) {
    // write your code in C99 (gcc 4.8.2)
 char* basic_stack, *compare_stack;
 int top_b=-1, top_c=-1; 
 basic_stack=(char*)malloc(sizeof(char)*strlen(S)); 
 compare_stack=(char*)malloc(sizeof(char)*strlen(S));

 for(int i=0;i<strlen(S);i++)
 {
     basic_stack[i]=S[i];
     top_b++;
 }
    
 while(top_b!=-1){
    if (top_c==-1)
        compare_stack[++top_c]=basic_stack[top_b--];
    else{
        char temp=basic_stack[top_b--];
        if(temp=='}'||temp==')'||temp==']')
        {
        compare_stack[++top_c]=temp;
        }
        else if(temp=='{')
        {
            if(compare_stack[top_c]=='}')
            {
                top_c--;
            }
            else
            {
                compare_stack[++top_c]=temp;
            }
        }
        else if(temp=='(')
        {
            if(compare_stack[top_c]==')')
            {
                top_c--;
            }
            else
            {
                compare_stack[++top_c]=temp;
            }
        }
                else if(temp=='[')
        {
            if(compare_stack[top_c]==']')
            {
                top_c--;
            }
            else
            {
                compare_stack[++top_c]=temp;
            }
        }
        
        
    }
     
     
    }
    
    if(top_c==-1)
     return 1;
     else 
     return 0;
     
}