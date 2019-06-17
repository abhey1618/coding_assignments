#include<stdio.h>
#include<stdlib.h>
int *stack, p=0;
// A structure to represent an adjacency list's node 
struct AdjLNode 
{ 
    int y; 
    struct AdjLNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList 
{ 
    int mark;
	struct AdjLNode *head;  
}; 

// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be n (number of vertices in graph) 
struct Graph 
{ 
    int n; 
    struct AdjList* array; 
};

//A function that creates a graph of n vertices
struct Graph* CreateGraph(int n) 
{ 
    int i;
	struct Graph* graph =  (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->n = n; 
  
    // Create an array of adjacency lists. Size of array will be n
    graph->array =  (struct AdjList*) malloc(n * sizeof(struct AdjList)); 
  
    // Initialize each adjacency list as empty by making head as NULL
    // Initially mark all vertices as 0, i.e. unmarked
    for (i = 0; i < n; ++i)
	{
		graph->array[i].mark = 0;
		graph->array[i].head = NULL;
	}
  
    return graph;
}

// This function will help us to add edges to our undirected graph 
void addEdge(struct Graph* graph, int x, int y) 
{ 
    // This adds an edge from x to y. A new node is added to the adjacency list of x.  
	// The node is added at the beginning 
	
	//Create a new node
    struct AdjLNode* node,*node2;
	node = (struct AdjLNode*) malloc(sizeof(struct AdjLNode));
    node->y = y;
    node->next = graph->array[x].head;
    graph->array[x].head = node; 
  
    // Since graph is undirected, add an edge from y to x also 
    node2 = (struct AdjLNode*) malloc(sizeof(struct AdjLNode));
    node2->y = x;
    node2->next = graph->array[y].head;
    graph->array[y].head = node2;
}

int DFScycle(struct Graph* graph, int n)
{
	struct AdjLNode* temp;
	//Start with pushing 0
	stack[p] = 0;
	while(graph->array[stack[p]].head == NULL && stack[p] < n-1)
	{
		//Loop over the nodes which don't have an edge with any other node
		stack[p]++;
	}
	while(p>=0)
	{
		temp = graph->array[stack[p]].head;
		//If Stack has a already visited vertex we have a cycle
		if(graph->array[stack[p]].mark == 1) return 1;
		//Marking the vertex as visited before popping it from the stack
		graph->array[stack[p]].mark = 1;
		while(temp != NULL)
		{
			//Popping stack's top element and pushing all its non-visited adjacent vertices
			if(graph->array[temp->y].mark == 0)
			{
				stack[p] = temp->y;
				p++;
			}
			temp = temp->next;
		}
		p--;
	}
	//Stack has become empty without popping any already visited vertex
	return 0;
}

void printGraph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->n; ++v) 
    { 
        struct AdjLNode* pc = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pc != NULL) 
        { 
            printf("-> %d", pc->y); 
            pc = pc->next; 
        } 
        printf("\n"); 
    } 
}

int main()
{
	int n,m,i,x,y;
	printf("Enter the number of vertices and edges in the graph and after that input the edges of the graph. \n");
	scanf("%d %d",&n,&m);
    struct Graph* graph = CreateGraph(n);
    
    stack = (int *) malloc(n*(sizeof(int)));
    
    for(i=0;i<m;i++)
    {
    	scanf("%d %d",&x,&y);
    	addEdge(graph,x,y);
	}
    
    //Uncomment the following line to print the adjacency list representation of the above graph 
    //printGraph(graph);
    
    m = DFScycle(graph,n);
    if(m==0) printf("Cycle does not exist");
    else printf("Cycle exists");
    return 0; 	
}
