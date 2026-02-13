#include <iostream>      
#include <vector>        
#include <algorithm>     // esto es por el sort, para ordenar
using namespace std;


// esta estructura es una arista, o sea, una conexión entre dos nodos
class Edge {
    public:
    int u, v, weight; // u y v son los nodos que conecta, weight es el peso

    // esto es para que se puedan ordenar por peso de menor a mayor
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// estructura pa manejar conjuntos distintos
class DSU {
    private:
    vector<int> parent, rank;

    public:
    // constructor, cada nodo empieza siendo su propio jefe (o raíz)
    DSU(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; ++i) parent[i] = i;
    }

    // encuentra el jefe del conjunto al que pertenece x
    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]); // Si no es su propio jefe, entonces se busca a la raiz del conjunto
        return parent[x];
    }

    // une dos conjuntos si no están en el mismo
    bool unite(int x, int y) {
        int xboss = find(x), yboss = find(y);
        if(xboss == yboss) return false; // ya están conectados porque comparten la misma raiz, no se hace nada

        // unimos el de menor rango al de mayor rango para que no se desequilibre mucho
        if(rank[xboss] < rank[yboss]) parent[xboss] = yboss;
        else if(rank[xboss] > rank[yboss]) parent[yboss] = xboss;
        else {
            parent[yboss] = xboss;
            rank[xboss]++;
        }
        return true;
        
    }
};

// algoritmo de Kruskal para encontrar el MST (el árbol de expansión mínimo)
vector<Edge> kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // primero ordenamos las aristas por peso
    DSU dsu(n); // creamos la estructura para unir y buscar conjuntos
    vector<Edge> mst; // acá vamos metiendo las aristas que sí van al árbol

    // recorremos todas las aristas ordenadas
    for(const auto& e : edges) {
        if(dsu.unite(e.u, e.v)) { // si no forman ciclo, la metemos al MST
            mst.push_back(e);
        }
    }
    return mst; // devolvemos las aristas del árbol mínimo
}

int main() {
    // este es nuestro grafo, son aristas entre nodos con sus pesos
    vector<Edge> edges = {
        {0, 1, 7},
        {0, 3, 5},
        {1, 2, 8},
        {1, 3, 9},
        {1, 4, 7},
        {2, 4, 5},
        {3, 4, 15},
        {3, 5, 6},
        {4, 5, 8},
        {4, 6, 9},
        {5, 6, 11}
    };

    int n = 7; // tenemos 7 nodos, del 0 al 6 (importante no confundir con el número de aristas)

    vector<Edge> mst = kruskalMST(n, edges); // sacamos el árbol mínimo

    int totalWeight = 0; // para ir sumando el peso total del árbol
    cout << "Conexiones:\n";
    for(const auto& e : mst) {
        cout << e.u << " - " << e.v << " (Peso: " << e.weight << ")\n";
        totalWeight += e.weight;
    }
    cout << "Peso total: " << totalWeight << endl;
    return 0;
}
