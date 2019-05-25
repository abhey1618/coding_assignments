#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int count[20], ind=0; 
float tim[20];
void maxheap(int *a, int loc, int n)
{
	int large,b,l,r;
	large = loc;
	l = 2*loc+1;
	r = 2*loc+2;
	if(l <= n && a[l] > a[large]) large = l;
	if(r <= n && a[r] > a[large]) large = r;
	count[ind] = count[ind] + 2;
	if(large != loc)
	{
		b = a[large]; a[large] = a[loc]; a[loc] = b;
		maxheap(a,large,n);
	}
}
void heapsort(int *a, int n)
{
	int i,j;
	//First, we need to create a max-heap
	for(i = (n+1)/2 -1;i>=0;i--)
	{
		maxheap(a,i,n);
	}
	for(i = n; i>=0;i--)
	{
		j = a[0]; a[0]=a[i]; a[i] = j;
		maxheap(a,0,i-1);
	}
}

int main()
{
	int *a, i, j, n[6];
	n[0] = 500; n[1] = 1000; n[2] = 2000; n[3] = 5000; n[4] = 10000; n[5] = 50000;
	clock_t begin, end;
	srand(18);
	for(i=0;i<6;i++)
	{
		printf("For n = %d the time and comparisons are:\n", n[i]);
		a = (int *)malloc(n[i]*(sizeof(int)));
		while(ind<20)
		{
			for(j=0;j<n[i];j++)
			{
				a[j] = rand();
			//	printf("%d ", a[j]);
			}
			begin = clock();
			count[ind]=0;
			heapsort(a, n[i]-1);
			end = clock();
			//printf("\nThe sorted array is\n");
			//for(j=0;j<n[i];j++)
			//{
			//	printf("%d ", a[j]);			
			//}
			//printf("\n");
			tim[ind] = ((double)(end - begin))/ CLOCKS_PER_SEC;
			//printf("Time taken is %f.",tim[ind]);
			//printf("Count is %d\n",count[ind]);
			printf("%f\t",tim[ind]);
			printf("%d\n",count[ind]);
			ind++;
		}
		free(a);
		ind = 0;
		//if(i==0) break;
	}	
}
