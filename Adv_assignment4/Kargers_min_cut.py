import random

class Edge:
    def __init__(self,A,B):
        self.A = A
        self.B = B

class Graph:
    def __init__(self, V):
        self.n_vert = V
        self.EdgeSet = []

    def addEdge(self, A, B):
        self.EdgeSet.append(Edge(A,B))

class subset:
    def __init__(self, parent, rank):
        self.parent = parent
        self.rank = rank

def kargerCut(Graph):
    V = Graph.n_vert
    EList = Graph.EdgeSet
    E = len(EList)
    subsets = [0]*V

    for i in range(V):
        subsets[i] = subset(i, 0) #Initially singleton sets

    vert = V
    while vert>2:
        n = random.randint(0,E-1) #Choose an edge to contract
        sub1 = find(subsets, EList[n].A)
        sub2 = find(subsets, EList[n].B)
        #print(sub1 sub2)

        if sub1 == sub2:
            continue ##If both vertices belong to same subset

        else:
            vert = vert-1
            ##If both vertices belong to different subsets
            Union(subsets, sub1, sub2)

    n_cut = 0
    ##Now, we have only 2 subsets
    for i in range(E):
        sub1 = find(subsets, EList[i].A)
        sub2 = find(subsets, EList[i].B)
        ##We are only removing edges whose
        ##vertices belong to different subsets
        ##As, that gives us an edge cut
        if sub1 != sub2:
            n_cut = n_cut+1

    return n_cut

def find(subsets, i):
    ##Path Compression
    if subsets[i].parent != i:
        subsets[i].parent = find(subsets, subsets[i].parent)

    return subsets[i].parent

def Union(subsets, root1, root2):

    ##Higher rank becomes parent
    if subsets[root1].rank < subsets[root2].rank:
        subsets[root1].parent = root2
    elif subsets[root1].rank > subsets[root2].rank:
        subsets[root2].parent = root1

    ##If equal ranks doesn't matter which tree becomes parent
    else:
        subsets[root2].parent = root1
        subsets[root1].rank += 1

    
if __name__ == "__main__":
    V = 8 #number of vertices
    E = 14 #number of edges
    G = Graph(V) #Initialize Graph

    ## Add Edges to the graph
    G.addEdge(0,1)
    G.addEdge(0,2)
    G.addEdge(1,3)
    G.addEdge(0,3)
    G.addEdge(2,3)
    G.addEdge(1,2)
    G.addEdge(4,5)
    G.addEdge(4,6)
    G.addEdge(5,7)
    G.addEdge(4,7)
    G.addEdge(6,7)
    G.addEdge(5,6)
    G.addEdge(1,4)
    G.addEdge(2,7)

    #As, E is the upper bound for global min cut
    gcut = E

    random.seed(1618)

    #Calculate cut _ times and take the minimum value till now
    #Can change the number of times
    for i in range(5):
        #print(f'{i+1}th iteration')
        cut = kargerCut(G)
        if cut < gcut:
            gcut = cut

    print(f'{gcut} is Minimum Cut')
