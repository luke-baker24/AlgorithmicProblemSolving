#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <cmath>

class Vertex {
    public:
    int value;

    //Maps verted ID to edge weight
    std::unordered_map<Vertex*, int> edges;

    //For pathfinding
    long d;
    Vertex* pi;

    Vertex(int _value) {
        this->value = _value;

        this->pi = nullptr;
        this->d = 1000000000;
    }
};

class Graph {
    public:
    std::vector<Vertex> vertices;

    Graph() {
        vertices = std::vector<Vertex>();
    }
};

struct VertexComparator {
    bool operator()(const Vertex* a, const Vertex* b) const {
        return a->d > b->d;
    }
};

// Runs Dijkstra's algorithms to compute all SSSP distances
// for directed graph G and source vertex s.
// G must not contain any negative-weight edges, but it may
// contain cycles.
void dijkstra(Graph* g, Vertex* s) {
    s->d = 0;
    
    std::priority_queue<Vertex*, std::vector<Vertex*>, VertexComparator> Q;
    std::set<Vertex*> S;

    Q.push(s);
    
    while (!Q.empty()) {
        Vertex* u = Q.top();
        Q.pop();

        if (S.find(u) != S.end())
            continue;

        for (std::pair<Vertex*, int> edge : u->edges) {
            if (edge.first->d > u->d + edge.second) {
                edge.first->d = u->d + edge.second;
                edge.first->pi = u;

                Q.push(edge.first);
            }
        }
        
        S.insert(u);
    }
}

int max(int one, int two) {
    return one > two ? one : two;
}

// Prints the shortest path from source vertex s to vertex v in
// directed graph G.
// Assumes a SSSP algorithm has already terminated.
void printPath(Vertex* s, Vertex* v, int runningSum) {
    if (s == v)
        std::cout << runningSum << std::endl;

    else if (v->pi == nullptr)
        std::cout << "Impossible" << std::endl;

    else
        printPath(s, v->pi, runningSum + v->pi->edges.at(v));
}

int main() {
    while (true) {
        int nodes, edges, queries, s;
        std::cin >> nodes >> edges >> queries >> s;

        //End case
        if (nodes == 0 && edges == 0 && queries == 0 && s == 0) break;

        Graph graph;

        for (int i = 0; i < nodes; i++) {
            graph.vertices.push_back(Vertex(i));
        }

        for (int i = 0; i < edges; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;

            graph.vertices[u].edges.insert({&graph.vertices[v], w});
        }

        Vertex* source = &graph.vertices[s];

        dijkstra(&graph, source);

        for (int i = 0; i < queries; i++) {
            int q;
            std::cin >> q;

            printPath(source, &graph.vertices[q], 0);
        }
    }
}