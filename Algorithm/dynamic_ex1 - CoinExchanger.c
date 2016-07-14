/*2016. 6. 28
Joel Kim 
Exchage the money with the least number of given coins.
Given coins: 50, 12, 5 , 1 won */
#include <stdio.h>
#include <stdlib.h>
#define MAX 9000000

int main()
{
	int exchangeMoney = 33; //money to be exchanged
	int givenCoins = 4; // coin number
	int** result_arr, **component_arr;
	int coinValue[4] = { 1, 5, 12, 50 }; //coin value

	result_arr = (int**)malloc(sizeof(int*)*(exchangeMoney + 1));
	component_arr = (int**)malloc(sizeof(int*)*(exchangeMoney + 1));

	for (int i = 0; i <= exchangeMoney; i++)
	{
		result_arr[i] = (int*)malloc(sizeof(int)*givenCoins);
		component_arr[i] = (int*)malloc(sizeof(int)*givenCoins);

	}
	//initialization 
	for (int i = 0; i <= exchangeMoney; i++)
	{
		if (i == 0){
			memset(result_arr[i], 0, sizeof(int)*givenCoins);
			memset(component_arr[i], 0, sizeof(int)*givenCoins);
		}
		else{
			memset(result_arr[i], MAX, sizeof(int)*givenCoins);
			memset(component_arr[i], 0, sizeof(int)*givenCoins);
		}
	}

	for (int i = 0; i < givenCoins; i++)
	{
		for (int j = 1; j <= exchangeMoney; j++)//amount of money to be exchanged
		{

			if (i == 0)
			{
				if (j%coinValue[i] == 0){
					result_arr[j][i] = j / coinValue[i];
					component_arr[j][i] = j / coinValue[i];
				}
				else
					result_arr[j][i] = MAX;
			}
			else{


				for (int k = 0; k <= j; k++)
				{

					if (((j - k) % coinValue[i] == 0) && (result_arr[j][i] > result_arr[k][i - 1] + (j - k) / coinValue[i]))
					{
					
							result_arr[j][i] = result_arr[k][i - 1] + (j - k) / coinValue[i];
							component_arr[j][i] = (j - k) / coinValue[i];//where  the optimal solution come from.
					}
					
				}
			}
		}
	}

	printf("%d number of coin is needed.\n ", result_arr[exchangeMoney][3]);
	int each_coin[4] = { 0, };
	int current_money = exchangeMoney;
	//from the top, the number of coins is calculated. 
	for(int i = 3; i >= 0; i--)
	{
	

		each_coin[i] = component_arr[current_money][i];
		current_money = current_money - each_coin[i] * coinValue[i];
	
	}

	for (int j = 0; j <3; j++)
	{
		printf("%d of %d valued coin is needed .\n ", each_coin[j], coinValue[j]);
	}
	printf("\n");
	//deallocation
	for (int i = 0; i <= exchangeMoney; i++)
	{
		free(result_arr[i]);
		free(component_arr[i]);
	}
	free(result_arr);
	free(component_arr);
	system("pause");

	return 0;
}
