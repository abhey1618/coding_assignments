using namespace std;
#include<stdio.h>
#include<bits.h>
#include<vector>
#include<iostream>
#include<queue>
int V;

class Graph
{
	int vert;
	vector<vector<int> > capacity, flow;
	vector<int> height, excess, seen;
	queue<int> excess_vertices;
	// Function to push excess flow from u 
    void push(int u, int v);
  
    // Function to relabel a vertex u 
    void relabel(int u);

    // This function is called to initialize 
    // preflow 
    void initialize(int s);
    
    //Function to saturate all excess in a vertex
    void discharge(int u);

public:
	//Initialize the graph based on number of vertices
	initgraph(int V);
	
    // function to add an edge to graph 
    void addEdge(int A, int B, int capa); 
    
    // returns maximum flow from s to t 
    int getMaxFlow(int s, int t); 
};

void Graph::addEdge(int A, int B, int capa)
{
	capacity[A][B] = capa;
	//printf("%d\n", capacity[A][B]);
}

Graph::initgraph(int V) 
{
    this->vert = V; 
    // all vertices are initialized with 0 height 
    // and 0 excess flow
    excess.assign(V, 0);
    height.assign(V, 0);
    
	seen.assign(V, 0);
    //Seen is the number of vertices a vertex has seen during its discharge
	capacity.assign(V, vector<int>(V, 0));
}

void Graph::initialize(int s)
{
    height[s] = V; //Give height V to source
    flow.assign(V, vector<int>(V, 0));
    excess[s] = INT_MAX;//We can transfer a lot from source
    for (int i = 1; i < V; i++)
        push(0, i); //Saturate all the edges coming out from source
}

void Graph::push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;//Increase for forward edge
    flow[v][u] -= d;//Decrease for backward edge
    excess[u] -= d;
    excess[v] += d;
    if (excess[v] == d)
        excess_vertices.push(v);
}

void Graph::relabel(int u)
{
    int d = INT_MAX;
    for (int i = 0; i < V; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);//Choose the minimum vertex with height greater than vertex u
    }
    if (d < INT_MAX)
        height[u] = d + 1;
}

void Graph::discharge(int u)
{
    while (excess[u] > 0) {
        if (seen[u] < V) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v]+1)
                push(u, v);//If there is a feasible downward sloping edge
            else 
                seen[u]++;//Moving on to the next vertex
        } else {
            relabel(u);//After covering all vertices, we need to relabel u and set its seen to 0.
            seen[u] = 0;
        }
    }
}

int Graph::getMaxFlow(int s, int t)
{
	initialize(s);
	
    while (!excess_vertices.empty()) //Till queue not empty
	{
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);//Saturate all excess from a vertex if its not source or sink
    }

    int max_flow = 0;
    max_flow = excess[t];//MaxFLow is excess in sink because we can never change the height of sink
    return max_flow;
}

int main() 
{
    int flow,E,a,b,c;
    Graph g;
    printf("Enter number of vertices, edges and for each edge endpoints and capacity:\n");
    scanf("%d %d", &V, &E);
    g.initgraph(V);
	for(int i=0;i<E;i++)
    {
    	scanf("%d %d %d", &a, &b, &c);
    	g.addEdge(a,b,c);
	}
    
    // Initialize source and sink 
    int s = 0, t = V-1;
    
    //flow = g.getMaxFlow(s,t);
    cout << "Maximum flow is " << g.getMaxFlow(s,t) << endl;
    return 0; 
}
