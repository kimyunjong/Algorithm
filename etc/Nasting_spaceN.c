/*
writer: Joel Kim
A string S consisting of N characters is called properly nested if:

S is empty;
S has the form "(U)" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.
For example, string "(()(())())" is properly nested but string "())" isn't.

Write a function:

int solution(char *S);
that, given a string S consisting of N characters, returns 1 if string S is properly nested and 0 otherwise.

For example, given S = "(()(())())", the function should return 1 and given S = "())", the function should return 0, as explained above.

Assume that:

N is an integer within the range [0..1,000,000];
string S consists only of the characters "(" and/or ")".
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1) (not counting the storage required for input arguments).
Copyright 2009–2016 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.
*/
void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
//Use the input array as an stack. 
int solution(char *S) {
//if S is an odd number array.
 if (strlen(S) % 2 == 1)
		return 0;
//If the array is empty.
 if (strlen(S) == 0)
		return 1;


	int result = -1;
	int length = strlen(S) - 1;
	int half_length = length / 2;
	//Process the array divided into two pieces. 
	for (int i = length; i >= 0; i--)
	{
				
		if (i > half_length)
		{	//swap the two element from the each end of array to save the space.
			swap(&S[i], &S[length - i]);
			swap(&S[length - i], &S[++result]);
			
			//if there is the elements in the stack
			if (result > 0)
			{
				if (S[result] == '('&&S[result-1] == ')')
				{
					result = result - 2;
				}
			}
		}
		//After the process of the half of the array.
		else
		{	//if there is the elements in the stack
			if (result >=0)
			{
				if (S[length - i] == '('&&S[result] == ')')
					result = result - 1;
				else
				{
					S[++result] = S[length - i];
					if (result > half_length)
						return 0;
				}
			}
			//if there is no elements in the stack
			else
			{
				S[++result] = S[length - i];
			}
		}
		
	}

	if (result == -1)
		return 1;
	else
		return 0;  
}