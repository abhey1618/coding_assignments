#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int count[20], ind=0; 
float tim[20];
void quicksort(int *a,int left,int right)
{
	int l,r,c,piv;
	piv = a[left];
	l = left; r = right;
	if(l>=r) return;
	while(l<r)
	{
		while(a[l] <= piv && l<=right)
		{
			count[ind]++;
			l++;
		}
		while(a[r] > piv && r>=left)
		{
			count[ind]++;
			r--;
		}
		if(l<r)
		{
			c = a[r]; a[r] = a[l]; a[l] = c;
		}
	}
	c = a[r]; a[r] = a[left]; a[left] = c;
	quicksort(a, left, r-1);
	quicksort(a, r+1, right);
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
			quicksort(a, 0, n[i]-1);
			end = clock();
			//printf("\nThe sorted array is\n");
			//for(j=0;j<n[i];j++)
			//{
			//	printf("%d ", a[j]);			
			//}
			//printf("\n");
			tim[ind] = ((double)(end - begin))/ CLOCKS_PER_SEC;
			printf("Time taken is %f.",tim[ind]);
			printf("Count is %d\n",count[ind]);
			//printf("%f\t",tim[ind]);
			//printf("%d\n",count[ind]);
			ind++;
		}
		free(a);
		ind = 0;
		//if(i==0) break;
	}	
}
