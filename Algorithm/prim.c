/*
Finding the MST by using prim algorithm. 
start from the vertex 0.
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
	if (l < arrSize &&arr[l].weight < arr[parent].weight)min = l;
	else min = parent;
	if (r < arrSize &&arr[r].weight < arr[min].weight)min = r;

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
edge extractMin(edge* arr, int* arrSize)
{	
	(*arrSize) = (*arrSize)- 1;
	edge temp = arr[*arrSize];
	arr[*arrSize] = arr[0];
	arr[0] = temp;
	heapify(arr, *arrSize, 0);
	return arr[*arrSize];
}
void insertHeap(edge* arr, int *arrSize, edge added_edge)
{
	
	arr[*arrSize] = added_edge;
	(*arrSize) = (*arrSize) + 1;
	buildHeap(arr, *arrSize);

}

int main()
{
	srand(time(NULL));
	int item_size = 10;
	int set_size = 0;
	int edge_num = 17;
	int* check = (int*)malloc(sizeof(int)*item_size);
	for (int i = 0; i < item_size; i++)
	{
		check[i] = false;
	}

	edge* set_edge = (edge*)malloc(sizeof(edge) * item_size*item_size);
	edge* mst = (edge*)malloc(sizeof(edge) * item_size);
	edge* mst_candidate = (edge*)malloc(sizeof(edge) * edge_num*2);
	int count = 0;
	int edge_candidate_count = 0;
	//setting the start vertex
	check[0] = true;
	int start_vertex = 0;


	//initialization, setting the edge values from array.
	for (int i = 0; i < item_size; i++)
	{
		for (int j = 0; j < item_size; j++)
		{
			if (path[i][j] != MAX&&path[i][j] != 0)
			{
				set_edge[count].from = i;
				set_edge[count].to = j;
				set_edge[count++].weight = path[i][j];
				
				//set the first vertex's edge information.
				if (i == 0)
				{
					mst_candidate[edge_candidate_count].from = i;
					mst_candidate[edge_candidate_count].to = j;
					mst_candidate[edge_candidate_count++].weight = path[i][j];
				}
			}
		}
	}
	
	//build min heap
	buildHeap(mst_candidate, edge_candidate_count);
	for (int i = 0; i < item_size-1; i++)
	{	
		edge candidate;
		//cycle check
		do
		{	
			candidate = extractMin(mst_candidate, &edge_candidate_count);
			
		} while (check[candidate.to]);
		
		//check the choosen vertex to the 'check' array.
		check[candidate.from] = true;
		mst[i] = candidate;

		//add the new edge related with the choosen vertex
		for (int i = 0; i < count; i++)
		{
			if (set_edge[i].from == candidate.to)
			{	
			
				insertHeap(mst_candidate, &edge_candidate_count, set_edge[i]);
			}
		}


	}
	

	for (int i = 0; i < item_size - 1; i++)
	{
		printf("Result path-> From %d, To %d weight: %d \n", mst[i].from, mst[i].to, mst[i].weight);
	}
	system("pause");
}