#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum { false, true } bool;

typedef struct ItemStruct
{
	int item_id;
	struct ItemStruct* next_node;

}ItemNode;
typedef struct Edge
{
	int from;
	int to;
}edge;

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
		else if (result_a==result_b)
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
	int item_size = 20;
	int range = 10;
	int set_size = 0;
	ItemNode** set = (ItemNode**)malloc(sizeof(ItemNode*) * item_size);
	edge* set_edge = (edge*)malloc(sizeof(edge) * item_size);
	for (int i = 0; i < item_size; i++)
	{
		int from = rand() % range;
		int to = rand() % range;
		while (from==to)
		{
			to = rand() % range;
		}
		set_edge[i].from = from;
		set_edge[i].to = to;
		
	}
	for (int i = 0; i < item_size; i++)
	{
		if (union_set(set_edge[i].from, set_edge[i].to, set, &set_size))
		{
			printf("New path is added. From %d, To %d \n", set_edge[i].from, set_edge[i].to);
		}
		else{
			printf("This path is already in the set. From %d, To %d \n", set_edge[i].from, set_edge[i].to);
		}
	}


	//system("pause");
}