#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
	int x,y;
};
int ind=0;
float tim[20];
struct node *inp, p0, *stack;
int rot(struct node p,struct node q,struct node r)
{
	int s1 = (p.y - q.y)*(p.x - r.x) - (p.x - q.x)*(p.y - r.y);
	if(s1 == 0) return 0; //collinear points
	if(s1 > 0) return -1; //q is more counterclockwise than r
	else return 1; //r is more counterclockwise than q
}
int normSq(struct node a, struct node b)
{
	//This function is used if we encounter collinear points during ordering of vertices.
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int comp(const void* va, const void* vb)
{
	//This is the comparison function for qsort
	struct node a,b,*c,*d;
	int r;
	c = (struct node *)va;
	d = (struct node *)vb;
	a.x = c->x;
	a.y = c->y;
	b.x = d->x;
	b.y = d->y;
	//printf("%d, %d\n", a.x,a.y);
	r = rot(p0, a, b);
	if(r==0)
	{
		if(normSq(p0,a) >= normSq(p0,b)) return 1;
		else return -1;
	}
	if(r==1) return 1;
	else return -1;
}
void graham(int n)
{
	int l=0, i, p, q, y;
	struct node temp;
	for(i=1;i<n;i++)
	{
		y = inp[i].y;
		//First, choosing the lowest point and if two points have the same x coordinate choosing the leftmost one.
		if(y<inp[l].y || (y == inp[l].y && inp[i].x < inp[l].x))
		{
			l=i;
		}
	}
	//Swapping lowest point to index 0.
	temp = inp[0];
	inp[0]=inp[l];
	inp[l]=temp;
	
	p0 = inp[0];
	//Sorting the points according to the order in which they form a simple polygon.
	qsort(&inp[1], n-1, sizeof(struct node), comp);
	
	/*printf("The sorted set is:-\n");
	for(i=0;i<n;i++)
	{
		printf("(%d, %d), ", inp[i].x, inp[i].y);
	}*/
	
	q=1;
	//Removing the collinear points by choosing the outermost collinear point among them.
	for(i=1;i<n;i++)
	{
		while(i < n-1 && rot(p0, inp[i],inp[i+1]) ==0)
			i++;
		
		inp[q] = inp[i];
		q++;
	}
	
	//If, effective set is less than 3 we are done as convex polygon cannot be formed.
	if(q<3) return;
	stack = (struct node *)malloc(n*(sizeof(struct node)));
	//Putting first 3 points into the stack.
	for(i=0;i<3;i++) stack[i] = inp[i];
	p=3;
	
	
	for(i=3;i<q;i++)
	{
		//Till we don't get a point such that the last point
		//in the stack is more counter-clockwise than the next element 
		//with respect to second-last element we keep on popping from the stack.
		while(rot(stack[p-2],stack[p-1], inp[i])!=-1)
			p--;
		stack[p] = inp[i];
		p++;
	}
	/*printf("\nThe convex hull is:\n");
	for(i=0;i<p;i++)
	{
		printf("(%d, %d), ", stack[i].x, stack[i].y);
	}*/
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
		inp = (struct node *)malloc(n[i]*(sizeof(struct node)));
		while(ind<1)
		{
			for(j=0;j<n[i];j++)
			{
				inp[j].x = rand();
				inp[j].y = rand();	
			}
			begin = clock();
			graham(n[i]);
			end = clock();
			tim[ind] = ((double)(end - begin))/ CLOCKS_PER_SEC;
			printf("%f\n", tim[ind]);
			ind++;
		}
		ind=0;
	}
	return 0;
}
