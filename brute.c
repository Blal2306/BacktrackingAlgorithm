#include <stdio.h>
#include <stdlib.h>

//file pointer
FILE *fr;
int size;

//weights
int w[30];

//profits
int p[30];

//capacity
int c;

//****** OTHER VARIABLES *******/
int ps_x;
int in[30];
int out[50][15];
//******************************/

//2^n calculator
int power_cal(int n)
{
	int x = 2;
	if(n == 0)
	{
		return 1;
	}
	else
	{
		while(n!=1)
		{
			n--;
			x = x*2;
		}
	}
	return x;
}
void init()
{
	for(int i = 0; i < size; i++)
	{
		in[i] = i+1;
	}
}
void power_set(int n)
{

	int count = 0;
	int current_pos = 0;
	int pos = 0;
	
	for(int i = 0; i < ps_x; i++)
	{
		if(i == 0)
		{
			out[0][0] = 0;
			count++;
			pos++;
		}
		else
		{
			int tmp = count;
			for(int j = 0; j < tmp; j++)
			{
				out[pos][0] = out[j][0] + 1;

				int len = out[j][0];
				int t = 0;
				for(t = 0; t < len; t++)
				{
					out[pos][t+1] = out[j][t+1];
				}
				out[pos][t+1] = in[current_pos];
				
				pos++;
				count++;
				i++;
			}
			current_pos++;
		}
	
	}
		
}
void print_set()
{
		for(int i = 0; i < ps_x; i++)
	{
		for(int j = 0; j < size+1; j++)
		{
			printf("%d\t",out[i][j]);
		}
		printf("\n");
	}
}
void print_bag(int i)
{
	//size of the bag
	int size_p = out[i][0];
	
	//print the weights
	int wht = 0;
	for(int j = 1; j < size_p+1; j++)
	{
		int tmp = out[i][j] -1;
		wht = wht + w[tmp];
	}
	printf("%d\n",wht);
	
	//print the profits
	int pt = 0;
	for(int j = 1; j < size_p+1; j++)
	{
		int tmp = out[i][j] - 1;
		pt = pt + p[tmp];
	}
	printf("%d\n",pt);
	
	//print the set elements
	for(int j = 1; j < size_p+1; j++)
	{
		int tmp = out[i][j];
		if(j == size_p)
			printf("%d ",tmp-1);
		else
			printf("%d,",tmp-1);
	}
	printf("\n");
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
		w[i] = x;
		fscanf(fr,"%c",line);
	}
	
	//READ THE PROFITS
	x = 0;
	for(int i = 0; i < size; i ++)
	{
		fscanf(fr,"%d",&x);
		p[i] = x;
		fscanf(fr,"%c",line);
	}
	
	//GET THE CAPACITY
	fgets(line,30,fr);
	c = atoi(line);
	
	//***** END OF FILE READING ********//
	
	//what is the size of the power set
	//2^n
	ps_x = power_cal(size);
	
	//*********** KNAPSACK BRUTE FORCE ALGORITHM START ************//
	init();
	//generate a power set
	power_set(size);
	
	//+++++ location of the max set found thus far ++++++//
	int max_profit = 0;
	int max_weight = 0;
	int loc = -1;
	//+++++++++++++++++++++++++++++++++++++++++++++++++++//
	
	for(int i = 0; i < ps_x; i++)
	{
		int s_in = out[i][0];
		int sum = 0;
		int weight = 0;
		int l = -1;
		
		for(int j = 1; j < s_in + 1; j++)
		{
			int index = out[i][j] - 1;
			sum = sum + p[index];
			weight = weight + w[index];
			l = i;
		}
		
		if(weight <= c && sum > max_profit)
		{
			max_profit = sum;
			max_weight = weight;
			loc = l;
		}
	}
	print_bag(loc);
	//++++++++++++++ END OF ALGORITHM ++++++++++++++//

	return 0;
}
