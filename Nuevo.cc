#include <iostream>      
#include <vector>        
#include <algorithm>     
using namespace std;


class Edge {
    public:
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};


class UnionFind {
    private:
    vector<int> parent, rank;

    public:
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; ++i) parent[i] = i;
    }

    
    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]); 
        return parent[x];
    }

    
    bool unite(int x, int y) {
        int parentX = find(x), parentY = find(y);
        if(parentX == parentY) return false; 

        
        if(rank[parentX] < rank[ parentY]) parent[parentX] =  parentY;
        else if(rank[parentX] > rank[ parentY]) parent[ parentY] = parentX;
        else {
            parent[parentY] = parentX;
            rank[parentX]++;
        }
        return true;
        
    }
};


void addIfNotCycle(Edge edge, UnionFind& searchSet, vector<Edge>& minimmumSpanningTree) {
    if(searchSet.unite(edge.u, edge.v)) { 
            minimmumSpanningTree.push_back(edge);;
    }
}


vector<Edge> createMinimmumSpanningTree(UnionFind& searchSet, vector<Edge>& edges) {
    
    vector<Edge> minimmumSpanningTree; 

    for(const auto& eachEdge : edges) {
        addIfNotCycle(eachEdge, searchSet, minimmumSpanningTree);
    }
    return minimmumSpanningTree; 
}

void printMinimmumSpanningTree(vector<Edge> minimmumSpanningTree) {
int totalTreeWeight = 0; 
    cout << "Conexiones:\n";
    for(const auto& eachEdge : minimmumSpanningTree) {
        cout << eachEdge.u << " - " << eachEdge.v << " (Peso: " << eachEdge.weight<< ")\n";
        totalTreeWeight += eachEdge.weight;
    }
    cout << "Peso total: " << totalTreeWeight << endl;
}

void kruskalAlgorithm() {

vector<Edge> Graph = {
        {0, 1, 7},
        {0, 3, 5},
        {1, 2, 8},
        {1, 3, 9},
        {1, 4, 7},
        {2, 4, 5},
        {3, 4, 15},
    };

    int numberOfNodes = 7; 

    sort(Graph.begin(), Graph.end()); 
    UnionFind set(numberOfNodes); 
    vector<Edge> minimmumSpanningTree = createMinimmumSpanningTree(numberOfNodes, set, Graph);
    printMinimmumSpanningTree(minimmumSpanningTree);
}


int main() {
    kruskalAlgorithm();
    return 0;
}
