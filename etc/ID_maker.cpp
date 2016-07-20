/*
Joel kim 
2016.5.20
print the number of employee's id. Each Id is given in random from 0 to 99999.
Also each memeber gets score in rage from 0 to 100. 
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <String.h>
#define SCORERANGE 100
#define IDRANGE 100000
				



typedef struct WorkerStruct
{
	char id[8];
	int score;
}worker;
int analNum(int i);
void printWorkers(worker* workers, int count);
int Shuffle(int * index, int nMax);
int main()
{
	int count = 0, countForPick = 0;
	worker* workers;
	int* used_number, *indexArr;
	int i = 0, j = 0, blankNum;
	char head[3] = "NT";
	char blank[6] = "00000";
	char idNum[6];
	srand(time(NULL));
	printf("The number of Record: ");
	scanf_s(" %d", &count);
	countForPick = count;

	workers = (worker*)malloc(sizeof(worker)*count);
	indexArr = (int*)malloc(sizeof(int)*IDRANGE);

	for (i = 0; i < IDRANGE; i++)
	{
		indexArr[i] = i;
	}
	Shuffle(indexArr, IDRANGE);
	i = 0; //count 
	while (countForPick != 0){
		int temp = 0;
		//choose the id
		temp = Shuffle(indexArr, countForPick);
		blankNum = 5 - analNum(temp);
		sprintf_s(idNum, sizeof(idNum), "%d", temp);
		memset(workers[i].id, '\0', 8);
		strcat(workers[i].id, head);
		strncat(workers[i].id, blank, blankNum);
		strcat(workers[i].id, idNum);

		workers[i].score = rand() % SCORERANGE;
		i++;
		countForPick--;

	}

	printWorkers(workers, count);
	free(indexArr);
	free(workers);
	system("pause");
	return 0;

}

int analNum(int i)
{
	int var, check = 10, su = 1;
	var = i;
	if (var == 0)
	{

		return 0;
	}
	while (var / check)
	{
		su++;
		check *= 10;
	}
	return su;
}
void printWorkers(worker* workers, int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		printf("%s %d\n", workers[i].id, workers[i].score);

	}

}
int Shuffle(int * index, int nMax){
	int i, n;


	int nTmp;
	int returnVal;
	srand(time(NULL));
	for (i = nMax - 1; i >= 0; i--){

		n = rand() % nMax;
		nTmp = index[i];
		index[i] = index[n];
		index[n] = nTmp;

	}
	returnVal = index[0];
	index[0] = index[nMax - 1]; //delete the chosen one.
	return returnVal;

}
