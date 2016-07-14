/*
2016.07.04
By using the multi perceptron, make the XOR Logic gate. 
hidden layer: 4
input node:2

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>


typedef struct inputStructure
{
	int x[2];
	int d_output;

}Input;
float net(int* x, float* w, int input_size, int idx, int layer_num);
float net_2nd(float* w, float* outcome, int layer_num);

float sigmoid(float net);
float calDelta_unipolar_sigmoid(float desired, float outcome);
float calDelta_w(float learning_rate, int desired, float outcome2nd, float outcome1st);
float calDelta_v(float learning_rate, float delta, float weight2nd, int input, float outcome1st);

float calError(float outcome, int desired);

void update_1st(float* w1st, float* w1st_delta, int weight_size_1st);
void update_2nd(float* w2nd, float* w2nd_delta, int weight_size_2nd);

int main()
{
	Input inputArr[4];
	float weight1st[8];
	float weight2nd[4];
	float weight1st_delta[8];
	float weight2nd_delta[4];
	float outcome1st[4];
	float outcome2nd;
	float learning_rate =0.1;
	int layerNum, inputNum;
	layerNum = 4;
	inputNum =2;

	srand(time(NULL));

	//initialization
	inputArr[0].x[0] = 0;
	inputArr[0].x[1] = 0;
	inputArr[1].x[0] = 0;
	inputArr[1].x[1] = 1;
	inputArr[2].x[0] = 1;
	inputArr[2].x[1] = 0;
	inputArr[3].x[0] = 1;
	inputArr[3].x[1] = 1;
	for (int i = 0; i < layerNum; i++)
	{
		if (inputArr[i].x[0] == inputArr[i].x[1])
			inputArr[i].d_output = 0;
		else
			inputArr[i].d_output = 1;

		weight2nd[i] = ((float)rand() / RAND_MAX)*0.01 + 0.001;
	}
	for (int i = 0; i < layerNum*inputNum; i++)
	{
		weight1st[i] = ((float)rand() / RAND_MAX)*0.01 + 0.001;
	}
	
	float error = 1;
	int c = 0;//count
	while (error>0.001)
	{
		int k = rand() % layerNum;
			//1st to 2nd
			for (int i = 0; i < layerNum; i++)
			{
				outcome1st[i] = sigmoid(net(inputArr[k].x, weight1st, inputNum, i, layerNum));
			}
			//2nd to 3rd
			outcome2nd = sigmoid(net_2nd(weight2nd, outcome1st, layerNum));

			//back propagation(calculate delta
			for (int i = 0; i < layerNum; i++)
			{
				weight2nd_delta[i] = calDelta_w(learning_rate, inputArr[k].d_output, outcome2nd, outcome1st[i]);
				
			}
			for (int i = 0; i < layerNum;i++)
				update_2nd(weight2nd, weight2nd_delta, layerNum);
			
			for (int i = 0; i <layerNum; i++)
			{
				for (int j = 0; j <inputNum; j++)
					weight1st_delta[j*layerNum + i] = calDelta_v(learning_rate, calDelta_unipolar_sigmoid(inputArr[k].d_output, outcome2nd), weight2nd[i], inputArr[k].x[j], outcome1st[i]);
			}

			update_1st(weight1st, weight1st_delta, layerNum*inputNum);
		
			 error = calError(outcome2nd, inputArr[k].d_output);
			 c++;

			printf("trial number: %d error:   %4f  outcome: %4f  desired outcome: %d \n", c,error, outcome2nd, inputArr[k].d_output);
		
	}
	system("pause");
	return 0;
	
	
}

float net(int* x, float* w, int input_size,int idx,int layer_num){
	float total=0.0f;

	
		for (int j = 0; j < input_size; j++)
		{
			total += x[j] * w[idx + j*layer_num];
		}
		//total +=  w[2*idx]+w[input_size*idx+1]; add bias

	
	return total;
}
float net_2nd(float* w, float* outcome, int layer_num)
{
	float total=0.0f;
	for (int i = 0; i < layer_num; i++)
	{
		total+= w[i] * outcome[i];
	}
	return total;
}

float sigmoid(float x)
{
	float exp_value;
	float return_value;

	/*** Exponential calculation ***/
	exp_value = exp((float)-x);

	/*** Final sigmoid value ***/
	return_value = 1.0 / (1 + exp_value);

	return return_value;
}


float calDelta_unipolar_sigmoid(float desired, float outcome)
{
	return (desired - outcome)*outcome*(1 - outcome);
}
float calDelta_w(float learning_rate, int desired, float outcome2nd, float outcome1st)
{
	return learning_rate*(desired - outcome2nd)*outcome2nd*(1 - outcome2nd)*outcome1st;
}
float calDelta_v(float learning_rate, float delta, float weight2nd, int input, float outcome1st)  
{
	return learning_rate*outcome1st*(1 - outcome1st)*input*delta*weight2nd;
}

float calError(float outcome, int desired)
{
	float temp = outcome - desired;
	return 0.5*pow((double)(outcome - desired), (double)2);
}

void update_1st(float* w1st, float* w1st_delta, int weight_size_1st)
{
	for (int i = 0; i < weight_size_1st; i++)
	{
		w1st[i] += w1st_delta[i];
		
	}
	
}
void update_2nd(float* w2nd, float* w2nd_delta, int weight_size_2nd)
{
	for (int i = 0; i < weight_size_2nd; i++)
	{
		w2nd[i] += w2nd_delta[i];

	}
}