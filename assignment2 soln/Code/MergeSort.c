#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int count[20], ind=0; 
float tim[20];
void merge(int *a, int l, int m, int r)
{
	int c1,c2, i, j, k, *d1, *d2;
	c1 = m - l + 1;
	c2 = r - m;
	d1 = (int *)malloc((c1)*(sizeof(int)));
	d2 = (int *)malloc((c2)*(sizeof(int)));
	for(i=0;i<c1;i++)
	d1[i] = a[l+i];
	for(j=0;j<c2;j++)
	d2[j] = a[m+j+1];	
	i = 0; j = 0; k = l;
	while(i<c1 && j<c2)
	{
		if(d1[i]<d2[j])
		{
			count[ind]++;
			a[k] = d1[i];
			i++;
		}
		else
		{
			count[ind]++;
			a[k] = d2[j];
			j++;
		}
		k++;
	}
	while(k<r)
	{
		if(i==c1)
		{
			while(j<c2)
			{
				a[k] = d2[j];
				j++;
				k++;
			}
		}
		else
		{
			while(i<c1)
			{
				a[k] = d1[i];
				i++;
				k++;
			}
		}
	}
	free(d1);
	free(d2);
}
void mergesort(int *a, int l, int r)
{
	if(l < r)
	{
		count[ind]++;
		int m;
		m = (l+r)/2;
		mergesort(a, l, m);
		mergesort(a, m+1, r);
		merge(a, l, m, r);
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
			mergesort(a, 0, n[i]-1);
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
			ind++;
		}
		free(a);
		ind = 0;
	}	
}
