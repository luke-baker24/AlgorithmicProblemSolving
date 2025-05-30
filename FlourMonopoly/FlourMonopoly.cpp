#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

long INF = 1e18;

class Vertex {
    public:
    long value;

    // Maps vertex ID to edge weight
    std::vector< std::pair<long, long> > edges;

    // For pathfinding
    long d;
    long pi;

    Vertex(long _value) {
        this->value = _value;

        this->pi = -1;
        this->d = INF;
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
    bool operator()(const std::pair<long, Vertex*>& a, const std::pair<long, Vertex*>& b) const {
        return a.first > b.first;
    }
};

// Runs Dijkstra's algorithms to compute all SSSP distances
// for directed graph G and source vertex s.
// G must not contain any negative-weight edges, but it may
// contain cycles.
void dijkstra(Graph* graph, Vertex* s) {
    s->d = 0;
    
    std::priority_queue<std::pair<long, Vertex*>, std::vector<std::pair<long, Vertex*>>, VertexComparator> Q;
    std::set<long> S;

    Q.push({s->d, s});
    
    while (!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();

        if (S.find(u->value) != S.end())
            continue;

        for (std::pair<long, long> edge : u->edges) {
            if (graph->vertices[edge.first].d > u->d + edge.second) {
                graph->vertices[edge.first].d = u->d + edge.second;
                graph->vertices[edge.first].pi = u->value;

                Q.push({graph->vertices[edge.first].d, &graph->vertices[edge.first]});
            }
        }
        
        S.insert(u->value);
    }
}

// Prints the shortest path from source vertex s to vertex v in
// directed graph G.
// Assumes a SSSP algorithm has already terminated.
void printPath(Vertex* s, Vertex* v) {
    if (v->d == INF) 
        std::cout << "X" << std::endl;
    
    else 
        std::cout << v->d << std::endl;
}

int main() {
    long nodes, edges, d;
    std::cin >> nodes >> edges >> d;

    Graph graph;

    for (long i = 0; i < nodes; i++) {
        graph.vertices.push_back(Vertex(i));
    }

    for (long i = 0; i < edges; i++) {
        long u, v, w;
        std::cin >> u >> v >> w;

        u--;
        v--;

        graph.vertices[u].edges.push_back(std::pair<long, long>(v, w > d ? d : w));
        graph.vertices[v].edges.push_back(std::pair<long, long>(u, w > d ? d : w));
    }

    Vertex* source = &graph.vertices[0];

    dijkstra(&graph, source);

    for (int i = 0; i < nodes; i++) {
        printPath(source, &graph.vertices[i]);
    }
}