#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
	int x,y;
};
struct node *a, *hull;
float tim[20];
int ind=0;
int rot(int p,int q, int r)
{
	int s1 = (a[p].y - a[q].y)*(a[p].x - a[r].x) - (a[p].x - a[q].x)*(a[p].y - a[r].y);
	if(s1 == 0) return 0; //collinear points
	if(s1 > 0) return -1; //q is more counterclockwise than r
	else return 1; //r is more counterclockwise than q
}
void giftwrap(int n)
{
	int size=0, l=0, i, p, q;
	//Ifnumber of elements is less than 3 we are done as convex polygon cannot be formed.
	if(n<3) return;
	hull = (struct node *)malloc(n*(sizeof(struct node)));
	
	//First, we will find the leftmost point and if 2 points have the same x coordinate then we choose the one with lower y coordinate.
	for(i=1;i<n;i++)
	{
		if(a[i].x < a[l].x) l=i;
		else if(a[i].x == a[l].x && a[i].y < a[l].y) l=i;
	}
	p=l;
	//Assign it as the first point of the hull
	hull[size] = a[p];
	size++;
	do
	{
		q=(p+1)%n;
		//Choose the most counter-clockwise point to p as q.
		for(i=0;i<n;i++)
		{
			if(rot(p,q,i)==1) q=i;
		}
		p=q;
		//Put q in the hull and go forward with the loop taking q as p now.
		if(p != l)
		{
			hull[size] = a[p];
			size++;
		}
		//Run the loop while we reach back to the first point as the most counter-clockwise point.
	} while(p!=l);
	/*printf("\nThe convex hull is:-");
	for(i=0;i<size;i++)
	{
		printf("(%d, %d), ",hull[i].x, hull[i].y);
	}
	printf("\n");*/
}
int main()
{
	int i, j, n[6];
	n[0] = 5000; n[1] = 10000; n[2] = 20000; n[3] = 50000; n[4] = 70000; n[5] = 100000;
	clock_t begin, end;
	srand(1618);
	for(i=0;i<6;i++)
	{
		printf("For n = %d the time taken is:\n", n[i]);
		a = (struct node *)malloc(n[i]*(sizeof(struct node)));
		while(ind<1)
		{
			for(j=0;j<n[i];j++)
			{
				a[j].x = rand();
				a[j].y = rand();	
			}
			begin = clock();
			giftwrap(n[i]);
			end = clock();
			tim[ind] = ((double)(end - begin))/ CLOCKS_PER_SEC;
			printf("%f\n", tim[ind]);
			ind++;
		}
		ind=0;
	}
	return 0;
}
