/*
Finding the MST by using kruskal algorithm. Use the joint and disjoint when I check the cycle. 
given array:
int path[10][10] =
{ { 0, 125, MAX, 214, 161, MAX, MAX, MAX, MAX, MAX },
{ 125, 0, 126, MAX, MAX, MAX, 219, MAX, MAX, MAX },
{ MAX, 126, 0, MAX, MAX, MAX, MAX, 237, MAX, MAX },
{ 214, MAX, MAX, 0, 86, 99, MAX, MAX, MAX, MAX },
{ 161, MAX, MAX, 86, 0, MAX, 152, MAX, MAX, MAX },
{ MAX, MAX, MAX, 99, MAX, 0, 211, MAX, MAX, 161 },
{ MAX, 219, MAX, MAX, 152, 211, 0, 87, 108, 135 },
{ MAX, MAX, 237, MAX, MAX, MAX, 87, 0, 110, MAX },
{ MAX, MAX, MAX, MAX, MAX, MAX, 108, 110, 0, 106 },
{ MAX, MAX, MAX, MAX, MAX, 161, 135, MAX, 106, 0 } };



writer: kim joel

*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum { false, true } bool;
#define MAX 9999999

typedef struct ItemStruct
{
	int item_id;
	struct ItemStruct* next_node;

}ItemNode;
typedef struct vertexItem
{
	int id;
	int value;
}VertexItem;
typedef struct edge
{
	int from;
	int to;
	int weight;
}edge;
int path[10][10] =
{ { 0, 125, MAX, 214, 161, MAX, MAX, MAX, MAX, MAX },
{ 125, 0, 126, MAX, MAX, MAX, 219, MAX, MAX, MAX },
{ MAX, 126, 0, MAX, MAX, MAX, MAX, 237, MAX, MAX },
{ 214, MAX, MAX, 0, 86, 99, MAX, MAX, MAX, MAX },
{ 161, MAX, MAX, 86, 0, MAX, 152, MAX, MAX, MAX },
{ MAX, MAX, MAX, 99, MAX, 0, 211, MAX, MAX, 161 },
{ MAX, 219, MAX, MAX, 152, 211, 0, 87, 108, 135 },
{ MAX, MAX, 237, MAX, MAX, MAX, 87, 0, 110, MAX },
{ MAX, MAX, MAX, MAX, MAX, MAX, 108, 110, 0, 106 },
{ MAX, MAX, MAX, MAX, MAX, 161, 135, MAX, 106, 0 } };
void heapify(edge* arr, int arrSize, int parent)
{
	int l, r, min;
	l = parent * 2 + 1;
	r = parent * 2 + 2;
	if (l<arrSize &&arr[l].weight<arr[parent].weight)min = l;
	else min = parent;
	if (r<arrSize &&arr[r].weight<arr[min].weight)min = r;

	if (min != parent){
		edge temp = arr[parent];
		arr[parent] = arr[min];
		arr[min] = temp;
		heapify(arr, arrSize, min);
	}

}
void buildHeap(edge* arr, int arrSize)
{
	int current = arrSize / 2;
	for (int i = current; i >= 0; i--)
	{
		heapify(arr, arrSize, i);
		if (i == 0)
		{
			break;
		}
	}
}
edge extractMin(edge* arr, int arrSize)
{
	edge temp = arr[arrSize - 1];
	arr[arrSize - 1] = arr[0];
	arr[0] = temp;
	heapify(arr, arrSize - 1, 0);
	return arr[arrSize - 1];
}
int find_set(int a, ItemNode** set, int set_size)
{
	ItemNode* set_item = NULL;


	int idx = 0;
	set_item = set[idx];
	int find = false;
	//travel the each set of idx. 
	while (idx < set_size){

		while (set_item != NULL)
		{
			if (a == set_item->item_id)
			{
				find = true;
				break;
			}
			set_item = set_item->next_node;
		}
		if (find)
		{
			break;
		}
		idx++;
		set_item = set[idx];
	}
	// if find the designated value, return the idx of the value.
	if (find)
	{
		return idx;
	}
	else
		return -1;
}
//return true,if there is the union process. return false , if there is no union process; both value are already in the same set of idx. 
int union_set(int a, int b, ItemNode** set, int* set_size){

	ItemNode* temp_a = (ItemNode*)malloc(sizeof(ItemNode));
	ItemNode* temp_b = (ItemNode*)malloc(sizeof(ItemNode));
	temp_a->item_id = a;
	temp_a->next_node = NULL;
	temp_b->item_id = b;
	temp_b->next_node = NULL;
	ItemNode* current;
	int result_a = find_set(a, set, *set_size);
	int result_b = find_set(b, set, *set_size);
	int test = 0;
	//Both elements does not belong to the set.
	if (result_a == -1 && result_b == -1)
	{
		temp_a->next_node = temp_b;

		set[*set_size] = (ItemNode*)malloc(sizeof(ItemNode));
		set[*set_size] = temp_a;
		(*set_size)++;
		test = 4;
	}
	//All element belongs to the set. 
	else if (result_a != -1 && result_b != -1)
	{
		int pre;
		int post;
		//find the previous set and post set.
		if (result_a > result_b)
		{
			pre = result_b;
			post = result_a;
		}
		//if two values are already in the same idx of set. 
		else if (result_a == result_b)
		{
			return false;
		}
		else{
			pre = result_a;
			post = result_b;
		}
		//union two set. 
		current = set[pre];
		while (current->next_node != NULL)
		{
			current = current->next_node;
		}
		current->next_node = set[post];
	}
	//Only one element belong to the set.
	else
	{
		// when there is no set which contains a.
		if (result_a == -1)
		{
			current = set[result_b];
			while (current->next_node != NULL)
			{
				current = current->next_node;
			}
			current->next_node = temp_a;

		}
		// when there is no set which contains b.

		else{
			current = set[result_a];

			while (current->next_node != NULL)
			{
				current = current->next_node;
			}
			current->next_node = temp_b;
		}

	}
	return true;
}


int main()
{
	srand(time(NULL));
	int item_size = 10;
	int set_size = 0;
	ItemNode** set = (ItemNode**)malloc(sizeof(ItemNode*) * item_size);
	edge* set_edge = (edge*)malloc(sizeof(edge) * item_size*item_size);
	edge* mst = (edge*)malloc(sizeof(edge) * item_size);

	int count = 0;
	//initialization, setting the edge values from array.
	for (int i = 0; i < item_size; i++)
	{
		for (int j = i + 1; j < item_size; j++)
		{
			if (path[i][j] != MAX)
			{
				set_edge[count].from = i;
				set_edge[count].to = j;
				set_edge[count].weight = path[i][j];
				count++;
			}
		}
	}
	//build min heap
	buildHeap(set_edge, count);

	int result_count = 0;
	// extract min value. check whether the edge makes a cycle.
	for (int i = 0; i < count; i++)
	{
		edge temp = extractMin(set_edge, count - i);
		if (union_set(temp.from, temp.to, set, &set_size))
		{
			mst[result_count] = temp;
			result_count++;
		}
	}

	for (int i = 0; i < item_size-1; i++)
	{
		printf("Result path-> From %d, To %d weight: %d \n", mst[i].from, mst[i].to, mst[i].weight);
	}
	system("pause");
}