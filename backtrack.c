#include <stdio.h>
#include <stdlib.h>

//file pointer
FILE *fr;
int size;

//weights
int weights[30];

//profits
int profits[30];

//capacity
int capacity;

//****** other variables ********//
int data[30][3];
int maxprofit = 0;
int bestset[30];
int include[30];
//*******************************/
void init()
{
	for(int i = 0; i < size; i++)
	{
		data[i][0] = profits[i];
		data[i][1] = weights[i];
		data[i][2] = (int) data[i][0] / data[i][1];
	}
}
void print()
{
	for(int i = 0; i < size; i++)
	{
		printf("%d\t%d\t%d\n",data[i][0],data[i][1],data[i][2]);
	}
}
void insertion_sort()
{
	for(int j = 1; j < size; j++)
	{
		int key = data[j][2];
		int key_1 = data[j][1];
		int key_0 = data[j][0];
		
		int i = j - 1;
		while(i >= 0 && data[i][2] < key)
		{
			data[i+1][0] = data[i][0];
			data[i+1][0] = data[i][1];
			data[i+1][2] = data[i][2];
			
			i = i - 1;
		}
		data[i+1][2] = key;
		data[i+1][1] = key_1;
		data[i+1][0] = key_0;
	}
}
int KWF2(int i, int w, int profit)
{
	int weight = w;
	int bound = profit;
	double x[size];
	
	for(int j = i; j < size; j++)
	{
		x[j] = 0;
	}
	
	while(weight < capacity && i < size)
	{
		if(data[i][1] + weight < capacity)
		{
			x[i] = 1;
			weight = weight + data[i][1];
			bound = bound + data[i][0];
		}
		else
		{
			x[i] = (capacity - weight)/(double)data[i][1];
			weight = capacity;
			bound = bound + (int)((double)data[i][0]*x[i]);
		}
		i = i+1;
	}
	return bound;
}
int promising(int i, int weight, int profit)
{
	if(weight >= capacity)
	{
		return 0;
	}
	int bound = KWF2(i+1,weight,profit);
	if(bound > maxprofit)
		return 1;
	else
		return 0;
}
void knapsack(int i, int profit, int weight)
{
	if(weight <= capacity && profit > maxprofit)
	{
		maxprofit = profit;
		memcpy(bestset, include, size * sizeof(int));
	}
	if(promising(i,weight, profit))
	{
		include[i+1] = 1;
		knapsack(i+1,profit+data[i+1][0], weight+data[i+1][1]);
		include[i+1] = 0;
		knapsack(i+1,profit, weight);
	}
}
int main(int argc, char *argv[])
{
	//****** BEGIN OF FILE READING ******//
	//a line read will be stored here
	char line[80];
	
	//open the file with the given location
	fr = fopen (argv[1], "rt");
	
	//read the first line
	fgets(line,30,fr);
	
	//GET THE SIZE
	size = atoi(line);
	
	//READ THE WEIGHTS
	int x = 0;
	for(int i = 0; i < size; i ++)
	{
		fscanf(fr,"%d",&x);
		weights[i] = x;
		fscanf(fr,"%c",line);
	}
	
	//READ THE PROFITS
	x = 0;
	for(int i = 0; i < size; i ++)
	{
		fscanf(fr,"%d",&x);
		profits[i] = x;
		fscanf(fr,"%c",line);
	}
	
	//GET THE CAPACITY
	fgets(line,30,fr);
	capacity = atoi(line);
	
	//***** END OF FILE READING ********//
	
	init();
	insertion_sort();
	
	knapsack(-1,0,0);
	
	//get the total weight
	int wht = 0;
	for(int i = 0; i < size; i++)
	{
		if(bestset[i] == 1)
		{
			wht = wht + data[i][1];
		}
	}
	printf("%d\n",wht);
	
	//print the max profit
	printf("%d\n",maxprofit);
	
	//print the best set elements
	for(int i = 0; i < size; i++)
	{
		if(bestset[i] == 1)
		{
			printf("%d,",i);
		}
	}
	printf("\n");

}
