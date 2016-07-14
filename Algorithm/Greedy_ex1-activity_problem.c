/*
2016.6.29
Joel Kim
Activity problem : Find the largest number of possible activity combination.
input:
6
1   1   10
2   5   6
3   13  15
4   14  17
5   8   14
6   3   13
output:
3
2 5 4
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct ActivityStruct
{
	int id;
	int startTime;
	int finishTime;
	int include;
}acStruct;
void quickSort(acStruct* list, int left, int right);

int main() 
{
	int actvityNum = 0;
	acStruct *acList;
	int count = 0;
	char temp;
	scanf_s("%d", &actvityNum, sizeof(actvityNum));
	temp = getchar();
	acList = (acStruct*)malloc(sizeof(acStruct)*actvityNum);
	
	while (count!=actvityNum)
	{
		scanf_s("%d %d %d", &acList[count].id,&acList[count].startTime,&acList[count].finishTime);
		acList[count].include = 0;
		temp = getchar();
		count++;
	}

	quickSort(acList, 0, actvityNum - 1);

	count = 0;
	int resultCount = 0;
	int tempCompareTime=0;
	while (count != actvityNum)
	{
		if (count == 0)
		{
			acList[0].include = 1;
			tempCompareTime = acList[0].finishTime;
			resultCount++;
		}
		else
		{
			if (tempCompareTime <= acList[count].startTime)
			{
				acList[count].include = 1;
				tempCompareTime = acList[count].finishTime;
				resultCount++;
			}
		}
		count++;
	}
	printf("%d\n", resultCount);
	for (int i = 0; i < actvityNum; i++)
	{ 
		if (acList[i].include)
		printf("%d ", acList[i].id);
	}
	free(acList);
	system("pause");

	return 0;
}

void quickSort(acStruct* list, int left, int right)
{
	//set pivot
	int pivot,i,j;
	acStruct acTemp;
	i = left;
	j = right;
	pivot = list[(i + j) / 2].finishTime;

	//partitioning
	while (i <= j){
		while (list[i].finishTime < pivot)
			i++;
		while (list[j].finishTime > pivot)
			j--;
		if (i <= j){
			acTemp = list[j];
			list[j] = list[i];
			list[i] = acTemp;
			i++;
			j--;
		}
	}

	//recursion
	if (left < j)
		quickSort(list, left, j);
	if (i < right)
		quickSort(list, i, right);

}