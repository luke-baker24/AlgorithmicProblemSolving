#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

class Vertex {
    public:
    int value;

    //Maps verted ID to edge weight
    std::unordered_map<int, int> edges;

    //For pathfinding
    long d;
    int pi;

    Vertex(int _value) {
        this->value = _value;

        this->pi = -1;
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
void dijkstra(Graph* graph, Vertex* s) {
    s->d = 0;
    
    std::priority_queue<std::pair<long, Vertex*>, std::vector<std::pair<long, Vertex*>>, std::greater<std::pair<long, Vertex*>>> Q;
    std::set<int> S;

    Q.push({s->d, s});
    
    while (!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();

        if (S.find(u->value) != S.end())
            continue;

        for (std::pair<int, int> edge : u->edges) {
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
void printPath(Vertex* s, Vertex* v, int runningSum) {
    if (v->d == 1000000000) 
        std::cout << "Impossible" << std::endl;
    
    else 
        std::cout << v->d << std::endl;
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

            graph.vertices[u].edges.insert({v, w});
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